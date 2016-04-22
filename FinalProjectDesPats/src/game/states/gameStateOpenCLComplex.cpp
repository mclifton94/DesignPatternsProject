//
//  gameStateOpenCLComplex.cpp
//  FinalProjectDesPats
//
//  Created by MarkClifton on 4/10/16.
//  Copyright © 2016 designPatterns. All rights reserved.
//

#include "gameStateOpenCLComplex.hpp"
#include "game.hpp"

#include "shaderObject.hpp"
#include "point.hpp"
#include "rectangle.hpp"
#include "tools.hpp"

#include <vector>

using namespace cap;
using namespace opencl;

namespace cap { namespace state {
    
    gameStateOpenCLComplex::gameStateOpenCLComplex(gameWindow* window, game* game)
    : m_Window(window), m_Timer(new timer), m_Game(game)
    {
        m_Timer->reset();
    }
    
    boundaries getBounds(float tlX, float tlY, float brX, float brY){
        boundaries bounds;
        
        bounds.TL.centerX = tlX;
        bounds.TL.centerY = tlY;
        
        bounds.BL.centerX = tlX;
        bounds.BL.centerY = brX;
        
        bounds.TR.centerX = brX;
        bounds.TR.centerY = tlY;
        
        bounds.BR.centerX = brX;
        bounds.BR.centerY = brY;
        
        return bounds;
    }
    
    void gameStateOpenCLComplex::loop(){
        std::cerr << "OpenCL Complex!\n";
        
        
        glPointSize(1);

        shaderObject shader(tools::getEnv("/FinalProjectDesPats/res/shaders/vs.shader"), tools::getEnv("/FinalProjectDesPats/res/shaders/fs.shader"));
        shader.enable();
        shader.setUniformMat4("pr_matrix", Perspective(90, 640/480.f, .1, 100));

        std::vector<point> pts;
        int numPts = 4096*2;
        pt data[numPts];
        direct none;
        none.xValue = 0;
        none.yValue = 0;
        none.zValue = 0;
        for(int i=0; i< numPts; i++){
            if( i%2 == 0){
                pts.push_back(point(vec3((2*i)/(float)numPts-1,(2*i)/(float)numPts-1, -1)));
                data[i].mass = 10;
            }else{
                pts.push_back(point(vec3((2*i)/(float)numPts-1,(-2*i)/(float)numPts+1, -1)));
                data[i].mass = 16;
            }
            pts[pts.size()-1].setColor(vec4(1,.5,1,1));
            data[i].centerX = pts[pts.size()-1].getPosition()[0];
            data[i].centerY = pts[pts.size()-1].getPosition()[1];
            data[i].centerZ = pts[pts.size()-1].getPosition()[2];
            
            data[i].mass = 16;
            data[i].direction = none;
        }
        
        cap::opencl::pt pt[numPts];
        
        opencl::ocl o(opencl::DEVICE::GPU);
        o.setup(cap::utils::tools::getEnv("/FinalProjectDesPats/res/kernels/collision.cl").c_str(), (char*)"collision", 2048);
        o.getInputOutputPts(numPts);

        m_gravity = 0;
        m_release = false;
        
        rectangle temp (vec2(1,1), vec3(0,0,-1));
        while(!m_Window->shouldClose()){
            m_Window->clear();
            
            if(m_Timer->check()){
                std::cerr << m_Timer->get() << "\n";
                m_Timer->reset();
                
            }
            m_Timer->update();
            
            getInput();
            
            //Number of items
            cap::opencl::argument arg1;
            arg1.sizeOf = sizeof(int);
            arg1.actualParam = new int(numPts);
            
            //Number of items in array
            cap::opencl::argument arg2;
            arg2.sizeOf = sizeof(boundaries);
            arg2.actualParam = new boundaries(getBounds(-640/480.f, 1, 640/480.f, -1));
            
            //Number of items in array
            cap::opencl::argument arg3;
            arg3.sizeOf = sizeof(float);
            arg3.actualParam = new float(m_gravity);
            
            //Number of items in array
            cap::opencl::argument arg4;
            arg4.sizeOf = sizeof(bool);
            arg4.actualParam = new bool(m_release);
            
            cap::opencl::argument args[4] = {arg1, arg2, arg3, arg4};
            o.setArguments(4, args);
            
            delete (int*)arg1.actualParam;
            delete (boundaries*)arg2.actualParam;
            delete (float*)arg3.actualParam;
            delete (bool*)arg4.actualParam;
        
            o.writeInput(data);
            o.getWorkGroupAndExec();
            o.wait();
            o.getResults(pt);
            
            for(int i=0; i<numPts; i++){
                pts[i].m_position[0] = pt[i].centerX;
                pts[i].m_position[1] = pt[i].centerY;
                pts[i].m_position[2] = pt[i].centerZ;
                
                pts[i].setup();
                pts[i].rebuffer();
                
                data[i].centerX = pt[i].centerX;
                data[i].centerY = pt[i].centerY;
                data[i].centerZ = pt[i].centerZ;
                data[i].direction = pt[i].direction;
            }
            
            for(auto& item: pts){
                item.draw();
            }
            
            m_Window->swap();
            glfwPollEvents();
        }
    }
    
    bool gameStateOpenCLComplex::changeState(){
        return false;
    }
    
    void gameStateOpenCLComplex::getInput(){
        if(inputKeyboard::keysPressed.count(GLFW_KEY_1)){
            if(inputKeyboard::keysPressed[GLFW_KEY_1]){
                m_gravity += .0001;
            }
        }
        if(inputKeyboard::keysPressed.count(GLFW_KEY_2)){
            if(inputKeyboard::keysPressed[GLFW_KEY_2]){
                m_gravity += -.0001;
            }
        }
        if(inputKeyboard::keysPressed.count(GLFW_KEY_3)){
            if(inputKeyboard::keysPressed[GLFW_KEY_3]){
                m_release = true;
            }
        }
        if(inputKeyboard::keysPressed.count(GLFW_KEY_4)){
            if(inputKeyboard::keysPressed[GLFW_KEY_4]){
                m_release = false;
            }
        }
        
    }
    
}}
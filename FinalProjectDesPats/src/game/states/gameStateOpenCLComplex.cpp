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
        
        glEnable(GL_PROGRAM_POINT_SIZE);
        glPointSize(5);
        
        shaderObject shader(tools::getEnv("/FinalProjectDesPats/res/shaders/vs.shader"), tools::getEnv("/FinalProjectDesPats/res/shaders/fs.shader"));
        shader.enable();
        shader.setUniformMat4("pr_matrix", Ortho(-1, 1, -1, 1, .1, 100));

        std::vector<point> pts;
        int numPts = 64*32;
        pt data[numPts];
        direct none;
        none.xValue = 0;
        none.yValue = 0;
        none.zValue = 0;
        for(int i=0; i< numPts; i++){
            pts.push_back(point(vec3((2*i+1)/(float)numPts-1,1,-1)));
            data[i].centerX = (2*i+1)/(float)numPts-1;
            data[i].centerY = rand()%100-50;
            data[i].mass = 10;
            data[i].direction = none;
        }
        
        cap::opencl::pt pt[numPts];
        
        opencl::ocl o(opencl::DEVICE::GPU);
        o.setup(cap::utils::tools::getEnv("/FinalProjectDesPats/res/kernels/collision.cl").c_str(), (char*)"collision", numPts);
        o.getInputOutputPts(numPts);
        
        m_gravity = -.0001;
        
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
            arg2.actualParam = new boundaries(getBounds(-1, .9, 1, -.9));
            
            //Number of items in array
            cap::opencl::argument arg3;
            arg3.sizeOf = sizeof(float);
            arg3.actualParam = new float(m_gravity);
            
            cap::opencl::argument args[3] = {arg1, arg2, arg3};
            o.setArguments(3, args);
            
            delete (int*)arg1.actualParam;
            delete (boundaries*)arg2.actualParam;
            delete (float*)arg3.actualParam;
        
            o.writeInput(data);
            o.getWorkGroupAndExec();
            o.wait();
            o.getResults(pt);
            
            for(int i=0; i<numPts; i++){
                pts[i].setPosition(vec3(pt[i].centerX, pt[i].centerY, pts[i].getPosition()[2]));
                data[i].centerX = pt[i].centerX;
                data[i].centerY = pt[i].centerY;
                if(rand()%100>95){
                    data[i].centerY = data[i].centerY+2*m_gravity;
                }else{
                    data[i].centerY = pt[i].centerY;
                }
                data[i].direction = pt[i].direction;
            }
            
            for(auto& item: pts){
                item.draw();
            }
            
            m_Window->swap();
            glfwPollEvents();
            
            if(changeState()){
                return;
            }
        }
    }
    
    bool gameStateOpenCLComplex::changeState(){
        return false;
    }
    
    void gameStateOpenCLComplex::getInput(){
        if(inputKeyboard::keysPressed.count(GLFW_KEY_1)){
            if(inputKeyboard::keysPressed[GLFW_KEY_1]){
                m_gravity = .0001;
            }
        }
        if(inputKeyboard::keysPressed.count(GLFW_KEY_2)){
            if(inputKeyboard::keysPressed[GLFW_KEY_2]){
                m_gravity = -.0001;
            }
        }
        
    }
    
}}
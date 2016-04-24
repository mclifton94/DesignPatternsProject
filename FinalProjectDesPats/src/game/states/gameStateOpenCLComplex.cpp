//
//  gameStateOpenCLComplex.cpp
//  FinalProjectDesPats
//
//  Created by MarkClifton on 4/10/16.
//  Copyright © 2016 designPatterns. All rights reserved.
//

#include "gameStateOpenCLComplex.hpp"
#include "game.hpp"


using namespace cap;
using namespace opencl;

namespace cap { namespace state {
    
    //--------------------------------------------------------------------------------
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
    
    //--------------------------------------------------------------------------------
    gameStateOpenCLComplex::gameStateOpenCLComplex(gameWindow* window, game* game)
    : m_Window(window), m_Game(game), o(opencl::DEVICE::GPU)
    {
        m_shader.reset(new shaderObject(tools::getEnv("/FinalProjectDesPats/res/shaders/vs.shader"), tools::getEnv("/FinalProjectDesPats/res/shaders/fs.shader")));
        m_shader->enable();
        m_shader->setUniformMat4("pr_matrix", Perspective(90, 640/480.f, .1, 100));
        m_shader->disable();
    }
    
    //--------------------------------------------------------------------------------
    void gameStateOpenCLComplex::setup(){
        glPointSize(3);
        
        pts.clear();
        
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
        
        o.setup(cap::utils::tools::getEnv("/FinalProjectDesPats/res/kernels/collision.cl").c_str(), (char*)"collision", 64);
        o.getInputOutputPts(numPts);
        
        m_gravity = 0;
        m_release = false;
        
        arg1.sizeOf = sizeof(int);
        arg2.sizeOf = sizeof(boundaries);
        arg3.sizeOf = sizeof(float);
        arg4.sizeOf = sizeof(bool);
        
        bounds = boundaries(getBounds(-640/480.f, 1, 640/480.f, -1));
    }
    
    //--------------------------------------------------------------------------------
    void gameStateOpenCLComplex::loop(){
        m_Window->clear();
        m_shader->enable();
        getInput();
        
        arg1.actualParam = &numPts;
        arg2.actualParam = &bounds;
        arg3.actualParam = &m_gravity;
        arg4.actualParam = &m_release;
        
        args[0] = arg1;
        args[1] = arg2;
        args[2] = arg3;
        args[3] = arg4;
        o.setArguments(4, args);

        o.writeInput(data);
        o.getWorkGroupAndExec();
        o.wait();
        o.getResults(pt);
        
        for(int i=0; i<numPts; i++){
            pts[i].m_position[0] = pt[i].centerX;
            pts[i].m_position[1] = pt[i].centerY;
            pts[i].m_position[2] = pt[i].centerZ;
            
            pts[i].setup();
            pts[i].buffer();
            
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
        m_shader->disable();
        changeState();
    }
    
    //--------------------------------------------------------------------------------
    bool gameStateOpenCLComplex::changeState(){
        if( inputKeyboard::keysPressed.count(GLFW_KEY_0) && inputKeyboard::keysPressed[GLFW_KEY_0]){
            m_Game->setState(m_Game->getStateOpenCL());
            return true;
        }else if( inputKeyboard::keysPressed.count(GLFW_KEY_9) && inputKeyboard::keysPressed[GLFW_KEY_9]){
            m_Game->setState(m_Game->getStateOpenCLComplex());
            return true;
        }else if( inputKeyboard::keysPressed.count(GLFW_KEY_8) && inputKeyboard::keysPressed[GLFW_KEY_8]){
            m_Game->setState(m_Game->getStateMenu());
            return true;
        }
        return false;
    }
    
    //--------------------------------------------------------------------------------
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
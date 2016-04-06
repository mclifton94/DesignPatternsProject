//
//  gameStateGame.cpp
//  FinalProjectDesPats
//
//  Created by MarkClifton on 4/3/16.
//  Copyright © 2016 designPatterns. All rights reserved.
//

#include "gameStateGame.hpp"

#include "shaderObject.hpp"
#include "rectangle.hpp"
#include "tools.hpp"

namespace cap { namespace state {
  
    //--------------------------------------------------------------------------------
    gameStateGame::gameStateGame(gameWindow* window)
    : m_Window(window), m_Timer(new timer)
    {
        m_Timer->reset();
    }
    
    //--------------------------------------------------------------------------------
    void gameStateGame::loop(){

        shaderObject shader(tools::getEnv("/FinalProjectDesPats/res/shaders/vs.shader"), tools::getEnv("/FinalProjectDesPats/res/shaders/fs.shader"));
        shader.enable();
        
        GLuint VertexArrayID;
        glGenVertexArrays(1, &VertexArrayID);
        glBindVertexArray(VertexArrayID);
        
        rectangle r(vec2(1,1),vec3(-1,0,0));
        rectangle j(vec2(1,1),vec3(1,0,0));
        
        while(!m_Window->shouldClose()){
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            
            glEnableVertexAttribArray(0);

            glVertexAttribPointer(0, 3,GL_FLOAT,GL_FALSE,0,BUFFER_OFFSET(0));

            r.draw();
            j.draw();
            
            glfwSwapBuffers(m_Window->getWindowID());
            glfwPollEvents();
        }
        
    }
    
}}
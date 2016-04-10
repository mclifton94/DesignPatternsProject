//
//  gameStateGame.cpp
//  FinalProjectDesPats
//
//  Created by MarkClifton on 4/3/16.
//  Copyright © 2016 designPatterns. All rights reserved.
//

#include "gameStateGame.hpp"
#include "game.hpp"

#include "shaderObject.hpp"
#include "rectangle.hpp"
#include "tools.hpp"

namespace cap { namespace state {
  
    //--------------------------------------------------------------------------------
    gameStateGame::gameStateGame(gameWindow* window, game* game)
    : m_Window(window), m_Timer(new timer), m_Game(game)
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
        
        bool adding = true;
        
        while(!m_Window->shouldClose()){
            m_Window->clear();
            
            if(m_Timer->check()){
                std::cerr << m_Timer->get() << "\n";
                m_Timer->reset();
            }
            m_Timer->update();

            r.draw();
            j.draw();
            
            vec4 color = r.getColor();
            vec4 color1 = j.getColor();
            if( color[0] > 1 ){
                adding = false;
            }else if( color[0] < 0){
                adding = true;
            }
            
            if( adding ){
                r.setColor(vec4(color[0]+.01, .5, .5, 1));
                j.setColor(vec4(.5, color1[1]+.01, .5, 1));
            }else{
                r.setColor(vec4(color[0]-.01, .5, .5, 1));
                j.setColor(vec4(.5, color1[1]-.01, .5, 1));
            }
            
            m_Window->swap();
            glfwPollEvents();
            
            if(changeState()){
                return;
            }
        }
    }
    
    bool gameStateGame::changeState(){
        if( inputKeyboard::keysPressed.count(GLFW_KEY_0)){
            m_Game->setState(m_Game->getStateOpenCL());
            return true;
        }
        return false;
    }
    
}}
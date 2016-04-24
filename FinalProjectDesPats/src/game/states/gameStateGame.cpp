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
    : m_Window(window),  m_Game(game)
    {
        shaderObject shader(tools::getEnv("/FinalProjectDesPats/res/shaders/vs.shader"), tools::getEnv("/FinalProjectDesPats/res/shaders/fs.shader"));
        shader.enable();
        shader.setUniformMat4("pr_matrix", Ortho(-1, 1, -1, 1, .1, 100));
    }
    
    //--------------------------------------------------------------------------------
    void gameStateGame::setup(){
    }
    
    //--------------------------------------------------------------------------------
    void gameStateGame::loop(){
        m_Window->clear();

        m_Window->swap();
        glfwPollEvents();
            
        changeState();
    }
    
    bool gameStateGame::changeState(){
        if( inputKeyboard::keysPressed.count(GLFW_KEY_0)){
            m_Game->setState(m_Game->getStateOpenCL());
            return true;
        }else if( inputKeyboard::keysPressed.count(GLFW_KEY_9)){
            m_Game->setState(m_Game->getStateOpenCLComplex());
            return true;
        }
        return false;
    }
    
}}
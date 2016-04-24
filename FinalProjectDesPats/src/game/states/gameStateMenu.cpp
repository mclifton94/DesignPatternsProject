//
//  gameStateMenu.cpp
//  FinalProjectDesPats
//
//  Created by MarkClifton on 4/3/16.
//  Copyright © 2016 designPatterns. All rights reserved.
//

#include "gameStateMenu.hpp"
#include "game.hpp"

#include "shaderObject.hpp"
#include "tools.hpp"

namespace cap { namespace state {
    
    //--------------------------------------------------------------------------------
    gameStateMenu::gameStateMenu(gameWindow* window, game* game)
    : m_Window(window),  m_Game(game)
    {
        m_shader.reset(new shaderObject(tools::getEnv("/FinalProjectDesPats/res/shaders/vsMenu.shader"),
                                        tools::getEnv("/FinalProjectDesPats/res/shaders/fsMenu.shader")));
        m_shader->enable();
        m_shader->setUniformMat4("pr_matrix", Ortho(-1, 1, -1, 1, .1, 100));
        
        m_txPath["MenuPic"] = tools::getEnv("/FinalProjectDesPats/res/textures/MenuPicture.png");
        
        m_texManager.reset(new textureManager(16));
        m_texManager->submitTexture(m_txPath["MenuPic"]);
        m_shader->setUniform1iv("textures", m_texManager->getTextureIDs(), 16);
        
        m_menuPicture.reset(new rectangle(vec2(2,2),vec3(0,0,-1)));
        m_menuPicture->setTexture(m_texManager->findTexture(m_txPath["MenuPic"]).texture);
        m_menuPicture->setTexID(m_texManager->bindTexture(m_txPath["MenuPic"]));
        
        m_shader->disable();
    }
    
    //--------------------------------------------------------------------------------
    gameStateMenu::~gameStateMenu(){
    }
    
    //--------------------------------------------------------------------------------
    void gameStateMenu::setup(){
    }
    
    //--------------------------------------------------------------------------------
    void gameStateMenu::loop(){
        m_Window->clear();
        
        m_shader->enable();
        m_texManager->enableTextures();
        
        m_menuPicture->draw();
        
        m_Window->swap();
        glfwPollEvents();
        
        m_shader->disable();
        
        changeState();
    }
    
    //--------------------------------------------------------------------------------
    bool gameStateMenu::changeState(){
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
}}
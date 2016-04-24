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
        
        m_textures.push_back(new texture(tools::getEnv("/FinalProjectDesPats/res/textures/MenuPicture.png")));
        
        GLint texIDs[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        m_shader->setUniform1iv("textures", texIDs, 10);
        
        m_menuPicture.reset(new rectangle(vec2(2,2),vec3(0,0,-1)));
        m_menuPicture->setTexture(m_textures[0]);
        m_menuPicture->setTexID(1);
        
        m_texIDs.push_back(m_menuPicture->m_texture->getID());
        
        m_shader->disable();
    }
    
    //--------------------------------------------------------------------------------
    gameStateMenu::~gameStateMenu(){
        for(int c=0; c<m_textures.size(); c++){
            delete m_textures[c];
        }
    }
    
    //--------------------------------------------------------------------------------
    void gameStateMenu::setup(){
    }
    
    //--------------------------------------------------------------------------------
    void gameStateMenu::loop(){
        m_Window->clear();
        
        m_shader->enable();
        
        for (int i = 0; i < m_texIDs.size(); i++){
            glActiveTexture(GL_TEXTURE0 + i);
            glBindTexture(GL_TEXTURE_2D, m_texIDs[i]);
        }
        
        m_menuPicture->draw();
        
        m_Window->swap();
        glfwPollEvents();
        
        m_shader->disable();
        
        changeState();
    }
    
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
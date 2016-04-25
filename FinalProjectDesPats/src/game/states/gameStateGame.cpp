//
//  gameStateGame.cpp
//  FinalProjectDesPats
//
//  Created by MarkClifton on 4/3/16.
//  Copyright © 2016 designPatterns. All rights reserved.
//

#include "gameStateGame.hpp"
#include "game.hpp"

#include "rectangle.hpp"
#include "tools.hpp"

namespace cap { namespace state {
  
    //--------------------------------------------------------------------------------
    gameStateGame::gameStateGame(gameWindow* window, game* game)
    : m_Window(window),  m_Game(game)
    {
        m_shader.reset(new shaderObject(tools::getEnv("/FinalProjectDesPats/res/shaders/vsGame.shader"),
                                        tools::getEnv("/FinalProjectDesPats/res/shaders/fsGame.shader")));
        m_shader->enable();
        m_shader->setUniformMat4("pr_matrix", Ortho(-1, 1, -1, 1, .1, 100));
        
        m_txPath["DK_SPRITES"] = tools::getEnv("/FinalProjectDesPats/res/textures/dk.png");
        m_txPath["DK_BACKGROUND"] = tools::getEnv("/FinalProjectDesPats/res/textures/backgroundDK.png");
        
        m_texManager = textureManager::getInstance();
        m_texManager->submitTexture(m_txPath["DK_SPRITES"], 1);
        m_texManager->submitTexture(m_txPath["DK_BACKGROUND"], 0);
        m_shader->setUniform1iv("textures", m_texManager->getTextureIDs(), 16);
        
        player.reset(new DK(vec2(.25,.25),vec3(-1+.2,.29,-1)));
        player->setTexture(m_texManager->findTexture(m_txPath["DK_SPRITES"]).texture);
        player->setTexID(m_texManager->bindTexture(m_txPath["DK_SPRITES"]));
        
        screenMin = (player->getPosition()[0]+1)/2.f - .18/2.f;
        screenMax = (player->getPosition()[0]+1)/2.f + .18/2.f;
        
        background.reset(new rectangle(vec2(2,2), vec3(0,0,-2)));
        background->setTexture(m_texManager->findTexture(m_txPath["DK_BACKGROUND"]).texture);
        background->setTexID(m_texManager->bindTexture(m_txPath["DK_BACKGROUND"]));
        background->setTexCoords(texCoords(vec2(screenMin,1),vec2(screenMax,0)));
        
        m_shader->disable();
    }
    
    //--------------------------------------------------------------------------------
    void gameStateGame::setup(){
        m_menuMusic.reset(new audioTrack(tools::getEnv("/FinalProjectDesPats/res/sounds/theme.wav")));
        m_menuMusic->play();
    }
    
    //--------------------------------------------------------------------------------
    void gameStateGame::loop(){
        m_Window->clear();
        m_shader->enable();
        
        background->draw();
        player->standing();
        player->draw();

        m_Window->swap();
        glfwPollEvents();
        
        m_shader->disable();
        
        handleInput();
        changeState();
    }
    
    //--------------------------------------------------------------------------------
    void gameStateGame::handleInput(){
        if(inputKeyboard::keysPressed.count(GLFW_KEY_D)){
            if(inputKeyboard::keysPressed[GLFW_KEY_D]){
                player->setVelocity(.0022);
                player->setDirection(vec3(1,0,0));
                if(screenMax <= 1 && screenMin < 1-.175){
                    player->setPosition(player->getVelocity()*player->getDirection()+player->getPosition());
                    screenMin = (player->getPosition()[0]+1)/2.f - .175/2.f;
                    screenMax = (player->getPosition()[0]+1)/2.f + .175/2.f;
                }
                background->setTexCoords(texCoords(vec2(screenMin,1),vec2(screenMax,0)));
            }
        }
        if(inputKeyboard::keysPressed.count(GLFW_KEY_S)){
            if(inputKeyboard::keysPressed[GLFW_KEY_S]){
                player->setVelocity(.0022);
                player->setDirection(vec3(-1,0,0));
                if(screenMax >= .175 && screenMin >=0){
                    player->setPosition(player->getVelocity()*player->getDirection()+player->getPosition());
                    screenMin = (player->getPosition()[0]+1)/2.f - .175/2.f;
                    screenMax = (player->getPosition()[0]+1)/2.f + .175/2.f;
                }
                background->setTexCoords(texCoords(vec2(screenMin,1),vec2(screenMax,0)));
            }
        }
    }
    
    //--------------------------------------------------------------------------------
    bool gameStateGame::changeState(){
        if( inputKeyboard::keysPressed.count(GLFW_KEY_0) && inputKeyboard::keysPressed[GLFW_KEY_0]){
            m_Game->setState(m_Game->getStateOpenCL());
            m_menuMusic->pause();
            m_menuMusic.reset();
            return true;
        }else if( inputKeyboard::keysPressed.count(GLFW_KEY_9) && inputKeyboard::keysPressed[GLFW_KEY_9]){
            m_Game->setState(m_Game->getStateOpenCLComplex());
            m_menuMusic->pause();
            m_menuMusic.reset();
            return true;
        }else if( inputKeyboard::keysPressed.count(GLFW_KEY_8) && inputKeyboard::keysPressed[GLFW_KEY_8]){
            m_Game->setState(m_Game->getStateMenu());
            m_menuMusic->pause();
            m_menuMusic.reset();
            return true;
        }
        
        return false;
    }
    
}}
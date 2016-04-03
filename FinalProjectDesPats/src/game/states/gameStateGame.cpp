//
//  gameStateGame.cpp
//  FinalProjectDesPats
//
//  Created by MarkClifton on 4/3/16.
//  Copyright © 2016 designPatterns. All rights reserved.
//

#include "gameStateGame.hpp"

namespace cap { namespace state {
  
    //--------------------------------------------------------------------------------
    gameStateGame::gameStateGame(gameWindow* window)
    : m_Window(window), m_Timer(new timer)
    {
        m_Timer->reset();
    }
    
    //--------------------------------------------------------------------------------
    void gameStateGame::loop(){
    
        while( !m_Window->shouldClose() ){
            if( m_Timer->check()){
                std::cerr << m_Timer->get() << "\n";
                m_Timer->reset();
            }
            m_Timer->update();
            
            m_Window->clear();
            
            glfwPollEvents();
            
            m_Window->swap();
        }
        
    }
    
}}
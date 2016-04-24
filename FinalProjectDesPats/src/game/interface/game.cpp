//
//  game.cpp
//  FinalProjectDesPats
//
//  Created by MarkClifton on 4/3/16.
//  Copyright © 2016 designPatterns. All rights reserved.
//

#include "states.hpp"
#include "game.hpp"

namespace cap { namespace state {
    
    //--------------------------------------------------------------------------------
    class gameStateGame;
    
    //--------------------------------------------------------------------------------
    game* game::getInstance(){
        static game instance;
        return &instance;
    }

    //--------------------------------------------------------------------------------
    game::game()
    : m_Timer(new timer())
    {
        window.reset( new gameWindow(640, 480, (char*)"Game Window!", 1 ));
        m_pStateGame.reset(new gameStateGame(window.get(), this));
        m_pStateMenu.reset(new gameStateMenu(window.get(), this));
        m_pStateOpenCL.reset(new gameStateOpenCL(window.get(), this));
        m_pStateOpenCLComplex.reset(new gameStateOpenCLComplex(window.get(), this));
        setState(m_pStateMenu.get());
        
        m_Timer->reset();
    }
    
    //--------------------------------------------------------------------------------
    void game::setState(gameStates* state){
        m_pStateCurrent = state;
        m_pStateCurrent->setup();
    }
    
    //--------------------------------------------------------------------------------
    void game::loop(){
        while(!window->shouldClose()){
            
            if(m_Timer->check()){
                std::cerr << m_Timer->get() << "\n";
                m_Timer->reset();
            }
            m_Timer->update();
            
            m_pStateCurrent->loop();
        }
    }
    
    //--------------------------------------------------------------------------------
    gameStates* game::getStateGame(){
        return m_pStateGame.get();
    }
    
    //--------------------------------------------------------------------------------
    gameStates* game::getStateMenu(){
        return m_pStateMenu.get();
    }
    
    //--------------------------------------------------------------------------------
    gameStates* game::getStateOpenCL(){
        return m_pStateOpenCL.get();
    }
    
    //--------------------------------------------------------------------------------
    gameStates* game::getStateOpenCLComplex(){
        return m_pStateOpenCLComplex.get();
    }
}}
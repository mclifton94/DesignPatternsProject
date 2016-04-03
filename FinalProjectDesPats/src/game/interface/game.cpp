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
    std::shared_ptr<gameWindow> game::window( new gameWindow(800, 600, (char*)"Hello, World!", false ));
    
    //--------------------------------------------------------------------------------
    class gameStateGame;
    
    //--------------------------------------------------------------------------------
    game& game::getInstance(){
        static game instance;
        return instance;
    }

    //--------------------------------------------------------------------------------
    game::game()
    : m_pStateGame(new gameStateGame(window.get()))
    { setState(m_pStateGame); }
    
    //--------------------------------------------------------------------------------
    void game::setState(gameStates* state){
        m_pStateCurrent = state;
    }
    
    //--------------------------------------------------------------------------------
    void game::loop(){
        m_pStateCurrent->loop();
    }
}}
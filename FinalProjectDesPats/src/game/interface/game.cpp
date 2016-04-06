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
    {
        window.reset( new gameWindow(640, 480, (char*)"Game Window!", false ));
        m_pStateGame.reset(new gameStateGame(window.get()));
        setState(m_pStateGame.get());
    }
    
    //--------------------------------------------------------------------------------
    void game::setState(gameStates* state){
        m_pStateCurrent = state;
    }
    
    //--------------------------------------------------------------------------------
    void game::loop(){
        m_pStateCurrent->loop();
    }
}}
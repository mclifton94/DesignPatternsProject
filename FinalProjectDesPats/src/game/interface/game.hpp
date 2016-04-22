//
//  game.hpp
//  FinalProjectDesPats
//
//  Created by MarkClifton on 4/3/16.
//  Copyright © 2016 designPatterns. All rights reserved.
//

#pragma once

#include <iostream>
#include "gameStates.hpp"
#include "timer.hpp"

namespace cap { namespace state {
    using namespace cap;
    using namespace utils;
    
    class game {
    public:
        static game* getInstance();

    private:
        game();
        
        gameStates* m_pStateCurrent;
        std::shared_ptr<gameStates> m_pStateGame;
        std::shared_ptr<gameStates> m_pStateOpenCL;
        std::shared_ptr<gameStates> m_pStateOpenCLComplex;
        
    public:
        void loop();
        std::unique_ptr<graphics::gameWindow> window;
        std::unique_ptr<timer> m_Timer;
        
        void setState(gameStates* state);
        
        gameStates* getStateGame();
        gameStates* getStateOpenCL();
        gameStates* getStateOpenCLComplex();
    };

}}
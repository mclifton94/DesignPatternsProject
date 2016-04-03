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

namespace cap { namespace state {

    class game {
    public:
        static game& getInstance();
        
    private:
        game();
        
        gameStates* m_pStateCurrent;
        gameStates* m_pStateGame;
        
        void setState(gameStates* state);
        
    public:
        void loop();
        static std::shared_ptr<gameWindow> window;
    };

}}
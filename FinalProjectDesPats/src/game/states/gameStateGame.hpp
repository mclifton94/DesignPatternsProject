//
//  gameStateGame.hpp
//  FinalProjectDesPats
//
//  Created by MarkClifton on 4/3/16.
//  Copyright © 2016 designPatterns. All rights reserved.
//

#pragma once

#include <iostream>
#include "gameWindow.hpp"
#include "keyboard.hpp"
#include "mouse.hpp"
#include "timer.hpp"

#include "gameStates.hpp"

using namespace cap;
using namespace graphics;
using namespace input;
using namespace utils;

namespace cap { namespace state {
    
    class gameStateGame : public gameStates {
    public:
        gameStateGame(gameWindow*);
        
        void loop();
        void setWindow(gameWindow*);
    private:
        gameWindow* m_Window;
        std::unique_ptr<timer> m_Timer;
        
    };

}}
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
    class game;
    class gameStateGame : public gameStates {
    public:
        gameStateGame(gameWindow*, game*);
        
        void setup();
        void loop();
        void setWindow(gameWindow*);
        bool changeState();
    private:
        gameWindow* m_Window;
        game* m_Game;
        
    };

}}
//
//  gameStateOpenCL.hpp
//  FinalProjectDesPats
//
//  Created by Mark Clifton on 4/7/16.
//  Copyright © 2016 designPatterns. All rights reserved.
//

#pragma once

#include <iostream>
#include "gameWindow.hpp"
#include "keyboard.hpp"
#include "mouse.hpp"
#include "timer.hpp"

#include "ocl.hpp"

#include "gameStates.hpp"

using namespace cap;
using namespace graphics;
using namespace input;
using namespace utils;

namespace cap { namespace state {
    class game;
    class gameStateOpenCL : public gameStates {
    public:
        gameStateOpenCL(gameWindow*, game*);
        
        void loop();
        bool changeState();
        
    private:
        gameWindow* m_Window;
        game* m_Game;
    };
    
}}
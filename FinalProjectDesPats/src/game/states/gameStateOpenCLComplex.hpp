//
//  gameStateOpenCLComplex.hpp
//  FinalProjectDesPats
//
//  Created by MarkClifton on 4/10/16.
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
    class gameStateOpenCLComplex : public gameStates {
    public:
        gameStateOpenCLComplex(gameWindow*, game*);
        
        void loop();
        bool changeState();
        void getInput();
        
        float m_gravity;
        
    private:
        gameWindow* m_Window;
        game* m_Game;
        std::unique_ptr<timer> m_Timer;
        bool m_release;
    };
    
}}
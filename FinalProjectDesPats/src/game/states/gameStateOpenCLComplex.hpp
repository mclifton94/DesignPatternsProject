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

#include "shaderObject.hpp"
#include "point.hpp"
#include "rectangle.hpp"
#include "tools.hpp"

#include <vector>

#include "ocl.hpp"

#include "gameStates.hpp"

using namespace cap;
using namespace graphics;
using namespace input;
using namespace utils;
using namespace opencl;

namespace cap { namespace state {
    class game;
    class gameStateOpenCLComplex : public gameStates {
    public:
        gameStateOpenCLComplex(gameWindow*, game*);
        
        void setup();
        void loop();
        bool changeState();
        void getInput();
        
        float m_gravity;
        
    protected:
        int numPts = 64;
        cap::opencl::pt pt[64];
        std::vector<point> pts;
        cap::opencl::pt data[64];
        opencl::ocl o;
        
        cap::opencl::argument arg1;
        cap::opencl::argument arg2;
        cap::opencl::argument arg3;
        cap::opencl::argument arg4;
        
        cap::opencl::argument args[4];
        
        boundaries bounds;
        
    private:
        gameWindow* m_Window;
        game* m_Game;
        
        std::unique_ptr<shaderObject> m_shader;
        
        bool m_release;
    };
    
}}
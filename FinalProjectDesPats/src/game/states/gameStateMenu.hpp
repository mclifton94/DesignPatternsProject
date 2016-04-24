//
//  gameStateMenu.hpp
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

#include "texture.hpp"
#include "rectangle.hpp"
#include "gameStates.hpp"
#include "shaderObject.hpp"

#include <vector>

using namespace cap;
using namespace graphics;
using namespace input;
using namespace utils;

namespace cap { namespace state {
    class game;
    class gameStateMenu : public gameStates {
    public:
        gameStateMenu(gameWindow*, game*);
        ~gameStateMenu();
        
        void setup();
        void loop();
        void setWindow(gameWindow*);
        bool changeState();
    private:
        gameWindow* m_Window;
        game* m_Game;
        
        std::unique_ptr<rectangle> m_menuPicture;
        
        std::unique_ptr<shaderObject> m_shader;
        std::vector<texture*> m_textures;
        std::vector<GLuint> m_texIDs;
        
    };
    
}}
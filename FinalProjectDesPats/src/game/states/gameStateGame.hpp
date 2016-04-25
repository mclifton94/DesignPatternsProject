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

#include "shaderObject.hpp"
#include "audioTrack.hpp"
#include "textureManager.hpp"

#include "gameStates.hpp"

#include "DK.hpp"

using namespace cap;
using namespace graphics;
using namespace input;
using namespace utils;
using namespace DKGAME;
using namespace openal;

namespace cap { namespace state {
    class game;
    
    class gameStateGame : public gameStates {
    public:
        gameStateGame(gameWindow*, game*);
        
        void setup();
        void loop();
        void setWindow(gameWindow*);
        bool changeState();
        
        void handleInput();
    
    private:
        gameWindow* m_Window;
        game* m_Game;
        std::unique_ptr<shaderObject> m_shader;
        
        textureManager* m_texManager;
        pathToString m_txPath;
        
        float screenMin, screenMax;
        
        std::unique_ptr<audioTrack> m_menuMusic;
    private:
        std::unique_ptr<DK> player;
        std::unique_ptr<rectangle> background;
        
    };

}}
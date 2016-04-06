//
//  gameWindow.hpp
//  FinalProjectDesPats
//
//  Created by MarkClifton on 4/3/16.
//  Copyright © 2016 designPatterns. All rights reserved.
//

#pragma once 

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "keyboard.hpp"
#include "mouse.hpp"

namespace cap { namespace graphics {

    class gameWindow {
    //--------------------------------------------------------------------------------
    private:
        GLFWwindow* m_pWindow;
        std::unique_ptr<input::inputMouse> m_Mouse;
        std::unique_ptr<input::inputKeyboard> m_Keyboard;
        int m_height, m_width;
        bool m_vsync;
        char* m_title;
    //--------------------------------------------------------------------------------
    public:
        gameWindow(int, int, char*, bool );
        ~gameWindow();
        
        void close() const;
        bool shouldClose() const;
        void setActive() const;
        
        void setSize( int, int);
        void setTitle( char*);
        virtual void setProperties();
        
        GLFWwindow* getWindowID() const;
        
        void clear();
        void swap();
    };
    
}}
//
//  keyboard.hpp
//  FinalProjectDesPats
//
//  Created by MarkClifton on 4/3/16.
//  Copyright © 2016 designPatterns. All rights reserved.
//

#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <map>

namespace cap { namespace input {
    
    typedef std::map<int, bool> Keys;
    
    class inputKeyboard {
    public:
        static Keys keysPressed;
        static Keys keysHeld;
        
    private:
        GLFWwindow* m_pWindow;
        
    public:
        
        inputKeyboard(GLFWwindow* Window)
        : m_pWindow(Window)
        {
            glfwSetKeyCallback(m_pWindow, callback);
        }
        
        static void callback(GLFWwindow* window, int key, int scancode, int action, int mods) ;
        
        GLFWwindow* getWindow(){ return m_pWindow; }
    };
    
}}
//
//  mouse.hpp
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
    
    typedef std::map<int, bool> Buttons;
    
    class inputMouse {
    public:
        static Buttons buttonPressed;
        static float x, y;
    private:
        
        GLFWwindow* m_window;
    public:
        inputMouse(GLFWwindow* Window)
        : m_window(Window)
        {
            glfwSetMouseButtonCallback(m_window, cbClick);
            glfwSetCursorPosCallback(m_window, cbPosition);
        }
        
        static void cbPosition(GLFWwindow* window, double x_value, double y_value);
        static void cbClick(GLFWwindow* window, int button, int action, int mod);
        
        inline float getX() const { return x; }
        inline float getY() const { return y; }
    };
    
}}
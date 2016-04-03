//
//  mouse.cpp
//  FinalProjectDesPats
//
//  Created by MarkClifton on 4/3/16.
//  Copyright © 2016 designPatterns. All rights reserved.
//

#include "mouse.hpp"

namespace cap { namespace input {

    //--------------------------------------------------------------------------------
    Buttons inputMouse::buttonPressed;
    float inputMouse::x, inputMouse::y;
    
    //--------------------------------------------------------------------------------
    void inputMouse::cbClick(GLFWwindow *window, int button, int action, int mod){
        if(action == GLFW_PRESS){
            buttonPressed[button] = true;
            std::cerr << button << " Pressed! at: " << x << ", " << y << ".\n";
        }else if(action == GLFW_RELEASE){
            buttonPressed[button] = false;
            std::cerr << button << " Released! at: " << x << ", " << y << ".\n";
        }
    }
    
    //--------------------------------------------------------------------------------
    void inputMouse::cbPosition(GLFWwindow* window, double x_value, double y_value){
        x = x_value;
        y = y_value;
    }

}}
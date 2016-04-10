//
//  keyboard.cpp
//  FinalProjectDesPats
//
//  Created by MarkClifton on 4/3/16.
//  Copyright © 2016 designPatterns. All rights reserved.
//

#include "keyboard.hpp"

namespace cap { namespace input {

    //--------------------------------------------------------------------------------
    Keys inputKeyboard::keysPressed;
    Keys inputKeyboard::keysHeld;
    
    //--------------------------------------------------------------------------------
    void inputKeyboard::callback(GLFWwindow* window, int key, int scancode, int action, int mods){
        if( action == GLFW_RELEASE){
            keysPressed[key] = false;
            keysHeld[key] = false;
            //std::cerr << key << " released!\n";
        }else if( action == GLFW_PRESS){
            keysPressed[key] = true;
            //std::cerr << key << " pressed!\n";
        }else{
            keysHeld[key] = true;
            //std::cerr << key << " held!\n";
        }
        
        if( action == GLFW_PRESS && key == GLFW_KEY_Q){
            glfwSetWindowShouldClose(window, GL_TRUE);
        }
    }

}}
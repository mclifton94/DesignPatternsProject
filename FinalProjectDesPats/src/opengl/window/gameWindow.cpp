//
//  gameWindow.cpp
//  FinalProjectDesPats
//
//  Created by MarkClifton on 4/3/16.
//  Copyright © 2016 designPatterns. All rights reserved.
//

#include "gameWindow.hpp"

namespace cap { namespace graphics {
    
    //--------------------------------------------------------------------------------
    gameWindow::gameWindow( int Width, int Height, char* Title, bool vsync )
    : m_width(Width), m_height(Height), m_title(Title), m_vsync(vsync)
    {
        
        if( !glfwInit() ){
            std::cerr << "Failed to init GLFW!\n";
        }
        else{
            
            setProperties();
            
            m_vsync == true ? glfwSwapInterval(1) : glfwSwapInterval(0);
            
            glewExperimental = GL_TRUE;
            if(glewInit() != GLEW_OK){
                std::cerr << "Failed to init GLEW!\n";
            }
            
            m_Keyboard.reset(new input::inputKeyboard(getWindowID()));
            m_Mouse.reset(new input::inputMouse(getWindowID()));
        }
    }
    //--------------------------------------------------------------------------------
    gameWindow::~gameWindow(){ close(); }
    
    //--------------------------------------------------------------------------------
    void gameWindow::close() const {
        glfwMakeContextCurrent(NULL);
        glfwDestroyWindow(m_pWindow);
        glfwTerminate();
    }

    //--------------------------------------------------------------------------------
    /*
     * If overrided, must provide window hints, create window, and any context properties
     */
    void gameWindow::setProperties(){
        glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 2);
        glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        
        m_pWindow = glfwCreateWindow(m_width, m_height, m_title, NULL, NULL);
        
        if (!m_pWindow)
        {
            glfwTerminate();
            std::cerr << "Failed to create Window!\n";
        }
        
        glfwMakeContextCurrent(m_pWindow);
        
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }
    
    //--------------------------------------------------------------------------------
    bool gameWindow::shouldClose() const { return glfwWindowShouldClose(m_pWindow); }

    //--------------------------------------------------------------------------------
    void gameWindow::setActive() const { glfwMakeContextCurrent(m_pWindow); }
    
    //--------------------------------------------------------------------------------
    void gameWindow::setSize( int Width, int Height ){
        m_width = Width;
        m_height = Height;
    }
    
    //--------------------------------------------------------------------------------
    void gameWindow::setTitle( char* Title ){ m_title = Title; }
    
    //--------------------------------------------------------------------------------
    GLFWwindow* gameWindow::getWindowID() const { return m_pWindow; }
    
    //--------------------------------------------------------------------------------
    void gameWindow::clear(){ glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); }
    
    //--------------------------------------------------------------------------------
    void gameWindow::swap(){ glfwSwapBuffers(m_pWindow); }
    
}}
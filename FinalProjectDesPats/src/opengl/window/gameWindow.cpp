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
            
            glfwWindowHint(GLFW_SAMPLES, 4);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
            
            m_pWindow = glfwCreateWindow(m_width, m_height, m_title, NULL, NULL);
            
            // set it to be the current OpenGL context
            glfwMakeContextCurrent(m_pWindow);
            
            // Initialize GLEW
            // global variable declared in GLEW files
            glewExperimental = true; // Needed for core profile
            if (glewInit() != GLEW_OK) {
                std::cerr << "failed to initialize GLEW\n";
                exit(EXIT_FAILURE);
            }
            
            // specify refresh rate (normally 1)
            glfwSwapInterval( vsync ? 1 : 0 );
            
            glEnable(GL_DEPTH_TEST);
            
            m_Keyboard.reset(new input::inputKeyboard(getWindowID()));
            m_Mouse.reset(new input::inputMouse(getWindowID()));
            
            glGenVertexArrays(1, &m_vao);
            glBindVertexArray(m_vao);
        }
    }
    //--------------------------------------------------------------------------------
    gameWindow::~gameWindow(){ close(); }
    
    //--------------------------------------------------------------------------------
    void gameWindow::close() const {
        glDeleteVertexArrays(1, &m_vao);
        glfwMakeContextCurrent(NULL);
        glfwDestroyWindow(m_pWindow);
        glfwTerminate();
    }

    //--------------------------------------------------------------------------------
    /*
     * If overrided, must provide window hints, create window, and any context properties
     */
    void gameWindow::setProperties(){
        
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
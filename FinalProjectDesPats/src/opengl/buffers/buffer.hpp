//
//  buffer.hpp
//  FinalProjectDesPats
//
//  Created by Mark Clifton on 4/4/16.
//  Copyright © 2016 designPatterns. All rights reserved.
//

#pragma once 

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "baseObject.hpp"

namespace cap { namespace graphics {
    struct vertex;
    
    class bufferObject {
    private:
        GLuint m_buffer, m_type;
    public:
        bufferObject(GLuint);
        ~bufferObject();
        
        void genBuffer();
        void bindBuffer();
        void unbindBuffer();
        void bufferData(GLsizei, int, vertex*, GLuint);
        GLuint getID() const { return m_buffer; }
    };
}}
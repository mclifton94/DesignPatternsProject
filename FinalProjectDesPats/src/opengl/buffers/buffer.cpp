//
//  buffer.cpp
//  FinalProjectDesPats
//
//  Created by Mark Clifton on 4/4/16.
//  Copyright © 2016 designPatterns. All rights reserved.
//

#include "buffer.hpp"

namespace cap { namespace graphics {
    
    //--------------------------------------------------------------------------------
    bufferObject::bufferObject( GLuint typeOfBuffer)
    : m_type(typeOfBuffer), m_buffer(0)
    {}
    
    //--------------------------------------------------------------------------------
    bufferObject::~bufferObject(){
        if(m_buffer != 0)
            glDeleteBuffers(1, &m_buffer);
    }
    
    //--------------------------------------------------------------------------------
    void bufferObject::genBuffer(){
        glGenBuffers(1, &m_buffer);
    }
    
    //--------------------------------------------------------------------------------
    void bufferObject::bindBuffer(){
        glBindBuffer(m_type, m_buffer);
    }
    
    //--------------------------------------------------------------------------------
    void bufferObject::unbindBuffer(){
        glBindBuffer(m_type, 0);
    }
    
    //--------------------------------------------------------------------------------
    void bufferObject::bufferData(GLsizei count, int sizeOfElement, vertex* Elements, GLuint drawType){
        glBufferData(m_type, count * sizeOfElement, Elements, drawType);
    }
    
}}
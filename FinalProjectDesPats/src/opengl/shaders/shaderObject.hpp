//
//  shaderObject.hpp
//  FinalProjectDesPats
//
//  Created by Mark Clifton on 4/4/16.
//  Copyright © 2016 designPatterns. All rights reserved.
//

#pragma once 

#include <GL/glew.h>

#include "Angel.h"
#include "fileReader.hpp"

namespace cap { namespace graphics {
  
    class shaderObject {
    private:
        utils::fileReader m_reader;
        GLuint m_program;
        
        GLuint m_vs, m_fs;
        std::string m_vsPath, m_fsPath;
    public:
        shaderObject(std::string, std::string);
        ~shaderObject();
        
        inline void enable() const { glUseProgram(m_program); }
        inline void disable() const { glUseProgram(0); }
        inline GLuint get() const { return m_program; }
        
        bool load(std::string, int, GLuint&);
        
        GLint getUniformLocation(const GLchar* name);
        
        //--------------------------------------------------------------------------------
        void setUniform1f(const GLchar* name, float value);
        void setUniform1fv(const GLchar* name, float* value, int count);
        void setUniform1i(const GLchar* name, int value);
        void setUniform1iv(const GLchar* name, int* value, int count);
        void setUniform2f(const GLchar* name, const vec2& vector);
        void setUniform3f(const GLchar* name, const vec3& vector);
        void setUniform4f(const GLchar* name, const vec4& vector);
        void setUniformMat4(const GLchar* name, const mat4& matrix);
    };
    
}}

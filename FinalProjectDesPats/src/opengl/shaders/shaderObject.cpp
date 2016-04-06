//
//  shaderObject.cpp
//  FinalProjectDesPats
//
//  Created by Mark Clifton on 4/4/16.
//  Copyright © 2016 designPatterns. All rights reserved.
//

#include "shaderObject.hpp"
#include <vector>

namespace cap { namespace graphics {
    
    shaderObject::shaderObject(std::string vertexShader, std::string fragmentShader)
    : m_vsPath(vertexShader), m_fsPath(fragmentShader)
    {
        m_program =  glCreateProgram();
        load(m_vsPath, GL_VERTEX_SHADER, m_vs);
        load(m_fsPath, GL_FRAGMENT_SHADER, m_fs);
        
        glAttachShader(m_program, m_vs);
        glAttachShader(m_program, m_fs);
        
        glLinkProgram(m_program);
        GLint linked;
        glGetProgramiv(m_program, GL_LINK_STATUS, &linked);
        
        // error checking
        if (!linked) {
            std::cerr << "Shader program failed to link" << std::endl;
            
            GLint  logSize;
            glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &logSize);
            if (logSize > 0) {
                char* logMsg = new char[logSize];
                glGetProgramInfoLog(m_program, logSize, NULL, logMsg);
                std::cerr << logMsg << std::endl;
                delete [] logMsg;
            }
        }
        
        glValidateProgram(m_program);
        
        glDeleteShader(m_vs);
        glDeleteShader(m_fs);
    }
    
    shaderObject::~shaderObject(){
        glDeleteProgram(m_program);
    }
    
    bool shaderObject::load(std::string path, int shaderType, GLuint& shader){
        if(!m_reader.open(path)){
            std::cerr << "Failed to open " << path << "\n";
            return false;
        }
        
        std::string contents = "";
        
        unsigned char c;
        while(m_reader.read(c)){
            contents += c;
        }
        
        m_reader.close();
        
        shader = glCreateShader(shaderType);
        const char* c_str = contents.c_str();
        glShaderSource(shader, 1, &c_str, NULL);
        
        glCompileShader(shader);
        
        GLint result;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
        if (result == GL_FALSE)
        {
            GLint length;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
            std::vector<char> error(length);
            glGetShaderInfoLog(shader, length, &length, &error[0]);
            std::cout << "Failed to compile " << shaderType << " shader!" << std::endl << &error[0] << std::endl;
            glDeleteShader(shader);
            return 0;
        }
        
        return true;
    }
    
    GLint shaderObject::getUniformLocation(const GLchar* name)
    {
        return glGetUniformLocation(m_program, name);
    }
    
    void shaderObject::setUniform1f(const GLchar* name, float value)
    {
        glUniform1f(getUniformLocation(name), value);
    }
    void shaderObject::setUniform1fv(const GLchar* name, float* value, int count)
    {
        glUniform1fv(getUniformLocation(name), count, value);
    }
    
    void shaderObject::setUniform1i(const GLchar* name, int value)
    {
        glUniform1i(getUniformLocation(name), value);
    }
    
    void shaderObject::setUniform1iv(const GLchar* name, int* value, int count)
    {
        glUniform1iv(getUniformLocation(name), count, value);
    }
    
    void shaderObject::setUniform2f(const GLchar* name, const vec2& vector)
    {
        glUniform2f(getUniformLocation(name), vector[0], vector[1]);
    }
    
    void shaderObject::setUniform3f(const GLchar* name, const vec3& vector)
    {
        glUniform3f(getUniformLocation(name), vector[0], vector[1], vector[2]);
    }
    
    void shaderObject::setUniform4f(const GLchar* name, const vec4& vector)
    {
        glUniform4f(getUniformLocation(name), vector[0], vector[1], vector[2], vector[3]);
    }
    
    void shaderObject::setUniformMat4(const GLchar* name, const mat4& matrix)
    {
        glUniformMatrix4fv(getUniformLocation(name), 16, GL_TRUE, matrix);
    }
    
}}
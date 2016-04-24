//
//  texture.cpp
//  FinalProjectDesPats
//
//  Created by MarkClifton on 4/24/16.
//  Copyright © 2016 designPatterns. All rights reserved.
//

#include "texture.hpp"
#include "textureLoad.hpp"

namespace cap { namespace graphics {
    
    texture::texture(const std::string& Filename)
    : m_filename(Filename)
    {
        m_texID = loadTexture();
    }
    
    texture::~texture() {
        glDeleteTextures(GL_TEXTURE_2D, &m_texID);
    }
    
    GLuint texture::loadTexture(){
        BYTE* pixels = loadTexture::load_Texture(m_filename.c_str(), &m_width, &m_height);
        
        GLuint result;
        glGenTextures(1, &result);
        glBindTexture(GL_TEXTURE_2D, result);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_BGRA, GL_UNSIGNED_BYTE, pixels);
        glBindTexture(GL_TEXTURE_2D, 0);
        
        return result;
    }
    
    void texture::bind() const {
        glBindTexture(GL_TEXTURE_2D, m_texID);
    }
    
    void texture::unbind() const {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    
    GLsizei texture::getWidth() const {
        return m_width;
    }
    
    GLsizei texture::getHeight() const {
        return m_height;
    }
    
    GLuint texture::getID() const {
        return m_texID;
    }
    
}}
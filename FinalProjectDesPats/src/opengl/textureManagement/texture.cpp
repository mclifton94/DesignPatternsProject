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
    
    //--------------------------------------------------------------------------------
    texture::texture(const std::string& Filename, int loadWith)
    : m_filename(Filename)
    {
        if(!loadWith){
            loadTexture();
        }else{
            loadTexture2();
        }
    }
    
    //--------------------------------------------------------------------------------
    texture::~texture() {
        glDeleteTextures(GL_TEXTURE_2D, &m_texID);
    }
    
    //--------------------------------------------------------------------------------
    void texture::loadTexture(){
        BYTE* pixels = loadTexture::load_Texture(m_filename.c_str(), &m_width, &m_height);
        
        glGenTextures(1, &m_texID);
        glBindTexture(GL_TEXTURE_2D, m_texID);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_BGRA, GL_UNSIGNED_BYTE, pixels);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    
    //--------------------------------------------------------------------------------
    void texture::loadTexture2(){
        BYTE* pixels = loadTexture::load_Texture(m_filename.c_str(), &m_width, &m_height);
        
        glGenTextures(1, &m_texID);
        glBindTexture(GL_TEXTURE_2D, m_texID);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_BGR, GL_UNSIGNED_BYTE, pixels);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    
    //--------------------------------------------------------------------------------
    void texture::bind() const {
        glBindTexture(GL_TEXTURE_2D, m_texID);
    }
    
    //--------------------------------------------------------------------------------
    void texture::unbind() const {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    
    //--------------------------------------------------------------------------------
    GLsizei texture::getWidth() const {
        return m_width;
    }
    
    //--------------------------------------------------------------------------------
    GLsizei texture::getHeight() const {
        return m_height;
    }
    
    //--------------------------------------------------------------------------------
    GLuint texture::getID() const {
        return m_texID;
    }
    
}}
//
//  texture.hpp
//  FinalProjectDesPats
//
//  Created by MarkClifton on 4/24/16.
//  Copyright © 2016 designPatterns. All rights reserved.
//

#pragma once

#include <string>
#include <GL/glew.h>

namespace cap { namespace graphics {
  
    class texture {
    private:
        std::string m_filename;
        GLuint m_texID;
        GLsizei m_width;
        GLsizei m_height;
        
        GLuint loadTexture();
        
    public:
        texture(const std::string&);
        ~texture();
        
        void bind() const;
        void unbind() const;
        
        GLsizei getWidth() const;
        GLsizei getHeight() const;
        GLuint getID() const;
    };
    
}}
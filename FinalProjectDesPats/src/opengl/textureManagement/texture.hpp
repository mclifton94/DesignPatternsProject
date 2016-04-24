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
    protected:
        std::string m_filename;
    private:
        GLuint m_texID;
        GLsizei m_width;
        GLsizei m_height;
        
        void loadTexture();
        
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
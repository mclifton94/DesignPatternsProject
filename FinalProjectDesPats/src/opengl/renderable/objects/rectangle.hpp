//
//  rectangle.hpp
//  FinalProjectDesPats
//
//  Created by Mark Clifton on 4/4/16.
//  Copyright © 2016 designPatterns. All rights reserved.
//

#pragma once

#include "baseObject.hpp"
#include "baseObjectActions.hpp"

namespace cap { namespace graphics {
    
    class rectangle : public baseObject, public baseObjectActions {
    private:
        vec4 m_color;
        vec2 m_size;
        
        GLuint _buffer;
        GLuint _vao;
        GLfloat arr[18];
        
    public:
        rectangle(vec2, vec3);
        
        void buffer();
        void rebuffer();
        
        void draw();
        void setup();
        
        void setColor(vec4);
        vec4 getColor();
        
        void setVelocity(float);
        float getVelocity();
        
        void setMass(float);
        float getMass();
        
        void setDirection(vec3);
        vec3 getDirection();
    };
    
}}
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
#include "spriteTextures.hpp"

namespace cap { namespace graphics {
    
    class rectangle : public baseObject, public baseObjectActions {
    private:
        vec4 m_color;
        vec2 m_size;
        texCoords m_coords;
        
    public:
        rectangle(vec2, vec3);
        
        void buffer();
        
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
        
        void setPosition(vec3);
        vec3 getPosition() const;
        
        void setTexture(texture*);
        void setTexID(float);
        
        void setTexCoords(texCoords);
        texCoords getTexCoords() const;
        
        rectangle* clone();
    };
    
}}
//
//  point.hpp
//  FinalProjectDesPats
//
//  Created by MarkClifton on 4/10/16.
//  Copyright © 2016 designPatterns. All rights reserved.
//

#pragma once

#include "baseObject.hpp"
#include "baseObjectActions.hpp"

#include "ocl.hpp"

namespace cap { namespace graphics {
    
    class point : public baseObject, public baseObjectActions {
        
    public:
        vec4 m_color;
        //position
        point(vec3);
        
        void buffer();
        
        void draw();
        void setup();
        
        void setColor(vec4);
        vec4 getColor();
        
        void setPosition(vec3);
        vec3 getPosition();
        
        void setVelocity(float);
        float getVelocity();
        
        void setMass(float);
        float getMass();
        
        void setDirection(vec3);
        vec3 getDirection();
    };
    
}}
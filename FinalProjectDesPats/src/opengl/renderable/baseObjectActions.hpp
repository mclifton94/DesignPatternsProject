//
//  baseObjectActions.hpp
//  FinalProjectDesPats
//
//  Created by Mark Clifton on 4/4/16.
//  Copyright © 2016 designPatterns. All rights reserved.
//

#pragma once 

class baseObjectActions {
public:
    virtual void buffer() = 0;
    virtual void draw() = 0;
    virtual void setup() = 0;
    
    virtual void setColor(vec4) = 0;
    virtual vec4 getColor() = 0;
    
    virtual void setVelocity(float) = 0;
    virtual float getVelocity() = 0;
    
    virtual void setMass(float) = 0;
    virtual float getMass() = 0;
    
    virtual void setDirection(vec3) = 0;
    virtual vec3 getDirection() = 0;
    
    virtual cap::graphics::baseObject* clone() = 0;
};

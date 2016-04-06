//
//  baseObject.cpp
//  FinalProjectDesPats
//
//  Created by Mark Clifton on 4/4/16.
//  Copyright © 2016 designPatterns. All rights reserved.
//

#include "baseObject.hpp"

namespace cap { namespace graphics {
 
    baseObject::baseObject()
    : m_direction(vec3(0,0,0)), m_velocity(0.0), m_mass(0.0)
    {}
    
}}
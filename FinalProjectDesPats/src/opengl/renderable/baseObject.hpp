//
//  baseObject.hpp
//  FinalProjectDesPats
//
//  Created by Mark Clifton on 4/4/16.
//  Copyright © 2016 designPatterns. All rights reserved.
//

#pragma once

#include "Angel.h"
#include "buffer.hpp"

namespace cap { namespace graphics {
    
    struct vertex {
        vec3 position;
        vec4 color;
    };
    
    class bufferObject;
    
    class baseObject {
    public:
        vec3 m_position;
        vec3 m_direction;
        float m_velocity;
        float m_mass;
        
        std::unique_ptr<vertex[]> m_vertices;
        std::unique_ptr<bufferObject> m_buffer;
        
    public:
        baseObject();
        
    };
    
}}
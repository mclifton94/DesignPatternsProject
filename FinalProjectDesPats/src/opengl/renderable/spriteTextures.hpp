//
//  spriteTextures.h
//  FinalProjectDesPats
//
//  Created by MarkClifton on 4/24/16.
//  Copyright © 2016 designPatterns. All rights reserved.
//

#pragma once 

#include "Angel.h"

#include <map>

namespace cap { namespace graphics {
    
    class texCoords {
    public:
        vec2 tl;
        vec2 tr;
        vec2 bl;
        vec2 br;
        
        texCoords(vec2 topLeft, vec2 bottomRight){
            tl = topLeft;
            br = bottomRight;
            bl = vec2(tl.x, br.y);
            tr = vec2(br.x, tl.y);
        }
        
        texCoords(){}
    };
    
    struct texSearchResult {
        bool isFound;
        texCoords coords;
    };
    
    typedef std::map<int, texCoords> spriteMap;
    
    class spriteTextures {
    protected:
        spriteMap m_map;
    public:
        spriteTextures();
        ~spriteTextures();
        
        texSearchResult getCoordsFor(int);
        bool addCoordsFor(int, texCoords);
    };

}}
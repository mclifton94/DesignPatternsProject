//
//  spriteTextures.cpp
//  FinalProjectDesPats
//
//  Created by MarkClifton on 4/24/16.
//  Copyright © 2016 designPatterns. All rights reserved.
//

#include "spriteTextures.hpp"

namespace cap { namespace graphics {
    
    //--------------------------------------------------------------------------------
    spriteTextures::spriteTextures(){
    }
    
    //--------------------------------------------------------------------------------
    spriteTextures::~spriteTextures(){
    }
    
    //--------------------------------------------------------------------------------
    texSearchResult spriteTextures::getCoordsFor(int CoordValue){
        texSearchResult search;
        search.isFound = false;
        if(m_map.count(CoordValue)){
            search.coords = m_map[CoordValue];
            search.isFound = true;
        }
        return search;
    }
    
    //--------------------------------------------------------------------------------
    bool spriteTextures::addCoordsFor(int CoordValue, texCoords uv){
        if(!m_map.count(CoordValue)){
            m_map[CoordValue] = uv;
        }
        
        return false;
    }
    
}}
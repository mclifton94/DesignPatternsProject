//
//  DK.cpp
//  FinalProjectDesPats
//
//  Created by MarkClifton on 4/24/16.
//  Copyright © 2016 designPatterns. All rights reserved.
//

#include "DK.hpp"
namespace DKGAME {

    DK::DK(vec2 size, vec3 position)
    : rectangle(size, position)
    {
        m_map[STANDING0] = texCoords(vec2(.0055,.99), vec2(.0315,.97));
        m_map[STANDING1] = texCoords(vec2(.0358,.99), vec2(.0618,.97));
        m_map[STANDING2] = texCoords(vec2(.0643,.99), vec2(.0903,.97));
        m_map[STANDING3] = texCoords(vec2(.0930,.99), vec2(.1190,.97));
        m_map[STANDING4] = texCoords(vec2(.1208,.99), vec2(.1468,.97));
        m_map[STANDING5] = texCoords(vec2(.1488,.99), vec2(.1748,.97));
        m_map[STANDING6] = texCoords(vec2(.1765,.99), vec2(.2025,.97));
        m_map[STANDING7] = texCoords(vec2(.2042,.9908), vec2(.2302,.9708));
        m_map[STANDING8] = texCoords(vec2(.2320,.9908), vec2(.2580,.9708));
        m_map[STANDING9] = texCoords(vec2(.2605,.9908), vec2(.2865,.9708));
        m_map[STANDING10] = texCoords(vec2(.2890,.9908), vec2(.3150,.9708));
        
        standCount = 0; standTimer = 0;
        increment = 1;
    }

    void DK::standing(){
        if(standTimer > 5){
            standCount += increment;
            standTimer = 0;
        }
        standTimer += 1;
        
        if(standCount > 10){
            increment = -1;
            standCount = 9;
        }else if(standCount < 0){
            increment = 1;
            standCount = 1;
        }
        
        setTexCoords(m_map[standCount%11]);
    }
}
//
//  DK.hpp
//  FinalProjectDesPats
//
//  Created by MarkClifton on 4/24/16.
//  Copyright © 2016 designPatterns. All rights reserved.
//

#pragma once 

#include "rectangle.hpp"
#include "spriteTextures.hpp"

using namespace cap;
using namespace graphics;

namespace DKGAME {
    
    enum _DK_ {
        STANDING0 = 0,
        STANDING1 = 1,
        STANDING2 = 2,
        STANDING3 = 3,
        STANDING4 = 4,
        STANDING5 = 5,
        STANDING6 = 6,
        STANDING7 = 7,
        STANDING8 = 8,
        STANDING9 = 9,
        STANDING10 = 10
    };

    class DK : public rectangle, spriteTextures {
    private:
        int standCount, standTimer;
        int moveCount;
        int increment;
    public:
        DK(vec2, vec3);
        
        void standing();
    };

}


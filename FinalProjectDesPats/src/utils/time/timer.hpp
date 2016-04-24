//
//  timer.hpp
//  FinalProjectDesPats
//
//  Created by MarkClifton on 4/3/16.
//  Copyright © 2016 designPatterns. All rights reserved.
//

#pragma once 

#include <time.h>

namespace cap { namespace utils {
    
    class timer {
    public:
        timer()
        : counter(0)
        {}
        
        inline void reset(){ counter = 0; time(&startInterval);}
        inline int get() const {return counter; }
        inline void update() { counter++; }
        inline bool check() { time(&endInterval); return(endInterval - startInterval) > 1; }
    
    private:
        time_t startInterval, endInterval;
        float current;
        int counter;
    };
    
}}
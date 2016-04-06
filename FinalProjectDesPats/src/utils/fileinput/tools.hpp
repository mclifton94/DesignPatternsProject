//
//  tools.hpp
//  FinalProjectDesPats
//
//  Created by Mark Clifton on 4/4/16.
//  Copyright © 2016 designPatterns. All rights reserved.
//

#pragma once

#include <unistd.h>

namespace cap { namespace utils {
    
    class tools {
    public:
        static std::string getEnv(std::string path){
            char temp[256];
            getcwd(temp, 256) ? std::string( temp ) : std::string("");
            return temp+path;
        }
    };
    
}}

//
//  fileReader.hpp
//  FinalProjectDesPats
//
//  Created by Mark Clifton on 4/4/16.
//  Copyright © 2016 designPatterns. All rights reserved.
//

#pragma once 

#include <cstdio>
#include <string>

namespace cap { namespace utils {
    
    class fileReader {
    private:
        char* _fp = nullptr;
        FILE* _file = nullptr;
    public:
        fileReader();
        
        bool open(std::string filename);
        bool close();
        bool read(unsigned char &val);
    };
    
}}
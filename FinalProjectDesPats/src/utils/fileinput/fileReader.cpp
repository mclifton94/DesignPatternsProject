//
//  fileReader.cpp
//  FinalProjectDesPats
//
//  Created by Mark Clifton on 4/4/16.
//  Copyright © 2016 designPatterns. All rights reserved.
//

#include "fileReader.hpp"

namespace cap { namespace utils {
    
    //--------------------------------------------------------------------------------
    fileReader::fileReader()
    {}
    
    //--------------------------------------------------------------------------------
    bool fileReader::open(std::string filename){
        _file = fopen(filename.c_str(), "r");
        return (_file != NULL);
    }
    
    //--------------------------------------------------------------------------------
    bool fileReader::close(){
        return fclose(_file) == 0;
    }
    
    //--------------------------------------------------------------------------------
    bool fileReader::read(unsigned char &val){
        return (fread(&val, sizeof(unsigned char), 1, _file) == 1);
    }
    
}}
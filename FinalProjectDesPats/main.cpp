//
//  main.cpp
//  FinalProjectDesPats
//
//  Created by Mark Clifton on 3/28/16.
//  Copyright © 2016 designPatterns. All rights reserved.
//

#include "game.hpp"
#include "ocl.hpp"

#include "tools.hpp"

#define DATA_SIZE (64*64)

using namespace cap;
using namespace opencl;
using namespace state;

auto main(int argc, const char * argv[]) -> int {

    
    float data[DATA_SIZE];
    float results[DATA_SIZE];
    
    unsigned int correct;
    
    for(int i = 0; i < DATA_SIZE; i++){
        data[i] = 1;
    }
    
    ocl o(DEVICE::CPU);
    o.setup(utils::tools::getEnv("/FinalProjectDesPats/res/kernels/kernel.cl").c_str(), (char*)"square", DATA_SIZE, data);
    o.wait();
    o.getResults(results);
        
    for(int i = 0; i < DATA_SIZE; i++)
    {
        if(results[i] == data[i] * data[i])
            correct++;
    }
    
    printf("Computed '%d/%d' correct values!\n", correct, DATA_SIZE);
    
    game* g = game::getInstance();
    g->loop();

    return 0;
}

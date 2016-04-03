//
//  main.cpp
//  FinalProjectDesPats
//
//  Created by Mark Clifton on 3/28/16.
//  Copyright © 2016 designPatterns. All rights reserved.
//

#include "game.hpp"
#include "ocl.hpp"

#define DATA_SIZE (4096*128)

using namespace cap;
using namespace opencl;
using namespace state;

const char *KernelSource = "\n" \
"__kernel void square(                                                       \n" \
"   __global float* input,                                              \n" \
"   __global float* output,                                             \n" \
"   const unsigned int count)                                           \n" \
"{                                                                      \n" \
"   int i = get_global_id(0);                                           \n" \
"   if(i < count)                                                       \n" \
"       output[i] = input[i] * input[i];                                \n" \
"}                                                                      \n" \
"\n";

auto main(int argc, const char * argv[]) -> int {
    
    float data[DATA_SIZE];
    float results[DATA_SIZE];
    
    unsigned int correct;
    
    for(int i = 0; i < DATA_SIZE; i++){
        data[i] = 1;
    }
    
    ocl o(false);
        o.getProgram(&KernelSource);
    o.getProgramExec();
    o.getKernel((char*)"square");
    o.getInputOutput(DATA_SIZE);
    o.writeInput(data);
    o.setArguments();
    o.getWorkGroupAndExec();
    o.wait();
    o.getResults(results);
        
    for(int i = 0; i < DATA_SIZE; i++)
    {
        if(results[i] == data[i] * data[i])
            correct++;
    }
    
    printf("Computed '%d/%d' correct values!\n", correct, DATA_SIZE);
    
    game g = game::getInstance();
    
    g.loop();

    return 0;
}

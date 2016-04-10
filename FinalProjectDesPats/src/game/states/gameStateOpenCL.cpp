//
//  gameStateOpenCL.cpp
//  FinalProjectDesPats
//
//  Created by Mark Clifton on 4/7/16.
//  Copyright © 2016 designPatterns. All rights reserved.
//

#include "gameStateOpenCL.hpp"
#include "game.hpp"

#include "tools.hpp"

#define DATA_SIZE (64*64)


namespace cap { namespace state {
    
    gameStateOpenCL::gameStateOpenCL(gameWindow* window, game* game)
    : m_Window(window), m_Game(game)
    {}
    
    void gameStateOpenCL::loop(){
        std::cout << "OPENCL STATE!\n";
        
        float data[DATA_SIZE];
        for(int i=0; i<DATA_SIZE; i++){
            data[i] = rand()%100-50;
        }
        cap::opencl::results results[DATA_SIZE];
        
        opencl::ocl o(opencl::DEVICE::GPU);
        o.setup(cap::utils::tools::getEnv("/FinalProjectDesPats/res/kernels/MaxContSub.cl").c_str(), (char*)"maxSub", DATA_SIZE, data);
        
        //Number of threads
        cap::opencl::argument arg1;
        arg1.sizeOf = sizeof(unsigned int);
        arg1.actualParam = new int(DATA_SIZE/1024);
        
        //Number of items in array
        cap::opencl::argument arg2;
        arg2.sizeOf = sizeof(unsigned int);
        arg2.actualParam = new int(DATA_SIZE);
        
        cap::opencl::argument args[2] = {arg1, arg2};
        
        o.setArguments(2, args);
        o.getWorkGroupAndExec();
        o.wait();
        o.getResults(results);
        
        for(int i = 0; i < DATA_SIZE/1024; i++)
        {
            std::cout << results[i].start << " " << results[i].end << " " << results[i].value << "\n";
        }
        
        glfwSetWindowShouldClose(m_Window->getWindowID(), true);
        return;
    }
    
    bool gameStateOpenCL::changeState(){
        return false;
    }
    
}}
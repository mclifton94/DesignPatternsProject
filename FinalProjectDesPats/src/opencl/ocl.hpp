//
//  ocl.hpp
//  FinalProjectDesPats
//
//  Created by MarkClifton on 4/3/16.
//  Copyright © 2016 designPatterns. All rights reserved.
//

#pragma once

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <OpenCL/opencl.h>

#include "fileReader.hpp"

namespace cap { namespace opencl {
    enum DEVICE {
        CPU = 0,
        GPU = 1
    };
    
    struct argument {
        int sizeOf;
        void* actualParam;
        
    };
    
    struct results {
        int start;
        int end;
        int value;
    };
    
    class ocl {
    private:
        int err;
        unsigned int _count;
        utils::fileReader m_reader;
        
        size_t m_LocalMax, m_GlobalMax;
        
        cl_device_id m_DeviceID;
        cl_context m_Context;
        cl_command_queue m_Queue;
        cl_program m_Program;
        cl_kernel m_Kernel;
        
        cl_mem m_InputMem;
        cl_mem m_OutputMem;
        
    public:
        ocl(bool);
        ~ocl();
        void setup(const char*, const char*, unsigned int, const float[]);
        void setup(const char**, const char*, unsigned, const float[]);
        void setArguments(int, argument[]);
        void getWorkGroupAndExec();
        void wait();
        void getResults(results*);
        
    private:
        void getContext();
        void getQueue();
        void getProgram(const char** );
        void getProgramExec();
        void getKernel(const char* );
        void getInputOutput(uint );
        void writeInput(const float[] );
    };

}}
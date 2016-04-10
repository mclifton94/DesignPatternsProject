//
//  ocl.cpp
//  FinalProjectDesPats
//
//  Created by MarkClifton on 4/3/16.
//  Copyright © 2016 designPatterns. All rights reserved.
//

#include "ocl.hpp"
#include <iostream>

namespace cap { namespace opencl {
  
    ocl::ocl(bool gpu_cpu){
        err = clGetDeviceIDs(NULL, gpu_cpu ? CL_DEVICE_TYPE_GPU : CL_DEVICE_TYPE_CPU, 1, &m_DeviceID, NULL);
        if( err != CL_SUCCESS ){
            std::cerr << "Failed to create device group!\n";
        }
        
        getContext();
        getQueue();
        
    }
    
    ocl::~ocl(){
        clReleaseMemObject(m_InputMem);
        clReleaseMemObject(m_OutputMem);
        clReleaseProgram(m_Program);
        clReleaseKernel(m_Kernel);
        clReleaseCommandQueue(m_Queue);
        clReleaseContext(m_Context);
    }
    
    void ocl::setup(const char** Kernel, const char* kernelFunc, unsigned int count, const float * data){
        getProgram(Kernel);
        getProgramExec();
        getKernel(kernelFunc);
        getInputOutput(count);
        writeInput(data);
    }
    
    void ocl::setup(const char* kernelFile, const char* kernelFunc, unsigned int count, const float * data){
        if(!m_reader.open(kernelFile)){
            std::cerr << "Failed to open " << kernelFile << "\n";
            return;
        }
        
        // NEED IMPROVEMENT, IF POSSIBLE
        std::string contents = "";
        unsigned char c;
        while(m_reader.read(c)){
            contents += c;
        }
        m_reader.close();
        const char* temp = contents.c_str();
        
        getProgram(&temp);
        getProgramExec();
        getKernel(kernelFunc);
        getInputOutput(count);
        writeInput(data);
    }
    
    void ocl::getContext(){
        m_Context = clCreateContext(0, 1, &m_DeviceID, NULL, NULL, &err);
        if(!m_Context){
            std::cerr << "Failed to create context!\n";
        }
    }
    
    void ocl::getQueue(){
        m_Queue = clCreateCommandQueue(m_Context, m_DeviceID, 0, &err);
        if(!m_Queue){
            std::cerr << "Failed to get queue!\n";
        }
    }
    
    void ocl::getProgram(const char** fileinput ){
        m_Program = clCreateProgramWithSource(m_Context, 1, fileinput, NULL, &err);
        if(!m_Program){
            std::cerr << "Failed to create program!\n";
        }
    }
    
    void ocl::getProgramExec(){
        err = clBuildProgram(m_Program, 0, NULL, NULL, NULL, NULL);
        if(err){
            std::cerr << "Failed to build program executable!\n";
            
             size_t len;
             char buffer[2048];
             clGetProgramBuildInfo(m_Program, m_DeviceID, CL_PROGRAM_BUILD_LOG, sizeof(buffer), buffer, &len);
             printf("%s\n", buffer);
             
        }
    }
    
    void ocl::getKernel(const char* kernelName ){
        m_Kernel = clCreateKernel(m_Program, kernelName, &err);
        if (!m_Kernel || err)
        {
            std::cerr << "Failed to create compute kernel!\n";
        }
    }
    
    void ocl::getInputOutput(unsigned int count ){
        _count = count;
        m_InputMem = clCreateBuffer(m_Context,  CL_MEM_READ_ONLY,  sizeof(float) * _count, NULL, NULL);
        m_OutputMem = clCreateBuffer(m_Context, CL_MEM_WRITE_ONLY, sizeof(results) * _count, NULL, NULL);
        if (!m_InputMem || !m_OutputMem)
        {
            std::cerr << "Failed to allocate device memory!\n";
        }
    }
    
    void ocl::writeInput(const float data[]){
        err = clEnqueueWriteBuffer(m_Queue, m_InputMem, CL_TRUE, 0, sizeof(float) * _count, data, 0, NULL, NULL);
        if (err)
        {
            std::cerr << "Failed to write to source array!\n";
        }
    }
    void getWorkGroupAndExec();
    
    void ocl::setArguments(int count, argument args[]){
        err = 0;
        err  = clSetKernelArg(m_Kernel, 0, sizeof(cl_mem), &m_InputMem);
        err |= clSetKernelArg(m_Kernel, 1, sizeof(cl_mem), &m_OutputMem);
        
        for(int i=0; i< count; i++){
            err |= clSetKernelArg(m_Kernel, i+2, args[i].sizeOf, args[i].actualParam);
        }
        
        if (err)
        {
            std::cerr << "Failed to set kernel arguments! " << err << "\n";
        }
    }
    
    void ocl::getWorkGroupAndExec(){
        err = clGetKernelWorkGroupInfo(m_Kernel, m_DeviceID, CL_KERNEL_WORK_GROUP_SIZE, sizeof(m_LocalMax), &m_LocalMax, NULL);
        if (err != CL_SUCCESS)
        {
            std::cerr << "Failed to retrieve kernel work group info! " << err << "\n";
        }
        
        m_LocalMax = _count < m_LocalMax ? _count : m_LocalMax;
        m_GlobalMax = _count < m_LocalMax ? m_LocalMax : _count;
        
        err = clEnqueueNDRangeKernel(m_Queue, m_Kernel, 1, NULL, &m_GlobalMax, &m_LocalMax, 0, NULL, NULL);
        if (err)
        {
            std::cerr << "Failed to execute kernel!\n";
        }
    }
    
    void ocl::wait(){
        clFinish(m_Queue);
    }
    
    void ocl::getResults(results* result){
        err = clEnqueueReadBuffer( m_Queue, m_OutputMem, CL_TRUE, 0, sizeof(results) * _count, result, 0, NULL, NULL );
        if (err)
        {
            std::cerr << "Failed to read output array! " << err << "\n";
        }
    }
    
}}
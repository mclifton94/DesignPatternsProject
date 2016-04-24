//
//  audioTrack.cpp
//  FinalProjectDesPats
//
//  Created by MarkClifton on 4/24/16.
//  Copyright © 2016 designPatterns. All rights reserved.
//

#include "audioTrack.hpp"

namespace cap { namespace openal {
  
    audioTrack::audioTrack(std::string filepath, bool debug)
    : m_filepath(filepath)
    {
        FILE* fp = NULL;
        fp = fopen(m_filepath.c_str(), "rb");
        if( !fp ){
            error(1, "Failed to open file!\n");
            return;
        }
        
        char type[4];
        int size, chunkSize, avgBytesPS, dataSize;
        short formatType, channels, bytesPS, bitsPS;
        
        fread(type,sizeof(char),4,fp);
        if(type[0]!='R' || type[1]!='I' || type[2]!='F' || type[3]!='F'){
            error(2, "Invalid file format!\n");
            return;
        }
        
        fread(&size, sizeof(int),1,fp);
        fread(type, sizeof(char),4,fp);
        if (type[0]!='W' || type[1]!='A' || type[2]!='V' || type[3]!='E'){
            error(3, "Invalid file format!\n");
            return;
        }
    
        fread(type,sizeof(char),4,fp);
        if (type[0]!='f' || type[1]!='m' || type[2]!='t' || type[3]!=' '){
            error(4, "Invalid file format!\n");
            return;
        }
        
        fread(&chunkSize,sizeof(int),1,fp);
        fread(&formatType,sizeof(short),1,fp);
        fread(&channels,sizeof(short),1,fp);
        fread(&m_freq,sizeof(int),1,fp);
        fread(&avgBytesPS,sizeof(int),1,fp);
        fread(&bytesPS,sizeof(short),1,fp);
        fread(&bitsPS,sizeof(short),1,fp);
        
        fread(type, sizeof(char), 4, fp);
        while(type[0]!='d' || type[1]!='a' || type[2]!='t' || type[3]!='a'){
            if(fread(type, sizeof(char), 4, fp) != 1){
                error(404, "CORRUPT FILE!\n");
                return;
            }
        }
        
        fread(&dataSize,sizeof(int),1,fp);
        
        if(debug){
            std::cout << "Chunk Size: " << chunkSize << "\n";
            std::cout << "Format Type: " << formatType << "\n";
            std::cout << "Channels: " << channels << "\n";
            std::cout << "Sample Rate: " << m_freq << "\n";
            std::cout << "Average Bytes Per Second: " << avgBytesPS << "\n";
            std::cout << "Bytes Per Sample: " << bytesPS << "\n";
            std::cout << "Bits Per Sample: " << bitsPS << "\n";
            std::cout << "Data Size: " << dataSize << "\n";
        }
        m_data.reset(new unsigned char[dataSize]);
        fread(m_data.get(),sizeof(char),dataSize,fp);
        
        m_device = alcOpenDevice(NULL);
        if( !m_device ){
            error(10, "Failed to get sound device!\n");
            return;
        }
        
        m_context = alcCreateContext(m_device, NULL);
        alcMakeContextCurrent(m_context);
        if( !m_context ){
            error(11, "Failed to get sound context!\n");
            return;
        }
        
        alGenBuffers(1, &m_buffer);
        alGenSources(1, &m_source);
        if( alGetError() != AL_NO_ERROR){
            error(20, "Failed to Generate Source\n");
            return;
        }
        
        if(bitsPS == 8)
        {
            if(channels == 1)
                m_format = AL_FORMAT_MONO8;
            else if(channels == 2)
                m_format = AL_FORMAT_STEREO8;
        }
        else if(bitsPS == 16)
        {
            if(channels == 1)
                m_format = AL_FORMAT_MONO16;
            else if(channels == 2)
                m_format = AL_FORMAT_STEREO16;
        }
        if( !m_format ){
            error(21, "Wrong Bits Per Sample!\n");
            return;
        }
        
        alBufferData(m_buffer, m_format, m_data.get(), dataSize, m_freq);
        if(alGetError() != AL_NO_ERROR){
            error(22, "Error loading buffer!\n");
            return;
        }
        
        properties();
        
        fclose(fp);
    }
    
    void audioTrack::properties(){
        //Sound setting variables
        ALfloat SourcePos[] = { 0.0, 0.0, 0.0 };                                    //Position of the source sound
        ALfloat SourceVel[] = { 0.0, 0.0, 0.0 };                                    //Velocity of the source sound
        ALfloat ListenerPos[] = { 0.0, 0.0, 0.0 };                                  //Position of the listener
        ALfloat ListenerVel[] = { 0.0, 0.0, 0.0 };                                  //Velocity of the listener
        ALfloat ListenerOri[] = { 0.0, 0.0, -1.0,  0.0, 1.0, 0.0 };                 //Orientation of the listener
        //First direction vector, then vector pointing up)
        //Listener
        alListenerfv(AL_POSITION,    ListenerPos);                                  //Set position of the listener
        alListenerfv(AL_VELOCITY,    ListenerVel);                                  //Set velocity of the listener
        alListenerfv(AL_ORIENTATION, ListenerOri);                                  //Set orientation of the listener
        
        //Source
        alSourcei (m_source, AL_BUFFER,   m_buffer);                                 //Link the buffer to the source
        alSourcef (m_source, AL_PITCH,    1.0f     );                                 //Set the pitch of the source
        alSourcef (m_source, AL_GAIN,     1.0f     );                                 //Set the gain of the source
        alSourcefv(m_source, AL_POSITION, SourcePos);                                 //Set the position of the source
        alSourcefv(m_source, AL_VELOCITY, SourceVel);                                 //Set the velocity of the source
        alSourcei (m_source, AL_LOOPING,  AL_FALSE );                                 //Set if source is looping sound
    }
    
    audioTrack::~audioTrack(){
        alDeleteSources(1, &m_source);
        alDeleteBuffers(1, &m_buffer);
        alcMakeContextCurrent(NULL);
        alcDestroyContext(m_context);
        alcCloseDevice(m_device);
    }
    
    void audioTrack::play(){
       alSourcePlay(m_source);
        if(alGetError() != AL_NO_ERROR){
            error(50, "Failed to play!\n");
        }
    }
    
    void audioTrack::pause(){
        alSourcePause(m_source);
        if(alGetError() != AL_NO_ERROR){
            error(51, "Failed to pause!\n");
        }
    }
    
    void audioTrack::restart(){
        alSourceRewind(m_source);
        alSourcePlay(m_source);
        if(alGetError() != AL_NO_ERROR){
            error(52, "Failed to restart!\n");
        }
    }
    
    void audioTrack::error(int errCode, std::string errMsg){
        std::cerr << errCode << ": " << errMsg << "\n";
    }
    
}}
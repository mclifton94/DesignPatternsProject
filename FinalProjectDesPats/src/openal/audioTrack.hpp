//
//  audioTrack.hpp
//  FinalProjectDesPats
//
//  Created by MarkClifton on 4/24/16.
//  Copyright © 2016 designPatterns. All rights reserved.
//

#pragma once

#include <iostream>

#include "AL/al.h"
#include "AL/alc.h"
#include "AL/alext.h"

#include "common/alhelpers.h"

//#define DEBUG

namespace cap { namespace openal {
    
    class audioTrack {
    private:
        std::string m_filepath;
        
        ALuint m_source;
        ALuint m_buffer;
        ALuint m_freq;
        ALenum m_format = 0;
        
        ALCdevice* m_device;
        ALCcontext* m_context = NULL;
        
        std::unique_ptr<unsigned char> m_data;
        
        void properties();
        void error(int, std::string);
    public:
        audioTrack(std::string, bool = 0);
        ~audioTrack();
        
        void play();
        void pause();
        void restart();
    };
    
}}
//
//  textureLoad.hpp
//  FinalProjectDesPats
//
//  Created by MarkClifton on 4/24/16.
//  Copyright © 2016 designPatterns. All rights reserved.
//

#pragma once

#include <FreeImage.h>
#include <string>
#include <GL/glew.h>

namespace cap { namespace graphics {

    class loadTexture {
    public:
        static BYTE* load_Texture(const char* filename, GLsizei* width, GLsizei* height)
        {
            FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
            FIBITMAP *dib = nullptr;
            fif = FreeImage_GetFileType(filename, 0);
            if (fif == FIF_UNKNOWN)
                fif = FreeImage_GetFIFFromFilename(filename);
            if (fif == FIF_UNKNOWN)
                return nullptr;
            
            if (FreeImage_FIFSupportsReading(fif))
                dib = FreeImage_Load(fif, filename);
            if (!dib)
                return nullptr;
            
            BYTE* result = FreeImage_GetBits(dib);
            *width = FreeImage_GetWidth(dib);
            *height = FreeImage_GetHeight(dib);
            
            return result;
        }
    };

}}
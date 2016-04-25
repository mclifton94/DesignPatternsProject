//
//  textureManager.hpp
//  FinalProjectDesPats
//
//  Created by MarkClifton on 4/24/16.
//  Copyright © 2016 designPatterns. All rights reserved.
//

#pragma once

#include "texture.hpp"

#include <vector>
#include <string>
#include <map>

namespace cap { namespace graphics {
    
    typedef std::map<std::string, int> textureMap;
    typedef std::map<std::string, std::string> pathToString;
    
    struct searchResult {
        bool isFound;
        texture* texture;
    };
    
    class textureManager {
    private:
        int m_maxTextures;
        
        std::vector<texture*> m_allTextures;
        std::vector<texture*> m_currentTextures; //0-max current bound
        std::unique_ptr<GLint[]> m_textureIDs; // 0-max
        
        textureMap m_textureMap; // path, int in allTextures vector
        
        textureManager(int);
        
    public:
        ~textureManager();
        static textureManager* getInstance();
        
        void submitTexture(std::string, int);
        searchResult findTexture(std::string);
        
        void enableTextures();
        void disableTextures();
        
        int bindTexture(std::string);
        
        inline void resetCurrentTextures(){ m_currentTextures.clear(); }
        inline GLint* getTextureIDs() const { return m_textureIDs.get(); }
    };

}}
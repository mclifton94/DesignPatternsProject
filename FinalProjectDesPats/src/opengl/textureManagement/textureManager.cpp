//
//  textureManager.cpp
//  FinalProjectDesPats
//
//  Created by MarkClifton on 4/24/16.
//  Copyright © 2016 designPatterns. All rights reserved.
//

#include "textureManager.hpp"

namespace cap { namespace graphics {
  
    
    //--------------------------------------------------------------------------------
    textureManager* textureManager::getInstance(){
        static textureManager instance(16);
        return &instance;
    }
    
    //--------------------------------------------------------------------------------
    textureManager::textureManager(int numTextures)
    : m_maxTextures(numTextures)
    {
        m_textureIDs.reset(new GLint[m_maxTextures]);
        for(int i=0; i < m_maxTextures; i++){
            m_textureIDs[i] = i;
        }
    }
    
    //--------------------------------------------------------------------------------
    textureManager::~textureManager(){
        for(int i=0; i<m_allTextures.size(); i++){
            delete m_allTextures[i];
        }
    }
    
    //--------------------------------------------------------------------------------
    void textureManager::submitTexture(std::string path, int loadWith){
        if( !findTexture(path).isFound ){
            m_allTextures.push_back(new texture(path, loadWith));
            m_textureMap[path] = (int)m_allTextures.size()-1;
        }
    }
    
    //--------------------------------------------------------------------------------
    searchResult textureManager::findTexture(std::string path){
        searchResult result;
        result.isFound = false;
        if(m_textureMap.count(path)){
            result.isFound = true;
            result.texture = m_allTextures[m_textureMap[path]];
        }
        return result;
    }
    
    //--------------------------------------------------------------------------------
    void textureManager::enableTextures(){
        for (int i = 0; i < m_currentTextures.size(); i++){
            glActiveTexture(GL_TEXTURE0 + i);
            glBindTexture(GL_TEXTURE_2D, m_currentTextures[i]->getID());
        }
    }
    
    //--------------------------------------------------------------------------------
    void textureManager::disableTextures(){
    }
    
    //--------------------------------------------------------------------------------
    int textureManager::bindTexture(std::string path){
        if((int)m_currentTextures.size() == m_maxTextures){
            resetCurrentTextures();
        }
        m_currentTextures.push_back(m_allTextures[m_textureMap[path]]);
        return (int)m_currentTextures.size();
    }
    
}}


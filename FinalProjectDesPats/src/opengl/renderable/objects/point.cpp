//
//  point.cpp
//  FinalProjectDesPats
//
//  Created by MarkClifton on 4/10/16.
//  Copyright © 2016 designPatterns. All rights reserved.
//

#include "point.hpp"

namespace cap { namespace graphics {
    
    //--------------------------------------------------------------------------------
    point::point(vec3 position){
        m_position = position;
        m_color = vec4(.9f,.9f,.9f,1);
        
        m_buffer.reset(new bufferObject(GL_ARRAY_BUFFER));
        m_vertices.reset(new vertex[1]);
        
        setup();
        buffer();
    }
    
    //--------------------------------------------------------------------------------
    void point::buffer(){
        if(m_buffer->getID() == 0)
            m_buffer->genBuffer();
        m_buffer->bindBuffer();
        m_buffer->bufferData(1, sizeof(vertex), m_vertices.get(), GL_STATIC_DRAW);
        m_buffer->unbindBuffer();
    }
    
    //--------------------------------------------------------------------------------
    void point::setPosition(vec3 position){
        m_position = position;
        setup();
        buffer();
    }
    
    //--------------------------------------------------------------------------------
    vec3 point::getPosition(){
        return m_position;
    }
    
    //--------------------------------------------------------------------------------
    void point::draw(){
        m_buffer->bindBuffer();
        
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        
        glVertexAttribPointer(0, sizeof(vertex::position)/sizeof(GLfloat), GL_FLOAT, GL_FALSE, sizeof(vertex), BUFFER_OFFSET(offsetof(vertex, position)));
        glVertexAttribPointer(1, sizeof(vertex::color)/sizeof(GLfloat), GL_FLOAT, GL_FALSE, sizeof(vertex), BUFFER_OFFSET(offsetof(vertex, color)));
        
        glDrawArrays(GL_POINTS, 0, 1);
        
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        
        m_buffer->unbindBuffer();
    }
    
    //--------------------------------------------------------------------------------
    void point::setup(){
        m_vertices[0].color = m_color;
        m_vertices[0].position = m_position;
    }
    
    //--------------------------------------------------------------------------------
    void point::setColor(vec4 color){
        m_color = color;
        setup();
        buffer();
    }
    
    //--------------------------------------------------------------------------------
    vec4 point::getColor(){
        return m_color;
    }
    
    //--------------------------------------------------------------------------------
    void point::setVelocity(float velocity){
        m_velocity = velocity;
    }
    
    //--------------------------------------------------------------------------------
    float point::getVelocity(){
        return m_velocity;
    }
    
    //--------------------------------------------------------------------------------
    void point::setMass(float mass){
        m_mass = mass;
    }
    
    //--------------------------------------------------------------------------------
    float point::getMass(){
        return m_mass;
    }
    
    //--------------------------------------------------------------------------------
    void point::setDirection(vec3 direction){
        m_direction = direction;
    }
    
    //--------------------------------------------------------------------------------
    vec3 point::getDirection(){
        return m_direction;
    }
    
    //--------------------------------------------------------------------------------
    point* point::clone(){
        point* newClone = new point(m_position);
        newClone->m_color = m_color;
        newClone->m_direction = m_direction;
        newClone->m_velocity = m_velocity;
        newClone->m_mass = m_mass;
        return newClone;
    }
}}
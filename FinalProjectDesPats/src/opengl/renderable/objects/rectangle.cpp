//
//  rectangle.cpp
//  FinalProjectDesPats
//
//  Created by Mark Clifton on 4/4/16.
//  Copyright © 2016 designPatterns. All rights reserved.
//

#include "rectangle.hpp"

namespace cap { namespace graphics {
    
    rectangle::rectangle(vec2 size, vec3 position){
        m_size = size;
        m_position = position;
        m_color = vec4(.9f,.9f,.9f,1);
        m_buffer.reset(new bufferObject(GL_ARRAY_BUFFER));
        
        m_vertices.reset(new vertex[6]);
        
        setup();
        buffer();
    }

    void rectangle::buffer(){
        if(m_buffer->getID() == 0)
            m_buffer->genBuffer();
        m_buffer->bindBuffer();
        
        m_buffer->bufferData(4, sizeof(vertex), m_vertices.get(), GL_STATIC_DRAW);
    }
    
    void rectangle::draw(){
        m_buffer->bindBuffer();
        
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        
        glVertexAttribPointer(0, sizeof(vertex::position)/sizeof(GLfloat), GL_FLOAT, GL_FALSE, sizeof(vertex), BUFFER_OFFSET(offsetof(vertex, position)));
        glVertexAttribPointer(1, sizeof(vertex::color)/sizeof(GLfloat), GL_FLOAT, GL_FALSE, sizeof(vertex), BUFFER_OFFSET(offsetof(vertex, color)));
        
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    }
    
    void rectangle::setup(){
        m_vertices[0].color = m_color;
        m_vertices[0].position = vec3(m_position[0]+m_size[0]/2.f, m_position[1]+m_size[1]/2.f, m_position[2]);
        
        m_vertices[1].color = m_color;
        m_vertices[1].position = vec3(m_position[0]+m_size[0]/2.f, m_position[1]-m_size[1]/2.f, m_position[2]);

        m_vertices[2].color = m_color;
        m_vertices[2].position = vec3(m_position[0]-m_size[0]/2.f, m_position[1]-m_size[1]/2.f, m_position[2]);
        
        m_vertices[3].color = m_color;
        m_vertices[3].position = vec3(m_position[0]-m_size[0]/2.f, m_position[1]+m_size[1]/2.f, m_position[2]);
    }
    
    void rectangle::setColor(vec4 color){
        m_color = color;
        
        setup();
        buffer();
    }
    
    vec4 rectangle::getColor(){
        return m_color;
    }
    
    void rectangle::setVelocity(float velocity){
        m_velocity = velocity;
    }
    
    float rectangle::getVelocity(){
        return m_velocity;
    }
    
    void rectangle::setMass(float mass){
        m_mass = mass;
    }
    
    float rectangle::getMass(){
        return m_mass;
    }
    
    void rectangle::setDirection(vec3 direction){
        m_direction = direction;
    }
    
    vec3 rectangle::getDirection(){
        return m_direction;
    }
    
}}
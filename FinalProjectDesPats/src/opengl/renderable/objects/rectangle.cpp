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
        
        setup();
        buffer();
    }

    void rectangle::buffer(){
        glGenVertexArrays(1, &_vao);
        glBindVertexArray(_vao);
        m_buffer->genBuffer();
        m_buffer->bindBuffer();
        
        //m_buffer->bufferData(12, sizeof(GLfloat), arr, GL_STATIC_DRAW);
        glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), arr, GL_STATIC_DRAW);

    }
    
    void rectangle::draw(){
        m_buffer->bindBuffer();
        
        glEnableVertexAttribArray(0);
        
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), BUFFER_OFFSET(0));
        
        glDrawArrays(GL_TRIANGLES, 0, 6);

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
        
        
        
        arr[0] = m_vertices[0].position[0];
        arr[1] = m_vertices[0].position[1];
        arr[2] = m_vertices[0].position[2];
        arr[3] = m_vertices[1].position[0];
        arr[4] = m_vertices[1].position[1];
        arr[5] = m_vertices[1].position[2];
        arr[6] = m_vertices[2].position[0];
        arr[7] = m_vertices[2].position[1];
        arr[8] = m_vertices[2].position[2];
        
        arr[9] = m_vertices[0].position[0];
        arr[10] = m_vertices[0].position[1];
        arr[11] = m_vertices[0].position[2];
        arr[12] = m_vertices[2].position[0];
        arr[13] = m_vertices[2].position[1];
        arr[14] = m_vertices[2].position[2];
        arr[15] = m_vertices[3].position[0];
        arr[16] = m_vertices[3].position[1];
        arr[17] = m_vertices[3].position[2];
        
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
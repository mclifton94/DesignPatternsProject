//
//  rectangle.cpp
//  FinalProjectDesPats
//
//  Created by Mark Clifton on 4/4/16.
//  Copyright © 2016 designPatterns. All rights reserved.
//

#include "rectangle.hpp"

namespace cap { namespace graphics {
    
    //--------------------------------------------------------------------------------
    rectangle::rectangle(vec2 size, vec3 position)
    : m_coords(vec2(), vec2())
    {
        m_size = size;
        m_position = position;
        m_color = vec4(.9f,.9f,.9f,1);
        m_buffer.reset(new bufferObject(GL_ARRAY_BUFFER));
        
        m_coords = texCoords(vec2(0,1), vec2(1,0));
        
        m_vertices.reset(new vertex[4]);
        
        setup();
        buffer();
    }

    //--------------------------------------------------------------------------------
    void rectangle::buffer(){
        if(m_buffer->getID() == 0)
            m_buffer->genBuffer();
        m_buffer->bindBuffer();
        m_buffer->bufferData(4, sizeof(vertex), m_vertices.get(), GL_STATIC_DRAW);
        m_buffer->unbindBuffer();
    }
    
    //--------------------------------------------------------------------------------
    void rectangle::setPosition(vec3 Position){
        m_position = Position;
    }
    
    //--------------------------------------------------------------------------------
    vec3 rectangle::getPosition() const {
        return m_position;
    }
    
    //--------------------------------------------------------------------------------
    void rectangle::draw(){
        m_buffer->bindBuffer();
        
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);
        glEnableVertexAttribArray(3);
        
        glVertexAttribPointer(0, sizeof(vertex::position)/sizeof(GLfloat), GL_FLOAT, GL_FALSE, sizeof(vertex), BUFFER_OFFSET(offsetof(vertex, position)));
        glVertexAttribPointer(1, sizeof(vertex::color)/sizeof(GLfloat), GL_FLOAT, GL_FALSE, sizeof(vertex), BUFFER_OFFSET(offsetof(vertex, color)));
        glVertexAttribPointer(2, sizeof(vertex::texCoord)/sizeof(GLfloat), GL_FLOAT, GL_FALSE, sizeof(vertex), BUFFER_OFFSET(offsetof(vertex, texCoord)));
        glVertexAttribPointer(3, sizeof(vertex::tid)/sizeof(GLfloat), GL_FLOAT, GL_FALSE, sizeof(vertex), BUFFER_OFFSET(offsetof(vertex, tid)));
        
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
        
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(2);
        glDisableVertexAttribArray(3);
        
        m_buffer->unbindBuffer();
    }
    
    //--------------------------------------------------------------------------------
    void rectangle::setup(){
        m_vertices[0].color = m_color;
        m_vertices[0].position = vec3(m_position[0]+m_size[0]/2.f, m_position[1]+m_size[1]/2.f, m_position[2]);
        m_vertices[0].texCoord = m_coords.tr;// vec2(.1,.1);
        m_vertices[0].tid = m_texID;
        
        m_vertices[1].color = m_color;
        m_vertices[1].position = vec3(m_position[0]+m_size[0]/2.f, m_position[1]-m_size[1]/2.f, m_position[2]);
        m_vertices[1].texCoord = m_coords.br;// vec2(.1,0);
        m_vertices[1].tid = m_texID;

        m_vertices[2].color = m_color;
        m_vertices[2].position = vec3(m_position[0]-m_size[0]/2.f, m_position[1]-m_size[1]/2.f, m_position[2]);
        m_vertices[2].texCoord = m_coords.bl;// vec2(0,0);
        m_vertices[2].tid = m_texID;
        
        m_vertices[3].color = m_color;
        m_vertices[3].position = vec3(m_position[0]-m_size[0]/2.f, m_position[1]+m_size[1]/2.f, m_position[2]);
        m_vertices[3].texCoord = m_coords.tl;// vec2(0,.1);
        m_vertices[3].tid = m_texID;
    }
    
    //--------------------------------------------------------------------------------
    void rectangle::setColor(vec4 color){
        m_color = color;
        setup();
        buffer();
    }
    
    //--------------------------------------------------------------------------------
    vec4 rectangle::getColor(){
        return m_color;
    }
    
    //--------------------------------------------------------------------------------
    void rectangle::setVelocity(float velocity){
        m_velocity = velocity;
    }
    
    //--------------------------------------------------------------------------------
    float rectangle::getVelocity(){
        return m_velocity;
    }
    
    //--------------------------------------------------------------------------------
    void rectangle::setMass(float mass){
        m_mass = mass;
    }
    
    //--------------------------------------------------------------------------------
    float rectangle::getMass(){
        return m_mass;
    }
    
    //--------------------------------------------------------------------------------
    void rectangle::setDirection(vec3 direction){
        m_direction = direction;
    }
    
    //--------------------------------------------------------------------------------
    vec3 rectangle::getDirection(){
        return m_direction;
    }
    
    //--------------------------------------------------------------------------------
    void rectangle::setTexture(texture* Texture){
        m_texture = Texture;
    }
    
    //--------------------------------------------------------------------------------
    void rectangle::setTexID(float tid){
        m_texID = tid;
        setup();
        buffer();
    }
    
    //--------------------------------------------------------------------------------
    void rectangle::setTexCoords(texCoords Coords){
        m_coords = Coords;
        setup();
        buffer();
    }
    
    //--------------------------------------------------------------------------------
    texCoords rectangle::getTexCoords() const {
        return m_coords;
    }
    
    //--------------------------------------------------------------------------------
    rectangle* rectangle::clone(){
        rectangle* newClone = new rectangle(m_size, m_position);
        newClone->m_direction = m_direction;
        newClone->m_velocity = m_velocity;
        newClone->m_texID = m_texID;
        newClone->m_texture = m_texture;
        newClone->m_mass = m_mass;
        return newClone;
    }
    
}}
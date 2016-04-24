#version 330 core

layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec4 vColor;
layout(location = 2) in vec2 texCoords;

uniform mat4 pr_matrix;

out vec4 fColor;
out vec3 fPosition;

void main(){
    gl_Position = pr_matrix * vec4(vPosition,1.f);
    gl_Position.w = 1.f;
    fColor = vColor;
    fPosition = gl_Position.xyz;
}
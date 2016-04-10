#version 330 core

layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec4 vColor;

uniform mat4 pr_matrix;

out vec4 fColor;

void main(){
gl_Position = pr_matrix * vec4(vertexPosition_modelspace,1.f);
gl_Position.w = 1.f;
fColor = vColor;
}
#version 330 core
out vec4 color;
in vec4 fColor;
in vec3 fPosition;

void main(){
vec3 light_pos = vec3(0,0,0);
float intensity = 1.0 / length(fPosition - light_pos);
color = fColor*intensity;
}
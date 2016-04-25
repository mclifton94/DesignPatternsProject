#version 410 core

out vec4 color;

in DATA
{
vec4 position;
vec2 uv;
vec4 color;
float tid;
} fs_in;

uniform sampler2D textures[16];

void main()
{
    color = fs_in.color;
    if(fs_in.tid > 0.0){
        int tid = int(fs_in.tid - 0.5);
        color = texture(textures[tid], fs_in.uv);
        if((color.r-5/255.f)*(color.r-5/255.f)<.01 && (color.g-254/255.f)*(color.g-254/255.f)<.01 && (color.b-254/255.f)*(color.b-252/255.f)<.01){
            color.w = 0.f;
        }
    }
}
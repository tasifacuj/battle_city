#version 460

in vec2 ioTexCoord;

uniform sampler2D sampler;

out vec4 frag_color;

void main(){
    vec4 texel = texture( sampler, ioTexCoord );    
    frag_color = texel;
}
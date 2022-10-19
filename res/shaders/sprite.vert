#version 460
layout(location = 0) in vec2 vertex_position;
layout(location = 1) in vec2 tex_coord;

out vec2 ioTexCoord;

uniform mat4 model;
uniform mat4 projection;

void main(){
    ioTexCoord = tex_coord;
    gl_Position = projection * model * vec4( vertex_position, 0.0, 1.0 );
}
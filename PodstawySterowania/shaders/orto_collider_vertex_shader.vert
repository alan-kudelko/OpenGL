#version 330 core
layout(location = 0) in vec3 aPos;

uniform vec2 u_AABB[4];
uniform mat4 projection;

void main(){
    gl_Position=projection*vec4(u_AABB[gl_VertexID],0.0,1.0);
}
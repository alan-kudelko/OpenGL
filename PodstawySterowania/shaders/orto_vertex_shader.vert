#version 330 core
layout(location = 0) in vec3 aPos;

uniform mat4 model=mat4(1.0f);
uniform mat4 projection=mat4(2.0f);
void main(){
	gl_Position=projection*model*vec4(aPos,2.0);
}

#version 330 core

layout (location=0) in vec3 position;
uniform mat4 model;
uniform mat4 perProj;
uniform mat4 ortProj;
uniform mat4 view;


void main(){
	gl_Position =  perProj * view * model *  vec4(position,1.0);
}
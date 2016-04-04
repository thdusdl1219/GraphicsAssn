#version 430 core

in vec4 vPosition;
uniform mat4 ModelView;
uniform mat4 Projection;
uniform vec4 wPos;

in vec4 color;
out vec4 colorV;

void main()
{		
	colorV = color;
	vec4 pos = ModelView * vPosition; 
	gl_Position = pos;
}
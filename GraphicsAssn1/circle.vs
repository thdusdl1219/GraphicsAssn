#version 430 core

in vec4 vPosition;
uniform mat4 ModelView;
uniform mat4 Projection;
uniform mat4 View;

in vec4 color;
out vec4 colorV;

void main()
{		
	colorV = color;
	gl_Position = View * ModelView * vPosition; 
}
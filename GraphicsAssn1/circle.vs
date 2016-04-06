#version 430 core

in vec4 vPosition;
uniform mat4 ModelView;

in vec4 vColor;
out vec4 color;

void main()
{		
	color = vColor;	
	gl_Position = ModelView * vPosition;
}
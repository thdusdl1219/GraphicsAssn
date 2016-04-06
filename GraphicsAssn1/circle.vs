#version 430 core

in vec4 vPosition;
uniform mat4 ModelView;
uniform mat4 Projection;
uniform mat4 View;

in vec4 vColor;
out vec4 color;

void main()
{		
	color = vColor;	
	gl_Position = View * ModelView * vPosition;
}
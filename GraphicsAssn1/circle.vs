#version 430 core

in vec4 vPosition;
//uniform mat4 ModelView;
//uniform mat4 Projection;


void main()
{		
	gl_Position = vPosition;
}
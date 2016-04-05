#version 430 core

in vec4 vPosition;
uniform mat4 ModelView;
uniform mat4 Projection;
uniform vec2 offset;
uniform mat4 scalef;

in vec4 color;
out vec4 colorV;

void main()
{		
	colorV = color;

	vec4 pos = ModelView * vPosition; 

	vec4 result = pos + vec4(offset,0.0,0.0);	
	gl_Position = scalef * result;
}
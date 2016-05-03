#version 430 core

in vec3 pos;
in vec3 normal;
in vec2 TexCoord;

out vec4 color;
out vec2 vTexCoord;
out vec3 vNormal;

uniform mat4 ModelView;
uniform vec3 uColor;


void main()
{		
	
	vTexCoord = TexCoord;
	vNormal = normal;
	color = vec4(uColor, 1.0);	
	gl_Position = ModelView * vec4(pos, 1.0);
}
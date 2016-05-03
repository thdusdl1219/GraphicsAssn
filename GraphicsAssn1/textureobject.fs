#version 430 core

uniform sampler2D myTexture;
in vec2 vTexCoord;
in vec4 color;
in vec3 vNormal;


void main() 
{ 
	vec3 norm = normalize(vNormal);
	gl_FragColor = texture(myTexture, vTexCoord) * color;
} 

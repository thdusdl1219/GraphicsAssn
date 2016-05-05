#version 430 core

uniform sampler2D myTexture;
uniform sampler2D noTexture;


in vec4 L;        //light vector
in vec3 V;		 //view vector

uniform vec4 AmbientColor;    //ambient RGBA -- alpha is intensity 
uniform vec3 Falloff;         //attenuation coefficients

uniform float specular_power = 1.0;
in vec2 vTexCoord;
in vec4 color;
in vec3 vNormal;
in vec3 vtangent;


void main() 
{ 
	gl_FragColor = color;
	
} 

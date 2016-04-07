#version 430 core

in vec4 color;

void main() 
{ 
	gl_FragColor = vec4(128.0 / 255.0, 128.0 / 255.0, 128.0 / 255.0, 1.0);
	//gl_FragColor = color;
} 

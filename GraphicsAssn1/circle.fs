#version 430 core

in vec4 color;

void main() 
{ 
    //gl_FragColor = vec4(0.0, 0.0, 1.0, 1.0);
	gl_FragColor = color;
} 

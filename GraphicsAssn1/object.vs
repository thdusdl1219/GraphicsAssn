#version 430 core

in vec3 pos;
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;


uniform vec3 uColor;
out vec4 color;

void main()
{		

	color = vec4(uColor, 1.0);	
<<<<<<< HEAD

	gl_Position = ModelView * vec4(pos, 1.0);
=======
	gl_Position = Projection * View * Model * vec4(pos, 1.0);
>>>>>>> normal map 구현 및 광원 버그 고침
}
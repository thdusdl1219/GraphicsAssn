#version 430 core
in vec2 pos;
// uniform mat4 scalef;
uniform mat4 ModelView;

void main()
{	
	gl_Position = ModelView * vec4(pos, 0.0, 1.0);
	//gl_Position = vec4(result, 0.0, 1.0);
}
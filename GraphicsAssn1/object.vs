#version 430 core
in vec2 pos;
uniform mat4 scalef;
uniform vec2 ModelView;

void main()
{	
	vec2 result = pos + ModelView;
	gl_Position = scalef * vec4(result, 0.0, 1.0);
}
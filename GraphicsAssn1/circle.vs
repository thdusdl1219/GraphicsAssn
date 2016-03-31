#version 430 core
in vec2 pos;
uniform mat4 scalef;

void main()
{	
	vec4 result = scalef * vec4(pos, 0.0, 1.0);
	gl_Position = vec4(result.x + 1.0, result.y + 1.0, 0.0, 1.0);
}
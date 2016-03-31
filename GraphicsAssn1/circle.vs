#version 430 core
in vec2 pos;

const float PI = 3.1415926;
void main()
{
	  for (int i = 0; i <= 10; i++) {
        // Angle between each side in radians
        float ang = PI * 2.0 / 10.0 * i;

        // Offset from center of point (0.3 to accomodate for aspect ratio)
        vec4 offset = vec4(cos(ang) * 0.3, -sin(ang) * 0.4, 0.0, 0.0);
        gl_Position = vec4(pos, 0.0, 1.0) + offset;

    }


}
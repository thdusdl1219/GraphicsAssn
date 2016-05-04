#version 430 core

in vec3 pos;
in vec3 normal;
in vec2 TexCoord;
in vec3 tangent;

out vec4 color;
out vec2 vTexCoord;
out vec3 vNormal;
out vec3 vtangent;
out vec3 vPosition;
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform vec3 uColor;
uniform vec4 vLightPos;
out vec4 LightPos;


void main()
{		
	//float bug = 0.0;
	vTexCoord = TexCoord;

	mat4 mvp = View * Model;
	mat3 normalMatrix = mat3(mvp);
	normalMatrix = inverse(normalMatrix);
	normalMatrix = transpose(normalMatrix);

	vec3 Normal = normalize(normalMatrix * normal);

	// for debug
	//if(Normal.z != 1.0)
	//	bug = 1.0;
	//vec4 Normal = vec4(normal, 1.0);

	vNormal = Normal.xyz;
	color = vec4(uColor.x, uColor.yz, 1.0);
		
	vec4 position = Projection * View * Model * vec4(pos, 1.0);

	vec3 Tangent = normalize(normalMatrix * tangent);
	//vec4 Tangent = vec4(tangent, 1.0);
	vtangent = Tangent.xyz;

	gl_Position = position;

	mat3 m = mat3(View);
	vec4 LightPostmp = View * vec4(vLightPos.xyz, 1.0);
	
	if(vLightPos.w == 0) {
		LightPostmp = vec4(m * vLightPos.xyz, 0);	
	}
	LightPos = vec4(LightPostmp.xyz, vLightPos.w);

	vPosition = position.xyz;
}
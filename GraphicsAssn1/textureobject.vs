#version 430 core

in vec3 pos;
in vec3 normal;
in vec2 TexCoord;

out vec4 color;
out vec2 vTexCoord;
out vec3 vNormal;
uniform mat4 ModelView;
uniform vec3 uColor;

uniform vec3 light_pos = vec3(0,1,1);
uniform vec3 diffuse_albedo = vec3(0.5, 0.2, 0.7);
uniform vec3 specular_albedo = vec3(0.7);
uniform vec3 ambient = vec3(0.1, 0.1, 0.1);
uniform float specular_power = 128.0;

void main()
{			
	vTexCoord = TexCoord;
	vNormal = normal;
	//color = vec4(uColor, 1.0);	
	vec4 position = ModelView * vec4(pos, 1.0);
	
	vec4 P = position;
	vec3 N = mat3(ModelView) * vNormal;
	vec3 L = light_pos - P.xyz;
	vec3 V = -P.xyz;

	N = normalize(N);
	L = normalize(L);
	V = normalize(V);

	vec3 R = reflect(-L,N);

	vec3 diffuse = max(dot(N,L), 0.0) * diffuse_albedo;
	vec3 specular = pow(max(dot(R,V), 0.0), specular_power) * specular_albedo;

	color = vec4(ambient + diffuse + specular, 1.0);

	gl_Position = position;
}
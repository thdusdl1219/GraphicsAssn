#version 430 core

in vec3 pos;
in vec3 normal;
in vec2 TexCoord;
in vec3 tangent;

out vec4 color;
out vec2 vTexCoord;
out vec3 vNormal;
out vec4 L;
out vec3 V;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform vec3 uColor;
uniform vec4 vLightPos;
uniform float specular_power = 1.0;

uniform vec4 AmbientColor;    //ambient RGBA -- alpha is intensity 
uniform vec3 Falloff;         //attenuation coefficients


void main()
{		
	//float bug = 0.0;
	vTexCoord = TexCoord;

	mat4 mvp = View * Model;
	mat3 normalMatrix = mat3(mvp);
	normalMatrix = inverse(normalMatrix);
	normalMatrix = transpose(normalMatrix);
	vec4 LightColor = vec4(1.0);
	
	vec3 Normal = normalize(normalMatrix * normal);

	// for debug
	//if(Normal.z != 1.0)
	//	bug = 1.0;
	//vec4 Normal = vec4(normal, 1.0);


	//≥Î∏ª ∫§≈Õ ∞ËªÍ
	vNormal = Normal.xyz;
	
		
	vec4 position = Projection * View * Model * vec4(pos, 1.0);
	mat3 v = mat3(View);
	mat3 m = mat3(Model);
	vec3 ViewPos = v * m * pos;	
	
	vec3 LV = (v * m * vLightPos.xyz) - ViewPos;
	
	//∫‰ ∞¯∞£ ∂Û¿Ã∆Æ ∫§≈Õ ∞ËªÍ
	L = vec4(LV, vLightPos.w);
	//∞≈∏Æ ∞ËªÍ
	float D = length(L);

	//∫‰ ∫§≈Õ ∞ËªÍ
	V = -ViewPos;

	
	//Normalize
	vNormal = normalize(vNormal);
	L = normalize(L);
	V = normalize(V);
	vec3 R = reflect(-L.xyz,vNormal);


	//∞®ºË
    vec3 Attenuation = vec3(1.0 / ( Falloff.x + (Falloff.y * D) + (Falloff.z * D * D)));		



	//Ambient, diffuse, specular ∞ËªÍ
	vec3 Ambient = AmbientColor.rgb * AmbientColor.a;
	vec3 Diffuse = (LightColor.rgb * LightColor.a) * max(dot(vNormal, L.xyz), 0.0);
	vec3 Specular = pow(max(dot(R,V),0.0), specular_power) * vec3(0.7);
	vec3 FinalColor;
	vec3 Intensity = Ambient + Diffuse;

	if(L.w == 0) // directional light
	{		
		FinalColor =  DiffuseColor.rgb * Intensity;		
	}
	else FinalColor = DiffuseColor.rgb * Intensity + Attenuation * Specular;	


	color = FinalColor;
	gl_Position = position;

}
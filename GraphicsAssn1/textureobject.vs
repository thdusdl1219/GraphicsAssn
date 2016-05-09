#version 430 core

uniform sampler2D myTexture;
uniform sampler2D noTexture;

in vec3 pos;
in vec3 normal;
in vec2 TexCoord;
in vec3 tangent;

flat out vec4 flat_color;
out vec4 color;
out vec2 vTexCoord;
out vec3 vNormal;
out vec4 L;
out vec4 L2;
out vec3 V;
out vec3 specular;
out vec3 vtangent;

out vec3 vPosition;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform vec3 uColor;
uniform vec4 vLightPos;
uniform vec4 vLightPos2;
uniform int shadingMode;

uniform vec4 AmbientColor;    //ambient RGBA -- alpha is intensity 
uniform vec3 Falloff;         //attenuation coefficients

uniform float specular_power = 10.0;

vec3 CalcNormal()
{
    vec3 Normal = normalize(vNormal);
    vec3 Tangent = normalize(vtangent);
    Tangent = normalize(Tangent - dot(Tangent, Normal) * Normal);
    vec3 Bitangent = cross(Tangent, Normal);
    vec3 BumpMapNormal = texture(noTexture, vTexCoord).rgb;
    BumpMapNormal = 2.0 * BumpMapNormal - vec3(1.0, 1.0, 1.0);
    vec3 NewNormal;
    mat3 TBN = mat3(Tangent, Bitangent, Normal);
    NewNormal = TBN * BumpMapNormal;
    NewNormal = normalize(NewNormal);
    return NewNormal;
}

void main()
{			
	vec4 LightColor = vec4(1.0);
	vec3 NormalMap = texture2D(noTexture, vTexCoord).rgb;

	//shadingMode = 1 은 Flat shading
	//shadingMode = 2 은 Gouraud shading
	if(shadingMode == 0 || shadingMode == 1 || shadingMode == 2 || shadingMode == 3)
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


		//노말 벡터 계산
		vNormal = Normal.xyz;
	
		
		vec4 position = Projection * View * Model * vec4(pos, 1.0);
		vec3 Tangent = normalize(normalMatrix * tangent);
		vtangent = Tangent.xyz;

		//mat3 v = mat3(View);	
		//mat3 m = mat3(Model);
		
		vec4 tmp = View * Model * vec4(pos, 1.0);	
		vec3 ViewPos = tmp.xyz;
		vec3 LV = (View * vLightPos).xyz - ViewPos.xyz;
		vec3 LV2 = (View * vLightPos2).xyz - ViewPos.xyz;
		if(vLightPos.w == 0)
		{
			LV = -ViewPos.xyz;
			LV2 = -ViewPos.xyz;
		}
		//뷰 공간 라이트 벡터 계산
				
		L = vec4(LV, vLightPos.w);
		L2 = vec4(LV2, vLightPos2.w);
		float D = length(LV);
		float D2 = length(LV2);
		//뷰 벡터 계산
		V = -ViewPos;
		
		if(shadingMode == 0 || shadingMode == 1 || shadingMode == 2)
		{
			//vNormal = normalize(vNormal);
			vNormal = CalcNormal();
			vNormal = normalize(vNormal);
			L = normalize(L);
			L2 = normalize(L2);
			V = normalize(V);
			vec3 R = reflect(-L.xyz,vNormal);
			vec3 R2 = reflect(-L2.xyz,vNormal);


			//감쇠
			float Attenuation = (1.0 / ( Falloff.x + (Falloff.y * D) + (Falloff.z * D * D)));	
			float Attenuation2 = (1.0 / ( Falloff.x + (Falloff.y * D2) + (Falloff.z * D2 * D2)));	

			//Ambient, diffuse, specular 계산
			vec3 Ambient = AmbientColor.rgb * AmbientColor.a;
			vec3 Diffuse = (LightColor.rgb * LightColor.a) * max(dot(vNormal, L.xyz), 0.0);
			vec3 Diffuse2 = (LightColor.rgb * LightColor.a) * max(dot(vNormal, L2.xyz), 0.0);
			vec3 Specular = pow(max(dot(R,V),0.0), specular_power) * vec3(0.7);
			vec3 Specular2 = pow(max(dot(R2,V),0.0), specular_power) * vec3(0.7);
			vec3 Intensity = (Ambient + Attenuation) * Diffuse;
			vec3 Intensity2 = (Ambient + Attenuation) * Diffuse2;


			vec3 FinalColor;
			vec4 DiffuseColor = texture2D(myTexture, vTexCoord);
			if(L.w == 0) // directional light
			{		
				//directional light는 attenuation 성분이 없음.
				FinalColor =  (2 * Ambient + Diffuse + Diffuse2) * DiffuseColor.rgb;		
				color = vec4(FinalColor, 1.0);
				flat_color = vec4(FinalColor, 1.0);
			}
			else{				
				FinalColor = (Intensity + Intensity2) * DiffuseColor.rgb + Attenuation * Specular + Attenuation2 * Specular2;
				color = vec4(FinalColor, 1.0);
				flat_color = vec4(FinalColor, 1.0);
			}
			
		}

		//shadingMode = 3 은 Phong shading
		else if(shadingMode == 3)
		{
			color = vec4(uColor.x, uColor.yz, 1.0);			
		}
		gl_Position = position;
	}
	

}
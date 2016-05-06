#version 430 core

uniform sampler2D myTexture;


in vec3 pos;
in vec3 normal;
in vec2 TexCoord;
in vec3 tangent;

flat out vec4 flat_color;
out vec4 color;
out vec2 vTexCoord;
out vec3 vNormal;
out vec4 L;
out vec3 V;
out vec3 specular;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform vec3 uColor;
uniform vec4 vLightPos;
uniform int shadingMode;

uniform vec4 AmbientColor;    //ambient RGBA -- alpha is intensity 
uniform vec3 Falloff;         //attenuation coefficients

uniform float specular_power = 1.0;


void main()
{		
	
	vec4 LightColor = vec4(1.0);
	//shadingMode = 2 은 Gouraud shading
	if(shadingMode == 1 || shadingMode == 2 || shadingMode == 3)
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
		mat3 v = mat3(View);
		mat3 m = mat3(Model);
		vec3 ViewPos = v * m * pos;	
	
		vec3 LV = (v * m * vLightPos.xyz) - ViewPos;
	
		//뷰 공간 라이트 벡터 계산
		L = vec4(LV, vLightPos.w);
		float D = length(L);
		//뷰 벡터 계산
		V = -ViewPos;
		
		if(shadingMode == 1 || shadingMode == 2)
		{
			vNormal = normalize(vNormal);
			L = normalize(L);
			V = normalize(V);
			vec3 R = reflect(-L.xyz,vNormal);


			//감쇠
			vec3 Attenuation = vec3(1.0 / ( Falloff.x + (Falloff.y * D) + (Falloff.z * D * D)));	


			//Ambient, diffuse, specular 계산
			vec3 Ambient = AmbientColor.rgb * AmbientColor.a;
			vec3 Diffuse = (LightColor.rgb * LightColor.a) * max(dot(vNormal, L.xyz), 0.0);
			vec3 Specular = pow(max(dot(R,V),0.0), specular_power) * vec3(0.7);
			vec3 FinalColor;
			vec3 Intensity = Ambient + Attenuation * Diffuse;

			vec4 DiffuseColor = texture2D(myTexture, vTexCoord);
			if(L.w == 0) // directional light
			{		
				//directional light는 attenuation 성분이 없음.
				FinalColor =  (Ambient + Diffuse) * DiffuseColor.rgb;		
				color = vec4(FinalColor, 1.0);
				flat_color = vec4(FinalColor, 1.0);
			}
			else{
				
				FinalColor = Intensity * DiffuseColor.rgb + Attenuation * Specular;
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
#version 430 core

uniform sampler2D myTexture;
uniform sampler2D noTexture;

uniform int shadingMode;


uniform vec4 AmbientColor;    //ambient RGBA -- alpha is intensity 
uniform vec3 Falloff;         //attenuation coefficients
uniform float specular_power;

in vec4 L;        //light vector
in vec4 L2;

in vec3 V;		 //view vector

in vec2 vTexCoord;
in vec4 color;
flat in vec4 flat_color;
in vec3 vNormal;
in vec3 vtangent;
in vec3 specular;

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

	//shadingMode 1, Flat shading
	if (shadingMode == 0)
		gl_FragColor = color;
	else if(shadingMode == 1)
		gl_FragColor = flat_color;

	//shaidngMode 2 , Gouraud shading
	else if(shadingMode == 2){		
		gl_FragColor = color;
	}		

	//shadingMode 3 , Phong shading
	else if(shadingMode == 3){
		vec4 DiffuseColor = texture2D(myTexture, vTexCoord);
		vec3 NormalMap = texture2D(noTexture, vTexCoord).rgb;
		vec4 LightColor = vec4(1.0);
		

		//Determine distance (used for attenuation) BEFORE we normalize our LightDir
		
		float D = length(L.xyz);
		float D2 = length(L2.xyz);

		//vec3 Normal = normalize(vNormal);	
		vec3 Normal = CalcNormal();
		vec4 Light = normalize(L);
		vec4 Light2 = normalize(L2);
		vec3 View = normalize(V);
		vec3 R = reflect(-Light.xyz,Normal);
		vec3 R2 = reflect(-Light2.xyz,Normal);
	
	

		//Pre-multiply light color with intensity
		//Then perform "N dot L" to determine our diffuse term
		vec3 Diffuse = (LightColor.rgb * LightColor.a) * max(dot(Normal, Light.xyz), 0.0);
		vec3 Diffuse2 = (LightColor.rgb * LightColor.a) * max(dot(Normal, Light2.xyz), 0.0);


		//pre-multiply ambient color with intensity
		vec3 Ambient = AmbientColor.rgb * AmbientColor.a;

		//calculate attenuation
		vec3 Attenuation = vec3(1.0 / ( Falloff.x + (Falloff.y * D) + (Falloff.z * D * D)));	
		vec3 Attenuation2 = vec3(1.0 / ( Falloff.x + (Falloff.y * D2) + (Falloff.z * D2 * D2)));		
		
		//Diffuse = Attenuation * Diffuse;
		//Diffuse2 = Attenuation2 * Diffuse2;

		vec3 Specular = pow(max(dot(R,View),0.0), specular_power) * vec3(0.7);
		vec3 Specular2 = pow(max(dot(R2,View),0.0), specular_power) * vec3(0.7);
		
		vec3 FinalColor;
		vec3 Intensity = Ambient + Diffuse * Attenuation;
		vec3 Intensity2 = Ambient + Diffuse2 * Attenuation2;

		if(Light.w == 0) // directional light
		{		
			FinalColor =  DiffuseColor.rgb * (2 * Ambient + Diffuse + Diffuse2);
		
		}
		else FinalColor = DiffuseColor.rgb * (Intensity + Intensity2) + Attenuation * Specular + Attenuation2 * Specular2;	 
	
		gl_FragColor = vec4(FinalColor, DiffuseColor.a);
	}
} 

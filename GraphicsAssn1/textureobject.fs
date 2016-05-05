#version 430 core

uniform sampler2D myTexture;
uniform sampler2D noTexture;


in vec4 L;        //light vector
in vec3 V;		 //view vector

uniform vec4 AmbientColor;    //ambient RGBA -- alpha is intensity 
uniform vec3 Falloff;         //attenuation coefficients

uniform float specular_power = 1.0;
in vec2 vTexCoord;
in vec4 color;
in vec3 vNormal;
in vec3 vtangent;
in vec3 vPosition;

void main() 
{ 
	vec4 DiffuseColor = texture2D(myTexture, vTexCoord);
	vec3 NormalMap = texture2D(noTexture, vTexCoord).rgb;
	vec4 LightColor = vec4(1.0);
		

	//Determine distance (used for attenuation) BEFORE we normalize our LightDir
    
	vec3 Normal = normalize(vNormal);
	float D = length(L);
	vec4 Light = normalize(L);
	vec3 View = normalize(V);
	vec3 R = reflect(-Light.xyz,Normal);
	
	

	//Pre-multiply light color with intensity
    //Then perform "N dot L" to determine our diffuse term
	vec3 Diffuse = (LightColor.rgb * LightColor.a) * max(dot(Normal, Light.xyz), 0.0);


	//pre-multiply ambient color with intensity
    vec3 Ambient = AmbientColor.rgb * AmbientColor.a;

	//calculate attenuation
    vec3 Attenuation = vec3(1.0 / ( Falloff.x + (Falloff.y * D) + (Falloff.z * D * D)));		
	Diffuse = Attenuation * Diffuse;

	vec3 Specular = pow(max(dot(R,View),0.0), specular_power) * vec3(1.0);
	vec3 FinalColor;
	vec3 Intensity;

	if(Light.w == 0) // directional light
	{
		Intensity = Ambient + Diffuse;
		FinalColor =  DiffuseColor.rgb * Intensity;
	}
	else FinalColor = DiffuseColor.rgb * Diffuse + Specular;
	 

	gl_FragColor = color * vec4(FinalColor, DiffuseColor.a);
	//gl_FragColor = color;
} 

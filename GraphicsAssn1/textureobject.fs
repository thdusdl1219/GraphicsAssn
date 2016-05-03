#version 430 core

uniform sampler2D myTexture;
uniform sampler2D noTexture;


uniform vec4 LightPos;        //light position, normalized
uniform vec2 Resolution;      //resolution of screen
uniform vec4 AmbientColor;    //ambient RGBA -- alpha is intensity 
uniform vec3 Falloff;         //attenuation coefficients

in vec2 vTexCoord;
in vec4 color;
in vec3 vNormal;


void main() 
{ 
	//vec3 norm = normalize(vNormal);
	vec4 DiffuseColor = texture2D(myTexture, vTexCoord);
	vec3 NormalMap = texture2D(noTexture, vTexCoord).rgb;
	vec4 LightColor = vec4(1.0);

	vec3 LightDir = vec3(LightPos.xy - (gl_FragCoord.xy / Resolution.xy), LightPos.z);
	if(LightPos.w == 0) // directional light
	{
		LightDir = vec3(LightPos.xyz);
	}
	LightDir.x *= Resolution.x / Resolution.y;

	 //Determine distance (used for attenuation) BEFORE we normalize our LightDir
    float D = length(LightDir);

	//normalize our vectors
    //vec3 N = normalize(NormalMap * 2.0 - 1.0);
	vec3 N = normalize(vNormal);
    vec3 L = normalize(LightDir);

	//Pre-multiply light color with intensity
    //Then perform "N dot L" to determine our diffuse term
	vec3 Diffuse = (LightColor.rgb * LightColor.a) * max(dot(N, L), 0.0);

	//pre-multiply ambient color with intensity
    vec3 Ambient = AmbientColor.rgb * AmbientColor.a;

	//calculate attenuation
    float Attenuation = 1.0 / ( Falloff.x + (Falloff.y*D) + (Falloff.z*D*D) );

	//the calculation which brings it all together
	vec3 Intensity = Ambient + Diffuse * Attenuation;
	if(LightPos.w == 0) // directional light
	{
		Intensity = Ambient + Diffuse;
	}
	vec3 FinalColor = DiffuseColor.rgb * Intensity;

	gl_FragColor = color * vec4(FinalColor, DiffuseColor.a);
} 

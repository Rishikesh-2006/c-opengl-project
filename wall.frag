//fragment shader for cube object

#version 330 core
out vec4 FragColor;
in vec3 ourColor;
in vec2 TexCoord;

in vec3 fragpos;
in vec3 Normal;
in vec4 fragposlight;
uniform vec3 lightpos;
uniform vec3 viewpos;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform sampler2D ourTexture;
uniform sampler2D shadowmap;
uniform vec3 attenval;
uniform float lightscale;
uniform float lightmultiplier;
void main()
{	

	//shadow calc
	float shadow = 0.0;
	vec3 lightcoors = fragposlight.xyz/fragposlight.w;

	if(lightcoors.z-0.005<=1.0)
	{
		lightcoors = (lightcoors+1)/2;

		float closest_depth = texture(shadowmap,lightcoors.xy).r;
		float current_depth = lightcoors.z;

		if(current_depth > closest_depth)
		{
		shadow = 1.0;
		}

	}

	//Blinn-phong calc
	float ambientstrength = 0.15;
	vec3 ambient = ambientstrength*lightColor;
	
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightpos - fragpos);
	
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

	float specularstrength = 0.6;
	vec3 viewdir = normalize(viewpos-fragpos);
	//vec3 reflectdir = reflect(-lightDir,norm);
	//float spec = pow(max(dot(viewdir, reflectdir), 0.0), 32);

	vec3 halfwaydir = normalize(lightDir+viewdir);
	float spec = pow(max(dot(norm, halfwaydir), 0.0), 16);
	vec3 specularlight = specularstrength*spec*lightColor;


	float distance  = length(lightpos-fragpos);
	float attenuation = 1.0 / (attenval.x + attenval.y * distance + 
    		    attenval.z* (distance * distance * 8)); 

	//ambient *=attenuation;
	diffuse *=attenuation;
	specularlight *=attenuation;

	vec3 result = (ambient + diffuse*(1.0-shadow) + specularlight) * objectColor;
	FragColor = texture(ourTexture, TexCoord)*vec4(result*lightscale*lightmultiplier, 1.0);

}
	
#version 330 core
out vec4 FragColor;


in vec3 Normal;
in vec3 fragpos;

uniform vec3 lightpos;
uniform vec3 viewpos;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 attenval;
uniform float lightscale;
uniform float lightmultiplier;

void main()
{
		//Blinn-phong calc
	float ambientstrength = 0.15;
	vec3 ambient = ambientstrength*lightColor;
	
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightpos - fragpos);
	
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

	float specularstrength = 0.6;
	vec3 viewdir = normalize(viewpos-fragpos);

	vec3 halfwaydir = normalize(lightDir+viewdir);
	float spec = pow(max(dot(norm, halfwaydir), 0.0), 4);
	vec3 specularlight = specularstrength*spec*lightColor;

	float distance  = length(lightpos-fragpos);
	float attenuation = 1.0 / (attenval.x + attenval.y * distance + 
    		    attenval.z* (distance * distance * 8)); 

	diffuse *=attenuation;
	specularlight *=attenuation;
	

	vec3 result = (ambient + diffuse + specularlight ) * objectColor;
	FragColor =vec4(result*lightscale*lightmultiplier, 1.0);
	//FragColor = vec4(0.0,0.0,1.0,1.0);
}
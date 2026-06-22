//fragment shader for cube object

#version 330 core
out vec4 FragColor;
in vec3 ourColor;
in vec2 TexCoord;

in vec3 fragpos;
in vec3 Normal;
uniform vec3 lightpos;
uniform vec3 viewpos;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform sampler2D ourTexture;

uniform vec3 attenval;
uniform float lightscale;
uniform float lightmultiplier;
void main()
{	
	
	float ambientstrength = 0.1;
	vec3 ambient = ambientstrength*lightColor;
	
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightpos - fragpos);
	
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

	float specularstrength = 1.2;
	vec3 viewdir = normalize(viewpos-fragpos);
	//vec3 reflectdir = reflect(-lightDir,norm);
	//float spec = pow(max(dot(viewdir, reflectdir), 0.0), 128);

	vec3 halfwaydir = normalize(lightDir+viewdir);
	float spec = pow(max(dot(Normal, halfwaydir), 0.0), 128);
	vec3 specularlight = specularstrength*spec*lightColor;


	float distance  = length(lightpos-fragpos);
	float attenuation = 1.0 / (attenval.x + attenval.y * distance + 
    		    attenval.z* (distance * distance)); 

	ambient *=attenuation;
	diffuse *=attenuation;
	specularlight *=attenuation;

	vec3 result = (ambient + diffuse + specularlight) * objectColor;
	FragColor = texture(ourTexture, TexCoord)*vec4(result*lightscale*lightmultiplier, 1.0);

}

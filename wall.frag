//fragment shader for cube object

#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 fragpos;
in vec3 Normal;
in vec3 Tangent;
in vec4 fragposlight;
in vec3 BITangent;

uniform vec3 lightpos;
uniform vec3 viewpos;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform sampler2D ourTexture;
uniform sampler2D shadowmap;
uniform vec3 attenval;
uniform float lightscale;
uniform float lightmultiplier;
uniform sampler2D normalmap;


float shadowcalc(vec4 fragposlight, vec3 normal,vec3 lightdir)
{
	vec3 lightcoors = fragposlight.xyz/fragposlight.w;
	lightcoors = lightcoors*0.5+0.5;
	if(lightcoors.z>1.0) return 0.0;
	
	float closest_depth = texture(shadowmap,lightcoors.xy).r;
	float current_depth = lightcoors.z;
	float bias = max(0.1*(1.0-dot(normal,lightdir)),0.02);
	float shadow = 0.0;
	vec2 texelsize = 1.0/textureSize(shadowmap,0);
	for(int x = -1;x<=1;++x) 
	{
		for(int y = -1;y<=1;++y)
		{
			float depth = texture(shadowmap,lightcoors.xy + vec2(x,y)*texelsize).r;
			shadow += current_depth - bias > depth ? 1.0:0.0;
		}
	}
	shadow /=9.0;
	
return shadow;

}


void main()
{	   
  
	//Blinn-phong calc
	float ambientstrength = 0.15;
	vec3 ambient = ambientstrength*lightColor;
	
	vec3 norm = normalize(Normal);
	mat3 TBN = mat3(Tangent,BITangent,norm);
	TBN = transpose(TBN);

	norm = normalize(TBN*texture(normalmap,TexCoord).xyz*2-1);
	vec3 lightDir = normalize(TBN*lightpos - TBN*fragpos);
	
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

	float specularstrength = 0.6;
	vec3 viewdir = normalize(viewpos-TBN*fragpos);

	vec3 halfwaydir = normalize(lightDir+viewdir);
	float spec = pow(max(dot(norm, halfwaydir), 0.0), 4);
	vec3 specularlight = specularstrength*spec*lightColor;

	float distance  = length(TBN*lightpos-TBN*fragpos);
	float attenuation = 1.0 / (attenval.x + attenval.y * distance + 
    		    attenval.z* (distance * distance * 8)); 

	diffuse *=attenuation;
	specularlight *=attenuation;
	
	float shadow = shadowcalc(fragposlight,norm,lightDir);

	vec3 result = (ambient +(1.0-shadow)*( diffuse + specularlight )) * objectColor;
	FragColor = texture(ourTexture, TexCoord)*vec4(result*lightscale*lightmultiplier, 1.0);

}
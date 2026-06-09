//fragment shader

#version 330 core
out vec4 FragColor;
in vec3 ourColor;
in vec2 TexCoord;
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform sampler2D ourTexture;

void main()
{	float ambientstrength = 0.1;
	vec3 ambient = ambientstrength*lightColor;
	vec3 result = ambient*objectColor;
	FragColor = texture(ourTexture, TexCoord)*vec4(result, 1.0);
}
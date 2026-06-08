//fragment shader

#version 330 core
out vec4 FragColor;
in vec3 ourColor;
in vec2 TexCoord;
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform sampler2D ourTexture;

void main()
{
	FragColor = texture(ourTexture, TexCoord)*vec4(lightColor * objectColor, 1.0);
}
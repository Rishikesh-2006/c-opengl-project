#version 330 core
uniform vec3 color;

in vec2 texcoord;
out vec4 FragColor;
//uniform sampler2D reflection_texture;
//unifrom sampler2D refraction_texture;
in vec4 worldpos;
void main()
{

    FragColor = vec4(color,1.0);
}
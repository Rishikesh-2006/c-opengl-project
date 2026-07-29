#version 330 core
uniform vec3 color;

in vec2 texcoord;
out vec4 FragColor; 

uniform sampler2D reflecttexture;

void main()
{
vec4 reflecttex = texture(reflecttexture,texcoord);
    FragColor = reflecttex;//*vec4(1.0,1.0,1.0,1.0);
}
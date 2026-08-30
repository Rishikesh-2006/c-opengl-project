#version 330 core
uniform vec3 color;

in vec2 texcoord;
out vec4 FragColor;
//uniform sampler2D reflection_texture;
//unifrom sampler2D refraction_texture;

in vec4 plane;
void main()
{
    //vec4 reflection_color = texture(reflection_texture,texcoord);
    //vec4 refraction_color = texture(refraction_texture,texcoord);
    /*min(reflection_color,refraction_color,0.5)*/
    FragColor = vec4(color,1.0);
}
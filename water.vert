/*#version 330 core
uniform float time;
uniform mat4 lightprojection;

out vec3 Normal;
out vec3 fragpos;
out vec4 fragposlight;
out vec2 Texcoord;
void main()
{
float frequency = 60;  //roughly multiplication with the scale value gives correct intution
float speed = 1.0;
float amplitude = 0.1;

vec3 position = aPos;

float wave = amplitude * exp(sin((aPos.x*frequency) + (time*speed)));
wave += (amplitude*0.5) * exp(sin((aPos.x*(frequency*3)) + (time*speed)*4.5));
wave += (amplitude*0.45) * exp(sin((aPos.x*(frequency*5)) + (time*speed)*3.65));
wave += (amplitude*0.39) * exp(sin((aPos.x*(frequency*7)) + (time*speed)*2.5));
wave += amplitude*0.9 * exp(sin((aPos.z*frequency*0.7) + (time*speed)*4));
wave += amplitude*0.5 * exp(sin((aPos.z*frequency*1.5) + (time*speed*3)));
wave += (amplitude*0.46) * exp(sin((aPos.z*(frequency*2.60)) + (time*speed)*3.9));
wave += (amplitude*0.32) * exp(sin((aPos.z*(frequency*4.48)) + (time*speed)*3));




position.y += wave;
fragpos = vec3(model * vec4(position, 1.0));
Normal = mat3(transpose(inverse(model))) * aNormal;

Texcoord = vec2(aTex.x,aTex.y);
fragposlight = lightprojection * vec4(fragpos,1.0);

gl_Position = projection * view * vec4(fragpos, 1.0);
}*/





#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTex;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 texcoord;
void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    texcoord = vec2(aTex.x,aTex.y);
}
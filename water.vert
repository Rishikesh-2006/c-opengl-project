#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTex;
uniform float time;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 lightprojection;

out vec3 Normal;
out vec3 fragpos;
out vec2 Texcoord;
out vec4 fragposlight;

void main()
{
float frequency = 100.5;  //roughly multiplication with the scale value gives correct intution
float speed = 1.0;
float amplitude = 0.3;

vec3 position = aPos;

float wave = amplitude * exp(sin((aPos.x*frequency) + (time*speed)));
wave += amplitude*1.2 * exp(sin((aPos.z*frequency*0.7) + (time*speed)*0.6));
wave += (amplitude*0.9 * exp(sin((-aPos.x*frequency*0.9) + (time*speed*2))));
wave += amplitude*0.8 * exp(sin((aPos.z*frequency*0.5) + (time*speed*2))); 
wave += (amplitude*0.6) * exp(sin((-aPos.z*(frequency*0.8)) + (time*speed*3)));
wave += (amplitude*0.5) * exp(sin((aPos.x*(frequency*1.98)) + (time*speed)*5)) ;
wave += (amplitude*0.4) * exp(sin((-aPos.x*(frequency*2.18)) + (time*speed)*1.3));
wave += (amplitude*0.3) * exp(sin((aPos.z*(frequency*2.48)) + (time*speed)*3));
wave += (amplitude*0.2) * exp(sin((-aPos.z*(frequency*3.8)) + (time*speed)*2));
wave += (amplitude*0.1) * exp(sin((aPos.x*(frequency*3.61)) + (time*speed)*5.3));
wave += (amplitude*0.01) * exp(sin((-aPos.x*(frequency*4.18)) + (time*speed)));

position.y += wave;
fragpos = vec3(model * vec4(position, 1.0));
Normal = mat3(transpose(inverse(model))) * aNormal;

Texcoord = vec2(aTex.x,aTex.y);
fragposlight = lightprojection * vec4(fragpos,1.0);

gl_Position = projection * view * vec4(fragpos, 1.0);

}
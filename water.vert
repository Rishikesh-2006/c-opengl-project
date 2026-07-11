#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
uniform float time;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 Normal;
out vec3 fragpos;

void main()
{
float frequency = 40.5;  //roughly multiplication with the scale value gives correct intution
float speed = 1.0;
float amplitude = 0.4;

float wave = amplitude * sin((aPos.x*frequency) + (time*speed));

wave += amplitude*0.9 * sin((aPos.z*frequency) + (time*speed*2));
wave += (amplitude*0.8) * sin((aPos.x*(frequency*2.18)) + (time*speed*3));
wave += (amplitude*0.7) * sin((aPos.z*(frequency*3.18)) + (time*speed)*5);
wave += (amplitude*0.6) * sin((aPos.x*(frequency*4.18)) + (time*speed)*1.3);
wave += (amplitude*0.5) * sin((aPos.z*(frequency*5.18)) + (time*speed)*3);
wave += (amplitude*0.4) * sin((aPos.x*(frequency*6.8)) + (time*speed)*2);
wave += (amplitude*0.3) * sin((aPos.z*(frequency*7.1)) + (time*speed)*5.3);
wave += (amplitude*0.2) * sin((aPos.x*(frequency*8.18)) + (time*speed));


vec3 position = aPos;
position.y += wave;
fragpos = vec3(model * vec4(position, 1.0));
Normal = mat3(transpose(inverse(model))) * aNormal;


gl_Position = projection * view * vec4(fragpos, 1.0);

}
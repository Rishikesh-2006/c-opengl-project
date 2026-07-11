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
float frequency = 10.0;
float speed = 3.0;
float amplitude = 0.5;

float wave = amplitude * sin((aPos.x*frequency) + (time*speed));
wave += amplitude * sin((aPos.z*frequency) + (time*speed));

vec3 position = aPos;
position.y += wave;
fragpos = vec3(model * vec4(position, 1.0));
Normal = mat3(transpose(inverse(model))) * aNormal;


gl_Position = projection * view * vec4(fragpos, 1.0);

}
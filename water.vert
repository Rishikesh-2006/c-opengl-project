#version 330 core
layout (location = 0) in vec3 aPos;
uniform float time;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;



void main()
{
float frequency = 10.0;
float speed = 3.0;
float amplitude = 0.6;

float wave = amplitude * sin((aPos.x*frequency) + (time*speed));
wave += 0.1 * cos((aPos.x*5) + (time*2));

vec3 position = aPos;
position.y += wave;

    gl_Position = projection * view * model * vec4(position, 1.0);
}
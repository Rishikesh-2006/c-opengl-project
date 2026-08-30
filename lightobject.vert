#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec4 plane;
void main()
{
   vec4 worldpos = model * vec4(aPos,1.0);
    gl_ClipDistance[0] = dot(plane,worldpos);

    gl_Position = projection * view * worldpos;
}
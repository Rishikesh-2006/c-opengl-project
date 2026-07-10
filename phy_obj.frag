#version 330 core
uniform vec3 color;
uniform vec2 uResolution;
out vec4 FragColor; 
in vec3 fragpos;
in vec3 pos;
void main()
{
    vec2 uv = gl_FragCoord.xy/uResolution.xy;

       vec3 finalColor;
       if(pos.x > 0.4 || pos.y>0.4 || pos.x <-0.4 || pos.y < -0.4)
       {
        finalColor = vec3(0.0,0.0,0.0);
       }
       
       else
       {
        finalColor = color;
       }

    FragColor = vec4(finalColor, 1.0);
}

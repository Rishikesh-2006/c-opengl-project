//vertex shader for cube object

#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec2 aTexCoord;
layout(location = 3) in vec3 aNormal;
layout(location = 4) in vec3 aTangent;
layout(location = 5) in vec3 aBITangent;

uniform mat4 transform;
uniform mat4 model;
uniform mat4 view;
uniform vec3 lightpos;
uniform mat4 projection;
uniform mat4 lightprojection;

out vec3 ourColor;
out vec2 TexCoord;
out vec3 Tangent;
out vec3 BITangent;

out vec3 Normal;
out vec3 fragpos;
out vec4 fragposlight;
void main()
{// temporary to check rotation --> transform*vec4(aPos, 1.0);
	fragpos = vec3(model * vec4(aPos, 1.0));
	ourColor = aColor;
	TexCoord = vec2(aTexCoord.x, aTexCoord.y);

	Normal = mat3(transpose(inverse(model))) * aNormal;
	Tangent = normalize(aTangent);
	BITangent = normalize(aBITangent);

	fragposlight = lightprojection * vec4(fragpos,1.0);
	
	gl_Position = projection*view*vec4(fragpos, 1.0);
}

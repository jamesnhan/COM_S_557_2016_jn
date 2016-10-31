#version 410 core

in vec2 in_TexCoord;
in vec3 in_Position;
in vec3 in_Color;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform mat4 inverseViewMatrix;

out vec4 pass_Color;
out vec2 pass_TexCoord;

void main(void)                                                   
{
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(in_Position, 1.0);
    pass_Color = vec4(in_Color, 0.5);
	pass_TexCoord = in_TexCoord;
}
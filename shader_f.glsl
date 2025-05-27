#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D text;
uniform float alphaValue;

void main()
{
	FragColor = texture(text, TexCoord);
}
#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D text;
uniform float alphaValue;

void main()
{
	vec3 color = texture(text, TexCoord).xyz;
	FragColor = vec4(color, alphaValue);
}
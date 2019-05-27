#version 450

layout(location=0) out vec4 FragColor;
layout(location=1) out vec4 color;

in float v_Grey;
in vec2 v_Tex;

uniform sampler2D u_TextureSampler;

void main()
{
	vec2 newTex = v_Tex;
	newTex.y = 1 - newTex.y;
	FragColor = texture(u_TextureSampler, newTex) * v_Grey;
}

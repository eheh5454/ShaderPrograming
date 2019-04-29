#version 450

layout(location=0) out vec4 FragColor;

uniform sampler2D u_Texture;
uniform float u_Time;

in vec2 v_UV;

void main()
{	
	
	
	vec4 newColor = texture(u_Texture, v_UV);
	vec2 newTex = fract(v_UV * 3);


	newColor = texture(u_Texture, newTex);
	
	FragColor = newColor;
}
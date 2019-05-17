#version 450

layout(location=0) out vec4 FragColor;

uniform sampler2D u_Texture;
uniform float u_Time;
uniform int select_num;

in vec2 v_UV;

void main()
{    
	vec2 newUV = v_UV;
	float newy = 9.0 - float(select_num);

	newUV.y = newUV.y / 10.f + newy/10.f;
	

	FragColor = texture(u_Texture,newUV);
	
}
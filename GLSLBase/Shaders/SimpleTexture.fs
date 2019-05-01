#version 450

layout(location=0) out vec4 FragColor;

uniform sampler2D u_Texture;
uniform float u_Time;

in vec2 v_UV;

void main()
{	
	
	

	//ºí·¯ 
	vec2 newTex[5];
	vec4 newColor[5];
	newTex[0]= vec2(v_UV.x, v_UV.y);
	newTex[1] = vec2(v_UV.x - 1/256, v_UV.y);
	newTex[2] = vec2(v_UV.x + 1/256, v_UV.y);
	newTex[3] = vec2(v_UV.x, v_UV.y - 1/256);
	newTex[4] = vec2(v_UV.x, v_UV.y + 1/256);
	newColor[0] = texture(u_Texture, newTex[0]);
	newColor[1] = texture(u_Texture, newTex[1]);
	newColor[2] = texture(u_Texture, newTex[2]);
	newColor[3] = texture(u_Texture, newTex[3]);
	newColor[4] = texture(u_Texture, newTex[4]);
	vec4 finalColor = newColor[0]+newColor[1]+newColor[2]+newColor[3]+newColor[4];
	finalColor /= 5;
	FragColor = finalColor;




	
}
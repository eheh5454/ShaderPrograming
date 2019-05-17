#version 450

layout(location=0) out vec4 FragColor;

uniform sampler2D u_Texture;
uniform sampler2D u_Texture2;
uniform float u_Time;
uniform int select_num;

in vec2 v_UV;

void main()
{	

    

	//뒤집기 
	vec2 newUV = v_UV;
	newUV.y *= 2; 
	if( newUV.y < 1)
	{
		newUV.y = 1- newUV.y;
	}
	FragColor = texture(u_Texture,newUV);

	//RGB 가로로 만들기 
	vec2 newUV2 = v_UV;
	newUV2.x = fract(newUV2.x * 3); //소수점을 날림 
	newUV2.y = newUV2.y / 3.0;
	newUV2.y += (2 - floor(v_UV.x * 3.0))/3.0;	
	FragColor = texture(u_Texture,newUV2);

	//세로로 뒤집기 
	vec2 newUV3 = v_UV;
	newUV3.y = (2-floor(newUV3.y * 3.0)) / 3.0;
	newUV3.y += fract(v_UV.y *3.0)/3.0;

	FragColor = texture(u_Texture,newUV3);

	//벽돌쌓기, 시험 출제 
	vec2 newUV4 = v_UV;

	vec2 newUV5 = v_UV;
	newUV5.y = 1 - newUV5.y;
	newUV5.x /= 2.f;	

	vec4 newTexColor; 
	vec2 newTex2 = vec2(v_UV.x, 1-v_UV.y);

	if(newTex2.x < 0.5)
	{
		newTexColor = texture(u_Texture2,vec2(newTex2.x*2,newTex2.y));
	}
	else
	{
		newTexColor = texture(u_Texture,vec2(newTex2.x*2,newTex2.y));
	}

	
	FragColor = newTexColor;
	
}
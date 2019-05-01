#version 450

layout(location=0) out vec4 FragColor;

uniform sampler2D u_Texture;
uniform float u_Time;

in vec2 v_UV;

void main()
{	

    //블러 
	
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
	
}
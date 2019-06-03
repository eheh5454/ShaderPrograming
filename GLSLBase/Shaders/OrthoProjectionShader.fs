#version 450

in vec4 v_Color;
in vec2 v_Tex;
in float v_Grey; 

out vec4 FragColor;

uniform sampler2D u_TextureSampler;
uniform sampler2D u_SnowTexture;
uniform sampler2D u_GrassTexture;

void main()
{
    //FragColor = vec4(1,0,1,0);
	vec2 newTex = v_Tex;
	newTex.y = 1 - newTex.y;

	vec4 grass = texture(u_GrassTexture, newTex) * (1.f - v_Grey);
	vec4 finalcolor = grass;
	FragColor = finalcolor;
	

}

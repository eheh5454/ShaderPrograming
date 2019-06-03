#version 450

in vec4 v_Color;
in vec2 v_Tex;

out vec4 FragColor;

uniform sampler2D u_TextureSampler;

void main()
{
    //FragColor = vec4(1,0,1,0);
	FragColor = texture(u_TextureSampler, v_Tex);

}

#version 450

layout(location=0) out vec4 FragColor;

uniform sampler2D u_Texture;
uniform float u_Time;

in vec2 v_UV;

void main()
{
	/*vec4 new_Color =  texture(u_Texture, v_UV);
    if(new_Color.a < 0.5)
		discard;

	FragColor = new_Color;*/
	
	//사인곡선 그리기 
	vec4 newColor = vec4(0);	
	newColor = texture(u_Texture, v_UV);
	float length = 0.01f;
	float UV_x = v_UV.x;
	UV_x += u_Time;

	if( v_UV.y - 0.5 < sin(UV_x * 3.14 * 2) / 2 + length)
	{
		if( v_UV.y - 0.5 > sin(UV_x * 3.14 * 2) / 2 -length)
			newColor = vec4(1);
	}

	FragColor = newColor;
}
#version 450

layout(location=0) out vec4 FragColor;

uniform sampler2D u_Texture;

in vec2 v_UV;

uniform float u_Blursize = 12.f;
uniform vec2 u_Texelsize = vec2(1.0f/1024.0f, 1.0f/1024.0f);

void main()
{
	float size = u_Blursize/2.0;
	vec2 xDir = vec2(1.0, 0);
	vec2 yDir = vec2(0, 1.0);
	vec3 newColor = vec3(0.0, 0.0, 0.0);
	float count = 0.f;

	for(float x = -size;x < size; x+=1.0)
	{
		for(float y = -size; y < size; y += 1.0)
		{
			vec2 newTex = v_UV + x * xDir * u_Texelsize + y * yDir * u_Texelsize;
			vec4 temp = texture(u_Texture, newTex);
			temp = clamp(temp - vec4(1.0), 0.0, 100.0);
			newColor += temp.rgb;
			count += 1.0f;
		}
	}
	FragColor = vec4(newColor/count + texture(u_Texture, v_UV).rgb, 1.0f);
}


#version 450

layout(location=0) out vec4 FragColor;

in vec4 v_color;
in vec2 v_orixy;
in float v_radius;

void main()
{
    vec4 newcolor;
	float dis = sqrt(v_orixy.x * v_orixy.x + v_orixy.y * v_orixy.y);

    if(dis < v_radius)
	{
		newcolor = v_color;
	}
	else 
	{
		newcolor = vec4(0, 0, 0, 0);
	}
	FragColor = newcolor;

}

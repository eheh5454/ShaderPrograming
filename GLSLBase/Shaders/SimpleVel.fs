#version 450

layout(location=0) out vec4 FragColor;

in vec4 v_color;

void main()
{
	FragColor = vec4(2.0);
	FragColor.a= 1.0;
}

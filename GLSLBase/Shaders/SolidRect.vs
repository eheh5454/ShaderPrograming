#version 450

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;

uniform float u_Time; //1.f

void main()
{
    
	float newX, newY;
	newX = sin(u_Time * 3.14 * 2);
	newY = cos(u_Time * 3.14 * 2);

	newX += a_Position.x;
	newY += a_Position.y;

	//gl_Position = vec4(newX, newY, 0, 1);
	gl_Position = vec4(a_Position.xy, 0, 1);
}

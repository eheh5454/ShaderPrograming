#version 450

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;

uniform float u_Time; //1.f

void main()
{
    
	float newX, newY;
	newX= a_Position.x; 
	newY = a_Position.y + sin((a_Position.x + 0.5) * 3.14 * 2 + u_Time) * 0.5 ;	

	gl_Position = vec4(newX, newY, 0, 1);
	//gl_Position = vec4(a_Position.xy, 0, 1);
}

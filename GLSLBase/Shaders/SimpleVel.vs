#version 450

in vec3 a_Position;
in vec3 a_Vel;

uniform float u_Time; 

void main()
{    
	vec3 newPos = a_Position.xyz;

	newPos += a_Vel * u_Time;
	

	gl_Position = vec4(newPos, 1);
}

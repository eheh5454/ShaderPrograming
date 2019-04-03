#version 450

in vec3 a_Position;
in vec2 a_StartLife;
in vec2 ratio_amp;

uniform float u_Time;

const float PI = 3.141592;

void main()
{    
	vec3 newPos = a_Position.xyz;	

	float startTime = a_StartLife.x;
	
	float lifeTime = a_StartLife.y;

	float newTime = u_Time - startTime;	

	if(newTime > 0)
	{	    
	    newTime = mod(newTime, lifeTime);
	    newPos.x += newTime;
		newPos.y += sin(newTime * 2 * PI * ratio_amp.x) * ratio_amp.y;
	}
	else
	{
	    newPos = vec3(10000, 10000, 0);
	}
	
	gl_Position = vec4(newPos.xyz, 1);
}

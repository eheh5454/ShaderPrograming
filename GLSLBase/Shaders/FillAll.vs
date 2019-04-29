#version 450

in vec3 a_Position;
in vec3 a_Vel;
in vec2 a_StartLife;
in vec2 ratio_amp;
in float Value;
in vec4 a_color;

out vec4 v_color;
out vec2 v_originXY;
out float v_radius;

uniform float u_Time;

const float PI = 3.141592;
const mat3 c_RP = mat3(0, -1, 0, 1, 0, 0, 0, 0, 0);
const vec3 c_Gravity = vec3(0, -1000, 0);

void main()
{    
	vec3 newPos = a_Position.xyz;	
	vec3 newVel = a_Vel.xyz;
	v_originXY = newPos.xy;
	v_radius = abs(newPos.x);

	float startTime = a_StartLife.x;
	
	float lifeTime = a_StartLife.y;

	float newTime = u_Time - startTime;	

	float ratio = ratio_amp.x;

	float amp = ratio_amp.y;	

	float value = Value;

	float newalpha; 
	

	if(newTime > 0)
	{
	    newPos.x += sin(value * PI * 2);
		newPos.y += cos(value * PI * 2);

	    newTime = mod(newTime, lifeTime);

		newVel = newVel + c_Gravity * newTime;

		newPos = newPos + a_Vel * newTime +  0.5 * c_Gravity * newTime * newTime;

		vec3 vSin = a_Vel * c_RP;
		newPos = newPos + vSin * sin(newTime * PI * 2 * ratio * 4) * amp;

		newalpha = pow(1 - newTime / lifeTime, 30);
	}
	else
	{
	    newPos = vec3(10000, 10000, 0);
	}
	
	gl_Position = vec4(newPos.xyz, 1);

	v_color = vec4(a_color.xyz, newalpha);
}
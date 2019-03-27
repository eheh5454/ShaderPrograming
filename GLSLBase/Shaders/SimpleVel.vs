#version 450

in vec3 a_Position;
in vec3 a_Vel;
in vec2 a_StartLife;

uniform float u_Time; 
bool u_Repeat = true;


const vec3 c_Gravity  = vec3(0, -5, 0);

void main()
{    
	vec3 newPos = a_Position.xyz;

	float startTime = a_StartLife.x;
	
	float lifeTime = a_StartLife.y;

	float newTime = u_Time - startTime;
		
	
	if(newTime > 0)
	{
	    float life = newTime;		

		float remainingLife = lifeTime - life; //남은 수명 계산 		

		if(u_Repeat == true)
		{
			remainingLife = 1.f;
			newTime = mod(newTime, lifeTime);
		}

		if(remainingLife < 0)
		{ 
			newPos = vec3(10000, 10000, 0);
		}

	    newPos += a_Vel * u_Time + (0.5 * c_Gravity * newTime * newTime);	
	}
	else
	{
	    newPos = vec3(10000, 10000, 0);
	}

	
	gl_Position = vec4(newPos, 1);
}

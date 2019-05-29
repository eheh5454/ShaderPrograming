#version 450

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;
const float PI = 3.141592f;

out float v_Grey;
out vec2 v_Tex;

uniform float u_Time; //1.f

uniform vec2 u_Points[5];

void Flag()
{
	vec3 newPos = a_Position;
	// 맨왼쪽은 고정.

	// 0~1
	float additionalValueX = newPos.x + 0.5f;
	float additionalValueY = newPos.y + 0.5f;

	float periodX =  1 + (1 - additionalValueY) * 0.5f;
	float periodY = (1 + additionalValueX * 0.5f);

	// x :: -0.5 ~ 0.5 -> +0.5 -> 0~1 -> *2 *PI -> 0~2PI
	float valueX = additionalValueY * 2.f * PI * periodX - u_Time * 2;
	float valueY = additionalValueX * 2.f * PI * periodY - u_Time * 1.5f;

	float sinValueX = sin(valueX) * 0.1;
	float sinValueY = sin(valueY) * 0.2f;

	// y scale
	newPos.y *= (1 - additionalValueX) * 0.5f + 0.5f;

	// x
	newPos.x -= sinValueX * additionalValueX;
	// y :: -0.5 ~ 0.5
	newPos.y += sinValueY * additionalValueX;

	v_Grey = (sinValueY + 0.5f);
	// 0~1, 0~1 tex coords
	v_Tex = vec2(0.5f, 0.5f) + a_Position.xy;

	gl_Position = vec4(newPos, 1);
}

//물방울 웨이브 
void Wave()
{
	vec3 newPos = a_Position;
	float grey = 0;

	for(int i = 0; i < 5; i++)
	{
		vec2 target;
		vec2 source;
		target = a_Position.xy;
		source = u_Points[i];
		float dis = length(target - source) * 4 * PI * float(i);
		grey += sin(dis - u_Time);
	}
	newPos.z += grey; 

	gl_Position = vec4(newPos, 1);

	v_Grey = (grey + 1.0) / 2.0;
	v_Tex = vec2(0.5f, 0.5f) + a_Position.xy;	


}

void SphereMapping()
{
	float r = 0.5;
	float newTime = 1 - fract(u_Time);

	float beta = (a_Position.x + 0.5) * 2 * PI; //경도 
	float theta = (a_Position.y + 0.5) * PI; //위도
	//가중치 계산법 사용(1-t)x + ty
	vec3 NewPos = (1 - newTime) * a_Position + newTime * vec3( 
		r * sin(theta) * cos(beta),
		r * sin(theta) * sin(beta),
		r * cos(theta));

	gl_Position = vec4(NewPos,1);
	v_Grey = 1;

}

//mix함수 사용 
void SphereMapping_Mix()
{
	
	float grey = 0;

	for(int i = 0; i < 5; i++)
	{
		vec2 target;
		vec2 source;
		target = a_Position.xy;
		source = u_Points[i];
		float dis = length(target - source) * 4 * PI * float(i);
		grey += sin(dis - u_Time);
	}

	float r = abs(grey) * 0.1 + 0.5;
	float newTime = 1 - fract(u_Time);

	float beta = (a_Position.x + 0.5) * 2 * PI; //경도 
	float theta = (a_Position.y + 0.5) * PI; //위도
	
	vec3 NewPos = vec3( 
		r * sin(theta) * cos(beta),
		r * sin(theta) * sin(beta),
		r * cos(theta));

	//vec3 originPos = a_Position.xyz; 

	//vec3 Pos = mix(originPos,NewPos,newTime);

	gl_Position = vec4(NewPos,1);
	v_Grey = 1;

}


void main()
{
	//Flag();
	//Wave();
	SphereMapping();
}

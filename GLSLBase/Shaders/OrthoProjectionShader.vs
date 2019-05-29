#version 450

in vec3 a_Position;
in vec3 a_Normal;
in vec4 a_Color;
const float PI = 3.141592f;

out float v_Grey;
out vec2 v_Tex;

uniform float u_Time; //1.f

uniform vec2 u_Points[5];

uniform mat4 u_ProjView;
out vec4 v_Color;

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

	gl_Position = vec4(newPos, 1) * u_ProjView;
}

void main()
{

	Flag();

  //gl_Position = u_ProjView * vec4(a_Position, 1.f);
  //v_Color = a_Color;
}


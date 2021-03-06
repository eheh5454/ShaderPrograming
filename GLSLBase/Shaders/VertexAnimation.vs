#version 450

layout(location = 0) in vec3 a_Position;
//in vec4 a_Color;
out float v_Grey;
out vec2 v_Tex;

// Cube
//in vec3 a_Position;
in vec3 a_Normal;
in vec4 a_Color;

uniform mat4 u_ProjView;
out vec4 v_Color;
out vec3 v_Norm;
out vec3 v_Position;

const float PI = 3.141592;
uniform float u_Time;

uniform vec2 u_Points[5];

uniform sampler2D u_heightMapTexture;

void Flag()
{
	vec3 newPos = a_Position;
	
	// 0 ~ 1
	float additionalValueX = newPos.x + 0.5;
	float additionalValueY = newPos.y + 0.5;

	// sin period
	float periodX = 1.0 + (1.0 - additionalValueY) * 0.5;
	float periodY = 1.0 + additionalValueX * 0.5;

	// x :: -0.5 ~ 0.5 --> +0.5 --> 0 ~ 1 --> * 2 * PI --> 0~2PI
	float valueX = additionalValueY * 2 * PI * periodX - u_Time * 12.0;
	float valueY = additionalValueX * 2 * PI * periodY - u_Time * 5.0;
	
	float sinValueX = sin(valueX) * 0.1;
	float sinValueY = sin(valueY) * 0.2;

	// y scale
	newPos.y = newPos.y * ((1.0 - additionalValueX) * 0.5 + 0.5);

	// x
	newPos.x = newPos.x - sinValueX * additionalValueX;
	// y 
	newPos.y = newPos.y + sinValueY * additionalValueX;
	
	gl_Position = u_ProjView * vec4(newPos.xyz,1.0);
	v_Grey = sinValueY + 0.5;
	v_Tex = vec2(0.5,0.5) + a_Position.xy;	// 0 ~ 1 Tex coord
	
}

void Wave()
{	
	float grey = 0;
	vec3 newPos = a_Position.xyz;
	for(int i=0;i<5;++i)
	{
		vec2 target;
		vec2 source;
		target = a_Position.xy;
		source = u_Points[i];

		float dist = length(target - source) * 4 * PI * 2 * float(i);	// 0 ~ 0.5 --> 0 ~ 2PI
		grey += sin(dist - u_Time * 2);
	}
	newPos.z += grey * 0.1;

	gl_Position = u_ProjView * vec4(newPos.xyz, 1);

	v_Grey = (grey + 1.0)/2.0;
	v_Tex = vec2(0.5,0.5) + a_Position.xy;
}

void Morphing()
{
	float grey = 0;
	vec3 newPos = a_Position.xyz;
	for(int i=0;i<5;++i)
	{
		vec2 target;
		vec2 source;
		target = a_Position.xy;
		source = u_Points[i];

		float dist = length(target - source) * 4 * PI * 2 * float(i);	// 0 ~ 0.5 --> 0 ~ 2PI
		grey += sin(dist - u_Time);
	}
	
	float r = abs(grey) * 0.1 + 0.5;
	float beta = (a_Position.x + 0.5) * 2 * PI;
	float theta = (a_Position.y + 0.5) * PI;
	vec3 spherePos = a_Position.xyz;

	spherePos = vec3(r*sin(theta)*cos(beta),r*sin(theta)*sin(beta),r*cos(theta));

	vec3 originPos = a_Position.xyz;

	float interpol = fract(u_Time);
	vec3 mixPos = mix(originPos,spherePos,interpol);

	gl_Position = vec4(mixPos.xyz,1);
	
	v_Grey = 1.0;
}

void HeightMap()
{
	float gap = 1.0/100.0;

	vec2 newUV = a_Position.xy + vec2(0.5 ,0.5);
	vec2 newUVRight = a_Position.xy + vec2(0.5 ,0.5) + vec2(gap , 0.0);
	vec2 newUVUp = a_Position.xy + vec2(0.5 ,0.5) + vec2(0.0 , gap);
	
	float height = texture(u_heightMapTexture,newUV).r;
	float heightRight = texture(u_heightMapTexture,newUVRight).r;
	float heightUp = texture(u_heightMapTexture,newUVUp).r;

	vec3 newPos = vec3(a_Position.xy,a_Position.z + height * 0.2);
	vec3 newPosRight = vec3(a_Position.xy + vec2(gap , 0.0),a_Position.z + heightRight * 0.2);
	vec3 newPosUp = vec3(a_Position.xy + vec2(0.0 , gap) ,a_Position.z + heightUp * 0.2);

	vec3 diff1 = newPosRight - newPos;
	vec3 diff2 = newPosUp - newPos;

	vec3 norm = cross(diff1 , diff2);

	//v_Tex = vec2(0.5 , 0.5) + a_Position.xy;
	gl_Position = u_ProjView * vec4(newPos , 1.0);
	v_Grey = height;
	v_Norm = normalize(norm);
	v_Position = newPos;
}

void main()
{
	//Flag();	
	//Wave();
	//Morphing();
	HeightMap();
}

#version 450

in vec3 a_Position;
in vec2 a_Tex;
in vec2 a_UV;

uniform vec2 u_Pos;
uniform vec2 u_Size;

out vec2 v_UV;

uniform float u_Time; //1.f


void main()
{
    
	vec3 newPos = vec3(a_Position.xy * u_Size.xy + u_Pos.xy, 0);
	gl_Position = vec4(newPos.xyz, 1);

	v_UV = a_UV;

}

#version 450

in vec3 a_Position;
in vec2 a_UV;

out vec2 v_UV;

void main()
{    
	
	gl_Position = vec4(a_Position.xyz, 1);

	v_UV = a_UV;
}
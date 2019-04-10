#version 450

in vec3 a_Position;
in vec2 a_RG;

out vec4 v_color;



void main()
{   
 
    v_color = vec4(a_RG, 0, 1);
	gl_Position = vec4(a_Position, 1);
}

#version 450

layout(location=0) out vec4 FragColor;
layout(location=1) out vec4 color;

uniform sampler2D u_Texture;

in vec4 v_color;
in vec2 v_originXY;
in float v_radius;

void main()
{
   FragColor = texture(u_Texture, v_originXY / v_radius);
   //FragColor = v_color;

}
#version 450

layout(location=0) out vec4 FragColor;

uniform sampler2D u_Texture;
uniform float u_Number;
uniform float u_Resolx;
uniform float u_Resoly; 

in vec2 v_UV;

void main()
{    
   vec2 newUV = v_UV;

   int x_index = int(floor(fract(u_Number / u_Resolx) * u_Resolx));
   int y_index = int(floor(floor(u_Number / u_Resoly))); 

   newUV.x = newUV.x / u_Resolx + x_index / float(u_Resolx);
   newUV.y = newUV.y / u_Resoly + y_index / float(u_Resoly);

   //FragColor = newColor;	

   

   FragColor = texture(u_Texture,newUV);
	
}
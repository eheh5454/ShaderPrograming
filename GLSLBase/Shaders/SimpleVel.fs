#version 450

layout(location=0) out vec4 FragColor;

in vec4 v_color;

const vec2 c_Points[2] = { vec2(0, 0), vec2(0.1, 0.1) };

void main()
{
   vec2 newUV = v_color.xy - vec2(0.5, 0.5);

   /*float distance = sqrt(newUV.x * newUV.x + newUV.y * newUV.y);
   float grey = sin(distance * 3.141592 * 4 * 10);

   if(distance < 0.5 && distance > 0.48)
   {
   	   FragColor = vec4(1);
   }
   else 
   {
   	   FragColor = vec4(0);
   }*/
	//FragColor = vec4(grey); //동심원 만들기 

	
	//레이더에서 적군 원 그리기 
	float pointGrey = 0;

	for (int i = 0; i < 2; i++)
	{
		vec2 newPoint = c_Points[i];
		vec2 newVec = newPoint - newUV;
		float distance = sqrt(newVec.x * newVec.x + newVec.y * newVec.y);
		if(distance < 0.1)
		{
			pointGrey += 0.5 * pow(1-(distance/0.1),5);
		}

	}

	FragColor = vec4(pointGrey);

}

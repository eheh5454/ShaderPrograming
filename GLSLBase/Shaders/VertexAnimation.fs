#version 450

layout(location=0) out vec4 FragColor;

in float v_Grey;
in vec2 v_Tex;

uniform sampler2D u_Texture;
uniform sampler2D u_snowTexture;
uniform sampler2D u_grassTexture;

const vec3 c_Light1 = vec3(0.0 , -1.0 , 1.0);
const vec3 c_Camera = vec3(0.0 , -1.0 , 0.6);

// Cube
in vec4 v_Color;
in vec3 v_Norm;
in vec3 v_Position;
//out vec4 FragColor;

void main()
{
	vec4 snowColor = texture(u_snowTexture,v_Tex * 1) * v_Grey;
	vec4 grassColor = texture(u_grassTexture,v_Tex * 1) * (1.0 - v_Grey);
	vec4 finalColor = snowColor + grassColor;
	//FragColor = texture(u_Texture,v_Tex)*v_Grey;
	float a = 0.4;
	float d = 0.5;
	float s = 1.0;

	vec3 lightDir = c_Light1 - v_Position;
	vec3 ambient = vec3(1,1,1);
	float diffuse = clamp(dot(lightDir,v_Norm),0.0,1.0);
	vec3 diffuseColor = vec3(1,1,1);
	vec3 reflectDir = reflect(lightDir,v_Norm);
	vec3 viewDir = v_Position - c_Camera;
	vec3 specColor = vec3(1,1,1);
	float spec = clamp(dot(viewDir,reflectDir),0.0,1.0);
	spec = pow(spec,6.0);

	vec3 newColor = ambient * a + diffuseColor * diffuse * d + specColor * spec * s;

	FragColor = vec4(newColor , 1);
}

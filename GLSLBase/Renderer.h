#pragma once

#include <string>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <random>
#include <math.h>

#include "Dependencies\glew.h"
#include "Dependencies\wglew.h"
#include "Dependencies\glm/glm.hpp"
#include "Dependencies\glm/gtc/matrix_transform.hpp"
#include "Dependencies\glm/gtx/euler_angles.hpp"

#define PI 3.14f

class Renderer
{
public:
	Renderer(int windowSizeX, int windowSizeY);
	~Renderer();

	GLuint CreatePngTexture(char * filePath);
	GLuint CreateBmpTexture(char * filePath);
	   
	void Test();

	void DrawGrid();

	void GenQuads(int num);

	void GenQuads_New(int num);

	void Draw_Quads();

	void CreateGridMesh();

	void Draw_f4();

	void Draw_SimpleVel();

	void Lecture5();

	void Lecture6();

	void Lecture7();

	void Lecture8();

	void FillAll();


private:
	void Initialize(int windowSizeX, int windowSizeY);
	bool ReadFile(char* filename, std::string *target);
	void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType);
	GLuint CompileShaders(char* filenameVS, char* filenameFS);
	void CreateVertexBufferObjects(); 
	unsigned char * Renderer::loadBMPRaw(const char * imagepath, unsigned int& outWidth, unsigned int& outHeight);

	bool m_Initialized = false;
	
	unsigned int m_WindowSizeX = 0;
	unsigned int m_WindowSizeY = 0;

	GLuint m_VBORect = 0;
	GLuint m_VBOLecture = 0;
	GLuint m_QuadRect = 0; //�������� VBO
	
	GLuint m_VBORect4 = 0; 
	GLuint m_VBOColor = 0;

	//shaders
	GLuint m_SolidRectShader = 0;
	GLuint m_SimpleVelShader = 0;
	GLuint m_FillAllShader = 0;

	GLuint m_VBOUV = 0;


	float g_Time = 0.f;
	float scale_speed = 0.0001f;

	int Quad_num = 0;

	GLuint m_VBOGridMesh = 0;
	int m_GridMesh_Count = 0;


	float x = 0.0001f; 
	float y = 0.f;

	int quad_vertex_count;


};


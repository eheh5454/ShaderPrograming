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

	void DrawSimpleTexture();

	void DrawCheckerboard();
	
	void DrawRGBTexture();

	void DrawMultiTexture();

	void DrawOneTexture();
	
	void DrawSprite(GLuint num);

	void InitMatrix();

	void DrawProj();

	void Cube();

	void DrawHeightMap();

	void DrawTexture(GLuint tex, float x, float y, float sx, float sy);

	void DrawHDRTexture(GLuint tex, float x, float y, float sx, float sy);

	GLuint CreateFBO(int sx, int sy, GLuint *tex, bool isHDR);

	void TestFBO();

private:
	void Initialize(int windowSizeX, int windowSizeY);
	bool ReadFile(char* filename, std::string *target);
	void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType);
	GLuint CompileShaders(char* filenameVS, char* filenameFS);
	void CreateVertexBufferObjects(); 
	unsigned char * Renderer::loadBMPRaw(const char * imagepath, unsigned int& outWidth, unsigned int& outHeight);
	void CreateMyTexture();
	

	bool m_Initialized = false;
	
	unsigned int m_WindowSizeX = 0;
	unsigned int m_WindowSizeY = 0;

	GLuint m_VBORect = 0;
	GLuint m_VBOLecture = 0;
	GLuint m_QuadRect = 0; //쿼드전용 VBO
	
	GLuint m_VBORect4 = 0; 
	GLuint m_VBOColor = 0;
	GLuint m_VBOTexture = 0;
	GLuint m_VBO_Cube = 0;

	//shaders
	GLuint m_SolidRectShader = 0;
	GLuint m_SimpleVelShader = 0;
	GLuint m_FillAllShader = 0;
	GLuint m_TextureShader = 0;
	GLuint m_RGBTextureShader = 0;
	GLuint m_OneTextureShader = 0;
	GLuint m_SpriteShader = 0;
	GLuint m_VSSandboxShader = 0;
	GLuint m_OrthoProjectionShader = 0;
	GLuint m_VertexAnimationShader = 0;
	GLuint m_DrawTextureRectShader = 0;
	GLuint m_DrawHDRTextureRectShader = 0;

	//textures
	GLuint m_ParticleTexture = 0;
	GLuint m_ParticleTexture2 = 0;
	GLuint m_ParticleTexture3 = 0;
	GLuint m_RGBTexture = 0;
	GLuint m_DIgimonTextures = 0;
	GLuint m_DIgimonTextures2 = 0;
	GLuint m_DIgimonTextures3 = 0;
	GLuint m_DIgimonTextures4 = 0;
	GLuint m_OneTexture = 0;
	GLuint m_BearTexture = 0;
	GLuint m_HeightTexture = 0;
	GLuint m_MyTexture = 0;
	GLuint m_SnowTexture = 0;
	GLuint m_GrassTexture = 0;
	GLuint m_FBOTexture = 0; 
	GLuint m_FBOTexture2 = 0;
	GLuint m_FBOTexture3 = 0;
	GLuint m_FBOTexture4 = 0;

	GLuint depthBuffer;

	GLuint m_FBO = 0;
	GLuint m_FBO2 = 0;
	GLuint m_FBO3 = 0;
	GLuint m_FBO4 = 0;

	float g_Time = 0.f;
	float scale_speed = 0.0001f;

	float tex_int = 0;

	int Quad_num = 0;

	GLuint m_VBOGridMesh = 0;
	int m_GridMesh_Count = 0;


	float x = 0.0001f; 
	float y = 0.f;

	int select_num = 0; //단일 텍스처에서 숫자 선택 
	

	int quad_vertex_count;

	glm::mat4 m_ViewMat4;
	glm::mat4 m_ViewProjMat4;
	glm::mat4 m_OrthoProjMat4;
	glm::mat4 m_PerspecProjMat4;
	glm::vec3 m_CameraPosVec3;
	glm::vec3 m_CameraUpVec3;
	glm::vec3 m_CameraLookatVec3;
	glm::vec3 m_CameraMat;
	


};


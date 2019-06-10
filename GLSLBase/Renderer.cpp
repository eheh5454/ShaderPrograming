#include "stdafx.h"
#include "Renderer.h"
#include "LoadPng.h"
#include <Windows.h>
#include <cstdlib>
#include <cassert>
#include <time.h>


using namespace std;

Renderer::Renderer(int windowSizeX, int windowSizeY)
{
	Initialize(windowSizeX, windowSizeY);
}


Renderer::~Renderer()
{
}

void Renderer::Initialize(int windowSizeX, int windowSizeY)
{
	//Set window size
	m_WindowSizeX = windowSizeX;
	m_WindowSizeY = windowSizeY;

	//Load shaders
	m_SolidRectShader = CompileShaders("./Shaders/SolidRect.vs", "./Shaders/SolidRect.fs");
	m_SimpleVelShader = CompileShaders("./Shaders/SimpleVel.vs", "./Shaders/SimpleVel.fs");
	m_FillAllShader = CompileShaders("./Shaders/FillAll.vs", "./Shaders/FillAll.fs");
	m_TextureShader = CompileShaders("./Shaders/SimpleTexture.vs", "./Shaders/SimpleTexture.fs");
	//m_RGBTextureShader = CompileShaders("./Shaders/RGBTexture.vs", "./Shaders/RGBTexture.fs");
	m_OneTextureShader = CompileShaders("./Shaders/OneTexture.vs", "./Shaders/OneTexture.fs");
	m_SpriteShader = CompileShaders("./Shaders/SpriteShader.vs", "./Shaders/SpriteShader.fs");
	m_VSSandboxShader = CompileShaders("./Shaders/FSSandbox.vs", "./Shaders/FSSandbox.fs");
	m_OrthoProjectionShader = CompileShaders("./Shaders/OrthoProjectionShader.vs", "./Shaders/OrthoProjectionShader.fs");
	m_VertexAnimationShader = CompileShaders("./Shaders/VertexAnimation.vs", "./Shaders/VertexAnimation.fs");

	m_ParticleTexture = CreatePngTexture("./Particles/p1.png");
	m_ParticleTexture2 = CreatePngTexture("./Particles/p2.png");
	m_RGBTexture = CreatePngTexture("./Particles/rgb.png");
	m_DIgimonTextures = CreatePngTexture("./Particles/agumon.png");
	m_DIgimonTextures2 = CreatePngTexture("./Particles/greymon.png");
	m_DIgimonTextures3 = CreatePngTexture("./Particles/metalgreymon.png");
	m_DIgimonTextures4 = CreatePngTexture("./Particles/wargreymon.png");
	m_OneTexture = CreatePngTexture("./Particles/123456789.png");
	m_BearTexture = CreatePngTexture("./Particles/bear.png");
	m_HeightTexture = CreatePngTexture("./Particles/heightmap.png");
	m_GrassTexture = CreatePngTexture("./Particles/grass.png");

	//Create VBOs
	CreateVertexBufferObjects();

	InitMatrix();
}

void Renderer::InitMatrix()
{
	
	m_OrthoProjMat4 = glm::ortho(-1.f,1.f,-1.f,1.f,0.f,2.f);
	m_PerspecProjMat4 = glm::perspective(3.141592f * 0.5f, 1.f, 0.001f, 100.f);

	m_CameraPosVec3 = glm::vec3(0.f,-1.f, 0.6f);
	m_CameraUpVec3 = glm::vec3(0.f, 0.f, 1.f);
	m_CameraLookatVec3 = glm::vec3(0.f, 0.f, 0.f);

	m_ViewMat4 = glm::lookAt(m_CameraPosVec3, m_CameraLookatVec3, m_CameraUpVec3);

	//m_ViewProjMat4 = m_OrthoProjMat4 * m_ViewMat4;
	m_ViewProjMat4 = m_PerspecProjMat4 * m_ViewMat4;
	

}

void Renderer::CreateVertexBufferObjects()
{

	float rect_size = 0.5f;
	float rect[]
		=
	{
		-rect_size, -rect_size, 0.f, 0.f, 0.f,
		-rect_size, rect_size, 0.f, 0.f,1.f,
		rect_size, rect_size, 0.f, 1.f,1.f, //Triangle1
		-rect_size, -rect_size, 0.f, 0.f,0.f,
		rect_size, rect_size, 0.f, 1.f,1.f,
		rect_size, -rect_size, 0.f, 1.f,0.f //Triangle2
	};

	glGenBuffers(1, &m_VBORect);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBORect);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rect), rect, GL_STATIC_DRAW);	

	float texture[]
		=
	{
		-rect_size, rect_size, 0.f, 0.f, 1.f,
		-rect_size, -rect_size, 0.f, 0.f,0.f,
		rect_size, rect_size, 0.f, 1.f,1.f, //Triangle1
		rect_size, rect_size, 0.f, 1.f,1.f,
		-rect_size, -rect_size, 0.f, 0.f,0.f,
		rect_size, -rect_size, 0.f, 1.f,0.f //Triangle2
	};

	glGenBuffers(1, &m_VBOTexture);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOTexture);
	glBufferData(GL_ARRAY_BUFFER, sizeof(texture), texture, GL_STATIC_DRAW);

	
	/*lecture2*/
	float myrect[]
		=
	{
		-0.5, -0.5, 0.f, 0.f, 0.5, 0.f, 0.5, -0.5, 0.f //Triangle1
		
	};

	glGenBuffers(1, &m_VBOLecture);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOLecture);
	glBufferData(GL_ARRAY_BUFFER, sizeof(myrect), myrect, GL_STATIC_DRAW);

	//float 4자리를 사용한다. 
	float rect_f4[]
		=
	{
		-0.5, -0.5, 0.f, 0.5,
		-0.5, 0.5, 0.f, 0.5,
		0.5, 0.5, 0.f, 0.5, //Triangle1
		-0.5, -0.5, 0.f, 0.5,
		0.5, 0.5, 0.f, 0.5,
		0.5, -0.5, 0.f, 0.5 //Triangle2
	};

	glGenBuffers(1, &m_VBORect4);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBORect4);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rect_f4), rect_f4, GL_STATIC_DRAW);

	float temp = 0.5f;

	float cube[] = {
	-temp,-temp,-temp, -1.f, 0.f, 0.f, 1.f, 0.f, 0.f, 1.f, //x, y, z, nx, ny, nz, r, g, b, a
	-temp,-temp, temp, -1.f, 0.f, 0.f, 1.f, 0.f, 0.f, 1.f,
	-temp, temp, temp, -1.f, 0.f, 0.f, 1.f, 0.f, 0.f, 1.f,

	temp, temp,-temp, 0.f, 0.f, -1.f, 0.f, 0.f, 1.f, 1.f,
	-temp,-temp,-temp, 0.f, 0.f, -1.f, 0.f, 0.f, 1.f, 1.f,
	-temp, temp,-temp, 0.f, 0.f, -1.f, 0.f, 0.f, 1.f, 1.f,

	temp,-temp, temp, 0.f, -1.f, 0.f, 0.f, 1.f, 0.f, 1.f,
	-temp,-temp,-temp, 0.f, -1.f, 0.f, 0.f, 1.f, 0.f, 1.f,
	temp,-temp,-temp, 0.f, -1.f, 0.f, 0.f, 1.f, 0.f, 1.f,

	temp, temp,-temp, 0.f, 0.f, -1.f, 0.f, 0.f, 1.f, 1.f,
	temp,-temp,-temp, 0.f, 0.f, -1.f, 0.f, 0.f, 1.f, 1.f,
	-temp,-temp,-temp, 0.f, 0.f, -1.f, 0.f, 0.f, 1.f, 1.f,

	-temp,-temp,-temp, -1.f, 0.f, 0.f, 1.f, 0.f, 0.f, 1.f,
	-temp, temp, temp, -1.f, 0.f, 0.f, 1.f, 0.f, 0.f, 1.f,
	-temp, temp,-temp, -1.f, 0.f, 0.f, 1.f, 0.f, 0.f, 1.f,

	temp,-temp, temp, 0.f, -1.f, 0.f, 0.f, 1.f, 0.f, 1.f,
	-temp,-temp, temp, 0.f, -1.f, 0.f, 0.f, 1.f, 0.f, 1.f,
	-temp,-temp,-temp, 0.f, -1.f, 0.f, 0.f, 1.f, 0.f, 1.f,

	-temp, temp, temp, 0.f, 0.f, 1.f, 0.f, 0.f, 1.f, 1.f,
	-temp,-temp, temp, 0.f, 0.f, 1.f, 0.f, 0.f, 1.f, 1.f,
	temp,-temp, temp, 0.f, 0.f, 1.f, 0.f, 0.f, 1.f, 1.f,

	temp, temp, temp, 1.f, 0.f, 0.f, 1.f, 0.f, 0.f, 1.f,
	temp,-temp,-temp, 1.f, 0.f, 0.f, 1.f, 0.f, 0.f, 1.f,
	temp, temp,-temp, 1.f, 0.f, 0.f, 1.f, 0.f, 0.f, 1.f,

	temp,-temp,-temp, 1.f, 0.f, 0.f, 1.f, 0.f, 0.f, 1.f,
	temp, temp, temp, 1.f, 0.f, 0.f, 1.f, 0.f, 0.f, 1.f,
	temp,-temp, temp, 1.f, 0.f, 0.f, 1.f, 0.f, 0.f, 1.f,

	temp, temp, temp, 0.f, 1.f, 0.f, 0.f, 1.f, 0.f, 1.f,
	temp, temp,-temp, 0.f, 1.f, 0.f, 0.f, 1.f, 0.f, 1.f,
	-temp, temp,-temp, 0.f, 1.f, 0.f, 0.f, 1.f, 0.f, 1.f,

	temp, temp, temp, 0.f, 1.f, 0.f, 0.f, 1.f, 0.f, 1.f,
	-temp, temp,-temp, 0.f, 1.f, 0.f, 0.f, 1.f, 0.f, 1.f,
	-temp, temp, temp, 0.f, 1.f, 0.f, 0.f, 1.f, 0.f, 1.f,

	temp, temp, temp, 0.f, 0.f, 1.f, 0.f, 0.f, 1.f, 1.f,
	-temp, temp, temp, 0.f, 0.f, 1.f, 0.f, 0.f, 1.f, 1.f,
	temp,-temp, temp, 0.f, 0.f, 1.f, 0.f, 0.f, 1.f, 1.f,
	};

	glGenBuffers(1, &m_VBO_Cube);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO_Cube);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube), cube, GL_STATIC_DRAW);

	float color[] =
	{
		1, 0, 0, 1, //r g b a
		1, 0, 0, 1,
		1, 0, 0, 1,
		1, 0, 0, 1
	};

	/*glGenBuffers(1, &m_VBOColor);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOColor);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);*/

	//GenQuads(1000);
	GenQuads_New(2000);

	CreateMyTexture();
	CreateGridMesh();
}

void Renderer::CreateGridMesh()
{
	float basePosX = -0.5f;
	float basePosY = -0.5f;
	float targetPosX = 0.5f;
	float targetPosY = 0.5f;

	int pointCountX = 32;
	int pointCountY = 32;

	float width = targetPosX - basePosX;
	float height = targetPosY - basePosY;

	float* point = new float[pointCountX*pointCountY * 2];
	float* vertices = new float[(pointCountX - 1)*(pointCountY - 1) * 2 * 3 * 3];
	m_GridMesh_Count = (pointCountX - 1)*(pointCountY - 1) * 2 * 3;



	//Prepare points
	for (int x = 0; x < pointCountX; x++)
	{
		for (int y = 0; y < pointCountY; y++)
		{
			point[(y*pointCountX + x) * 2 + 0] = basePosX + width * (x / (float)(pointCountX - 1));
			point[(y*pointCountX + x) * 2 + 1] = basePosY + height * (y / (float)(pointCountY - 1));
		}
	}

	//Make triangles
	int vertIndex = 0;
	for (int x = 0; x < pointCountX - 1; x++)
	{
		for (int y = 0; y < pointCountY - 1; y++)
		{
			//Triangle part 1
			vertices[vertIndex] = point[(y*pointCountX + x) * 2 + 0];
			vertIndex++;
			vertices[vertIndex] = point[(y*pointCountX + x) * 2 + 1];
			vertIndex++;
			vertices[vertIndex] = 0.f;
			vertIndex++;
			vertices[vertIndex] = point[((y + 1)*pointCountX + (x + 1)) * 2 + 0];
			vertIndex++;
			vertices[vertIndex] = point[((y + 1)*pointCountX + (x + 1)) * 2 + 1];
			vertIndex++;
			vertices[vertIndex] = 0.f;
			vertIndex++;
			vertices[vertIndex] = point[((y + 1)*pointCountX + x) * 2 + 0];
			vertIndex++;
			vertices[vertIndex] = point[((y + 1)*pointCountX + x) * 2 + 1];
			vertIndex++;
			vertices[vertIndex] = 0.f;
			vertIndex++;

			//Triangle part 2
			vertices[vertIndex] = point[(y*pointCountX + x) * 2 + 0];
			vertIndex++;
			vertices[vertIndex] = point[(y*pointCountX + x) * 2 + 1];
			vertIndex++;
			vertices[vertIndex] = 0.f;
			vertIndex++;
			vertices[vertIndex] = point[(y*pointCountX + (x + 1)) * 2 + 0];
			vertIndex++;
			vertices[vertIndex] = point[(y*pointCountX + (x + 1)) * 2 + 1];
			vertIndex++;
			vertices[vertIndex] = 0.f;
			vertIndex++;
			vertices[vertIndex] = point[((y + 1)*pointCountX + (x + 1)) * 2 + 0];
			vertIndex++;
			vertices[vertIndex] = point[((y + 1)*pointCountX + (x + 1)) * 2 + 1];
			vertIndex++;
			vertices[vertIndex] = 0.f;
			vertIndex++;
		}
	}

	glGenBuffers(1, &m_VBOGridMesh);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOGridMesh);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*(pointCountX - 1)*(pointCountY - 1) * 2 * 3 * 3, vertices, GL_STATIC_DRAW);
}


void Renderer::AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType)
{
	//쉐이더 오브젝트 생성
	GLuint ShaderObj = glCreateShader(ShaderType);

	if (ShaderObj == 0) {
		fprintf(stderr, "Error creating shader type %d\n", ShaderType);
	}

	const GLchar* p[1];
	p[0] = pShaderText;
	GLint Lengths[1];
	Lengths[0] = (GLint)strlen(pShaderText);
	//쉐이더 코드를 쉐이더 오브젝트에 할당
	glShaderSource(ShaderObj, 1, p, Lengths);

	//할당된 쉐이더 코드를 컴파일
	glCompileShader(ShaderObj);

	GLint success;
	// ShaderObj 가 성공적으로 컴파일 되었는지 확인
	glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);
	if (!success) {
		GLchar InfoLog[1024];

		//OpenGL 의 shader log 데이터를 가져옴
		glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);
		fprintf(stderr, "Error compiling shader type %d: '%s'\n", ShaderType, InfoLog);
		printf("%s \n", pShaderText);
	}

	// ShaderProgram 에 attach!!
	glAttachShader(ShaderProgram, ShaderObj);
}

bool Renderer::ReadFile(char* filename, std::string *target)
{
	std::ifstream file(filename);
	if (file.fail())
	{
		std::cout << filename << " file loading failed.. \n";
		file.close();
		return false;
	}
	std::string line;
	while (getline(file, line)) {
		target->append(line.c_str());
		target->append("\n");
	}
	return true;
}

GLuint Renderer::CompileShaders(char* filenameVS, char* filenameFS)
{
	GLuint ShaderProgram = glCreateProgram(); //빈 쉐이더 프로그램 생성

	if (ShaderProgram == 0) { //쉐이더 프로그램이 만들어졌는지 확인
		fprintf(stderr, "Error creating shader program\n");
	}

	std::string vs, fs;

	//shader.vs 가 vs 안으로 로딩됨
	if (!ReadFile(filenameVS, &vs)) {
		printf("Error compiling vertex shader\n");
		return -1;
	};

	//shader.fs 가 fs 안으로 로딩됨
	if (!ReadFile(filenameFS, &fs)) {
		printf("Error compiling fragment shader\n");
		return -1;
	};

	// ShaderProgram 에 vs.c_str() 버텍스 쉐이더를 컴파일한 결과를 attach함
	AddShader(ShaderProgram, vs.c_str(), GL_VERTEX_SHADER);

	// ShaderProgram 에 fs.c_str() 프레그먼트 쉐이더를 컴파일한 결과를 attach함
	AddShader(ShaderProgram, fs.c_str(), GL_FRAGMENT_SHADER);

	GLint Success = 0;
	GLchar ErrorLog[1024] = { 0 };

	//Attach 완료된 shaderProgram 을 링킹함
	glLinkProgram(ShaderProgram);

	//링크가 성공했는지 확인
	glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &Success);

	if (Success == 0) {
		// shader program 로그를 받아옴
		glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
		std::cout << filenameVS << ", " << filenameFS << " Error linking shader program\n" << ErrorLog;
		return -1;
	}

	glValidateProgram(ShaderProgram);
	glGetProgramiv(ShaderProgram, GL_VALIDATE_STATUS, &Success);
	if (!Success) {
		glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
		std::cout << filenameVS << ", " << filenameFS << " Error validating shader program\n" << ErrorLog;
		return -1;
	}

	glUseProgram(ShaderProgram);
	std::cout << filenameVS << ", " << filenameFS << " Shader compiling is done.\n";

	return ShaderProgram;
}
unsigned char * Renderer::loadBMPRaw(const char * imagepath, unsigned int& outWidth, unsigned int& outHeight)
{
	std::cout << "Loading bmp file " << imagepath << " ... " << std::endl;
	outWidth = -1;
	outHeight = -1;
	// Data read from the header of the BMP file
	unsigned char header[54];
	unsigned int dataPos;
	unsigned int imageSize;
	// Actual RGB data
	unsigned char * data;

	// Open the file
	FILE * file = NULL;
	fopen_s(&file, imagepath, "rb");
	if (!file)
	{
		std::cout << "Image could not be opened, " << imagepath << " is missing. " << std::endl;
		return NULL;
	}

	if (fread(header, 1, 54, file) != 54)
	{
		std::cout << imagepath << " is not a correct BMP file. " << std::endl;
		return NULL;
	}

	if (header[0] != 'B' || header[1] != 'M')
	{
		std::cout << imagepath << " is not a correct BMP file. " << std::endl;
		return NULL;
	}

	if (*(int*)&(header[0x1E]) != 0)
	{
		std::cout << imagepath << " is not a correct BMP file. " << std::endl;
		return NULL;
	}

	if (*(int*)&(header[0x1C]) != 24)
	{
		std::cout << imagepath << " is not a correct BMP file. " << std::endl;
		return NULL;
	}

	dataPos = *(int*)&(header[0x0A]);
	imageSize = *(int*)&(header[0x22]);
	outWidth = *(int*)&(header[0x12]);
	outHeight = *(int*)&(header[0x16]);

	if (imageSize == 0)
		imageSize = outWidth * outHeight * 3;

	if (dataPos == 0)
		dataPos = 54;

	data = new unsigned char[imageSize];

	fread(data, 1, imageSize, file);

	fclose(file);

	std::cout << imagepath << " is succesfully loaded. " << std::endl;

	return data;
}

GLuint Renderer::CreatePngTexture(char * filePath)
{
	//Load Pngs: Load file and decode image.
	std::vector<unsigned char> image;
	unsigned width, height;
	unsigned error = lodepng::decode(image, width, height, filePath);
	if (error != 0)
	{
		lodepng_error_text(error);
		assert(error == 0);
		return -1;
	}

	GLuint temp;
	glGenTextures(1, &temp);

	glBindTexture(GL_TEXTURE_2D, temp);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image[0]);

	return temp;
}

void Renderer::CreateMyTexture()
{
	static const GLulong checkerboard[] =
	{
	0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000,
	0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF,
	0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000,
	0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF,
	0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000,
	0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF,
	0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000,
	0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF
	};

	glGenTextures(1, &m_MyTexture);
	glBindTexture(GL_TEXTURE_2D, m_MyTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 8, 8, 0, GL_RGBA, GL_UNSIGNED_BYTE, checkerboard);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);


}

GLuint Renderer::CreateBmpTexture(char * filePath)
{
	//Load Bmp: Load file and decode image.
	unsigned int width, height;
	unsigned char * bmp
		= loadBMPRaw(filePath, width, height);

	

	if (bmp == NULL)
	{
		std::cout << "Error while loading bmp file : " << filePath << std::endl;
		assert(bmp != NULL);
		return -1;
	}

	GLuint temp;
	glGenTextures(1, &temp);

	glBindTexture(GL_TEXTURE_2D, temp);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, bmp);

	return temp;
}

void Renderer::Test()
{
	glUseProgram(m_SolidRectShader);	

	GLuint uTime = glGetUniformLocation(m_SolidRectShader, "u_Time");
	glUniform1f(uTime, g_Time);
	//scale = 1.f;
	//glDrawArrays 에서 uTime에 항상 1값을 준다. 

	GLuint aPos = glGetAttribLocation(m_VBORect, "a_Position");
	GLuint aCol = glGetAttribLocation(m_VBOColor, "a_Color");

	glEnableVertexAttribArray(aPos);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBORect);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0); //사이즈에 0을 줘도 됨(명확할 때만)

	glEnableVertexAttribArray(aCol);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOColor);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 4, 0); //사이즈에 0을 줘도 됨(명확할 때만)

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(aPos);
	glDisableVertexAttribArray(aCol);	
	

	if (g_Time > 1.f)
		scale_speed = -scale_speed;
	else if(g_Time < 0.f)
		scale_speed = -scale_speed;
	
	g_Time += scale_speed;

	
	
}

void Renderer::DrawGrid()
{
	glUseProgram(m_VSSandboxShader);

	GLfloat points[] = { 0, 0, 0.1, 0.1, 0.3, 0.3, -0.2, -0.2, -0.1, -0.1 };

	GLuint uPoints = glGetUniformLocation(m_VSSandboxShader, "u_Points");
	glUniform2fv(uPoints, 5, points);

	GLuint uTime = glGetUniformLocation(m_VSSandboxShader, "u_Time");
	glUniform1f(uTime, g_Time);
	g_Time += 0.0005f;

	GLuint uTex = glGetUniformLocation(m_VSSandboxShader, "u_TextureSampler");
	glUniform1i(uTex, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_DIgimonTextures);

	

	int attribPosition = glGetAttribLocation(m_VSSandboxShader, "a_Position");
	glEnableVertexAttribArray(attribPosition);
	
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOGridMesh);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

	glDrawArrays(GL_LINE_STRIP, 0, m_GridMesh_Count);

	glDisableVertexAttribArray(0);

}

//4개씩 읽어라 
void Renderer::Draw_f4()
{
	glUseProgram(m_SolidRectShader);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBORect4);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 4, 0); //이렇게도가능


	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(0);
}

void Renderer::GenQuads(int num)
{
	//Quad_num = num;

	default_random_engine dre;

	dre.seed(static_cast<unsigned int>(time(NULL)));

	uniform_real_distribution<float> urd(-1.f, 1.f);

	uniform_real_distribution<float> urd_start_Time(0.f, 2.f);

	uniform_real_distribution<float> urd_life_Time(0.f, 1.f);	

	int verticesPerQuad = 6; //사각형당 필요한 버텍스 

	int floatsPerVertex = 3 + 3 + 2; //버텍스당 필요한 float 

	int countQuad = num;

	int vertex_size = countQuad * verticesPerQuad * floatsPerVertex;

	float *Quad_vertex = new float[vertex_size];

	float quad_size = 0.01f;

	for (int i = 0; i < countQuad; i++)
	{
		int index = i * verticesPerQuad * floatsPerVertex;

		float new_x = urd(dre);
		float new_y = urd(dre);		
		float Vel_x = urd(dre);
		float Vel_y = urd(dre);
		float Vel_z = 0.f;
		float startTime, lifeTime;

		startTime = urd_start_Time(dre);
		lifeTime = urd_life_Time(dre);
		
		Quad_vertex[index] = new_x - quad_size; index++;
		Quad_vertex[index] = new_y - quad_size; index++;
		Quad_vertex[index] = 0.f; index++;
		Quad_vertex[index] = Vel_x; index++;
		Quad_vertex[index] = Vel_y; index++;
		Quad_vertex[index] = Vel_z; index++;
		Quad_vertex[index] = startTime; index++;
		Quad_vertex[index] = lifeTime; index++;


		Quad_vertex[index] = new_x - quad_size; index++;
		Quad_vertex[index] = new_y + quad_size; index++;
		Quad_vertex[index] = 0.f; index++;
		Quad_vertex[index] = Vel_x; index++;
		Quad_vertex[index] = Vel_y; index++;
		Quad_vertex[index] = Vel_z; index++;
		Quad_vertex[index] = startTime; index++;
		Quad_vertex[index] = lifeTime; index++;

		Quad_vertex[index] = new_x + quad_size; index++;
		Quad_vertex[index] = new_y + quad_size; index++;
		Quad_vertex[index] = 0.f; index++;
		Quad_vertex[index] = Vel_x; index++;
		Quad_vertex[index] = Vel_y; index++;
		Quad_vertex[index] = Vel_z; index++;
		Quad_vertex[index] = startTime; index++;
		Quad_vertex[index] = lifeTime; index++;

		Quad_vertex[index] = new_x - quad_size; index++;
		Quad_vertex[index] = new_y - quad_size; index++;
		Quad_vertex[index] = 0.f; index++;
		Quad_vertex[index] = Vel_x; index++;
		Quad_vertex[index] = Vel_y; index++;
		Quad_vertex[index] = Vel_z; index++;
		Quad_vertex[index] = startTime; index++;
		Quad_vertex[index] = lifeTime; index++;

		Quad_vertex[index] = new_x + quad_size; index++;
		Quad_vertex[index] = new_y + quad_size; index++;
		Quad_vertex[index] = 0.f; index++;
		Quad_vertex[index] = Vel_x; index++;
		Quad_vertex[index] = Vel_y; index++;
		Quad_vertex[index] = Vel_z; index++;
		Quad_vertex[index] = startTime; index++;
		Quad_vertex[index] = lifeTime; index++;

		Quad_vertex[index] = new_x + quad_size; index++;
		Quad_vertex[index] = new_y - quad_size; index++;
		Quad_vertex[index] = 0.f; index++;
		Quad_vertex[index] = Vel_x; index++;
		Quad_vertex[index] = Vel_y; index++;
		Quad_vertex[index] = Vel_z; index++;
		Quad_vertex[index] = startTime; index++;
		Quad_vertex[index] = lifeTime;

	}	
	

	glGenBuffers(1, &m_QuadRect);
	glBindBuffer(GL_ARRAY_BUFFER, m_QuadRect);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertex_size, Quad_vertex, GL_STATIC_DRAW); //동적배열은 크기 못잼)

	quad_vertex_count = countQuad * verticesPerQuad * floatsPerVertex;
}


//원점인 곳에 사각형 생성 
void Renderer::GenQuads_New(int num)
{
	default_random_engine dre;

	dre.seed(static_cast<unsigned int>(time(NULL)));

	uniform_real_distribution<float> urd(-1.f, 1.f);

	uniform_real_distribution<float> urd_start_Time(0.f, 2.f);

	uniform_real_distribution<float> urd_life_Time(0.f, 1.f);

	uniform_real_distribution<float> urd_ratio(1.f, 3.f); //주기 

	uniform_real_distribution<float> urd_amp(0.f, 0.5f); //진폭 

	

	int verticesPerQuad = 6; //사각형당 필요한 버텍스 

	int floatsPerVertex = 3 + 3 + 2 + 2 + 1 + 3 + 1; //버텍스당 필요한 float 

	int countQuad = num;

	int vertex_size = countQuad * verticesPerQuad * floatsPerVertex;

	float *Quad_vertex = new float[vertex_size];

	float quad_size = 0.1f;

	for (int i = 0; i < countQuad; i++)
	{
		int index = i * verticesPerQuad * floatsPerVertex;

		float new_x = 0.f;
		float new_y = 0.f;
		float Vel_x = urd(dre);
		float Vel_y = urd(dre);
		float Vel_z = 0.f;
		float startTime, lifeTime;
		float new_ratio = urd_ratio(dre);
		float new_amp = urd_amp(dre);
		float Value = urd_life_Time(dre);	
		float r = urd_life_Time(dre);
		float g = urd_life_Time(dre);
		float b = urd_life_Time(dre);		
		float a = urd_life_Time(dre);

		startTime = urd_start_Time(dre);
		lifeTime = urd_life_Time(dre);

		Quad_vertex[index] = new_x - quad_size; index++;
		Quad_vertex[index] = new_y - quad_size; index++;
		Quad_vertex[index] = 0.f; index++;
		Quad_vertex[index] = Vel_x; index++;
		Quad_vertex[index] = Vel_y; index++;
		Quad_vertex[index] = Vel_z; index++;
		Quad_vertex[index] = startTime; index++;
		Quad_vertex[index] = lifeTime; index++;
		Quad_vertex[index] = new_ratio; index++;
		Quad_vertex[index] = new_amp; index++;
		Quad_vertex[index] = Value; index++;
		Quad_vertex[index] = r; index++;
		Quad_vertex[index] = g; index++;
		Quad_vertex[index] = b; index++;
		Quad_vertex[index] = a; index++;

		Quad_vertex[index] = new_x - quad_size; index++;
		Quad_vertex[index] = new_y + quad_size; index++;
		Quad_vertex[index] = 0.f; index++;
		Quad_vertex[index] = Vel_x; index++;
		Quad_vertex[index] = Vel_y; index++;
		Quad_vertex[index] = Vel_z; index++;
		Quad_vertex[index] = startTime; index++;
		Quad_vertex[index] = lifeTime; index++;
		Quad_vertex[index] = new_ratio; index++;
		Quad_vertex[index] = new_amp; index++;
		Quad_vertex[index] = Value; index++;
		Quad_vertex[index] = r; index++;
		Quad_vertex[index] = g; index++;
		Quad_vertex[index] = b; index++;
		Quad_vertex[index] = a; index++;

		Quad_vertex[index] = new_x + quad_size; index++;
		Quad_vertex[index] = new_y + quad_size; index++;
		Quad_vertex[index] = 0.f; index++;
		Quad_vertex[index] = Vel_x; index++;
		Quad_vertex[index] = Vel_y; index++;
		Quad_vertex[index] = Vel_z; index++;
		Quad_vertex[index] = startTime; index++;
		Quad_vertex[index] = lifeTime; index++;
		Quad_vertex[index] = new_ratio; index++;
		Quad_vertex[index] = new_amp; index++;
		Quad_vertex[index] = Value; index++;
		Quad_vertex[index] = r; index++;
		Quad_vertex[index] = g; index++;
		Quad_vertex[index] = b; index++;
		Quad_vertex[index] = a; index++;

		Quad_vertex[index] = new_x - quad_size; index++;
		Quad_vertex[index] = new_y - quad_size; index++;
		Quad_vertex[index] = 0.f; index++;
		Quad_vertex[index] = Vel_x; index++;
		Quad_vertex[index] = Vel_y; index++;
		Quad_vertex[index] = Vel_z; index++;
		Quad_vertex[index] = startTime; index++;
		Quad_vertex[index] = lifeTime; index++;
		Quad_vertex[index] = new_ratio; index++;
		Quad_vertex[index] = new_amp; index++;
		Quad_vertex[index] = Value; index++;
		Quad_vertex[index] = r; index++;
		Quad_vertex[index] = g; index++;
		Quad_vertex[index] = b; index++;
		Quad_vertex[index] = a; index++;

		Quad_vertex[index] = new_x + quad_size; index++;
		Quad_vertex[index] = new_y + quad_size; index++;
		Quad_vertex[index] = 0.f; index++;
		Quad_vertex[index] = Vel_x; index++;
		Quad_vertex[index] = Vel_y; index++;
		Quad_vertex[index] = Vel_z; index++;
		Quad_vertex[index] = startTime; index++;
		Quad_vertex[index] = lifeTime; index++;
		Quad_vertex[index] = new_ratio; index++;
		Quad_vertex[index] = new_amp; index++;
		Quad_vertex[index] = Value; index++;
		Quad_vertex[index] = r; index++;
		Quad_vertex[index] = g; index++;
		Quad_vertex[index] = b; index++;
		Quad_vertex[index] = a; index++;

		Quad_vertex[index] = new_x + quad_size; index++;
		Quad_vertex[index] = new_y - quad_size; index++;
		Quad_vertex[index] = 0.f; index++;
		Quad_vertex[index] = Vel_x; index++;
		Quad_vertex[index] = Vel_y; index++;
		Quad_vertex[index] = Vel_z; index++;
		Quad_vertex[index] = startTime; index++;
		Quad_vertex[index] = lifeTime; index++;
		Quad_vertex[index] = new_ratio; index++;
		Quad_vertex[index] = new_amp; index++;
		Quad_vertex[index] = Value; index++;
		Quad_vertex[index] = r; index++;
		Quad_vertex[index] = g; index++;
		Quad_vertex[index] = b; index++;
		Quad_vertex[index] = a; 

	}


	glGenBuffers(1, &m_QuadRect);
	glBindBuffer(GL_ARRAY_BUFFER, m_QuadRect);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertex_size, Quad_vertex, GL_STATIC_DRAW); //동적배열은 크기 못잼)

	quad_vertex_count = countQuad * verticesPerQuad * floatsPerVertex;

	cout << quad_vertex_count << endl;
}


void Renderer::Draw_Quads()
{
	glUseProgram(m_SolidRectShader);

	
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, m_QuadRect);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

	glDrawArrays(GL_TRIANGLES, 0, 6 * Quad_num * 3);	

	glDisableVertexAttribArray(0);
	
}

void Renderer::Draw_SimpleVel()
{
	glUseProgram(m_SimpleVelShader);

	GLuint uTime = glGetUniformLocation(m_SolidRectShader, "u_Time");
	glUniform1f(uTime, g_Time);
	g_Time += 0.0001f;

	GLuint aPos = glGetAttribLocation(m_SimpleVelShader, "a_Position");
	GLuint aVel = glGetAttribLocation(m_SimpleVelShader, "a_Vel");

	glEnableVertexAttribArray(aPos);
	glEnableVertexAttribArray(aVel);
	glBindBuffer(GL_ARRAY_BUFFER, m_QuadRect);
	glVertexAttribPointer(aPos, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, 0);
	glVertexAttribPointer(aVel, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (GLvoid*)(sizeof(float)*3));

	glDrawArrays(GL_TRIANGLES, 0, 6 * Quad_num * 3 * 2);
	//glDrawArrays(GL_LINE_STRIP, 0, 6 * Quad_num * 3);

	glDisableVertexAttribArray(aPos);
	glDisableVertexAttribArray(aVel);
	
}

void Renderer::Lecture5()
{
	glUseProgram(m_SimpleVelShader);

	GLuint uTime = glGetUniformLocation(m_SolidRectShader, "u_Time");
	glUniform1f(uTime, g_Time);
	g_Time += 0.0001f;
	GLuint uRepeat = glGetUniformLocation(m_SolidRectShader, "u_Repeat");
	

	GLuint aPos = glGetAttribLocation(m_SimpleVelShader, "a_Position");
	GLuint aVel = glGetAttribLocation(m_SimpleVelShader, "a_Vel");
	GLuint aStartLife = glGetAttribLocation(m_SimpleVelShader, "a_StartLife");

	glEnableVertexAttribArray(aPos);
	glEnableVertexAttribArray(aVel);
	glEnableVertexAttribArray(aStartLife);
	glBindBuffer(GL_ARRAY_BUFFER, m_QuadRect);
	glVertexAttribPointer(aPos, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, 0);
	glVertexAttribPointer(aVel, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (GLvoid*)(sizeof(float) * 3));
	glVertexAttribPointer(aStartLife, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (GLvoid*)(sizeof(float) * 6));

	glDrawArrays(GL_TRIANGLES, 0, quad_vertex_count);
	//glDrawArrays(GL_LINE_STRIP, 0, 6 * Quad_num * 3);

	glDisableVertexAttribArray(aPos);
	glDisableVertexAttribArray(aVel);
	glDisableVertexAttribArray(aStartLife);
}

void Renderer::Lecture6()
{
	glUseProgram(m_FillAllShader);

	GLuint uTime = glGetUniformLocation(m_FillAllShader, "u_Time");
	glUniform1f(uTime, g_Time);
	g_Time += 0.0001f;

	int uniformTex = glGetUniformLocation(m_FillAllShader, "uTexSampler");
	glUniform1i(uniformTex, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_ParticleTexture);


	GLuint aPos = glGetAttribLocation(m_FillAllShader, "a_Position");
	GLuint ratio_amp = glGetAttribLocation(m_FillAllShader, "ratio_amp");
	GLuint aStartLife = glGetAttribLocation(m_FillAllShader, "a_StartLife");
	GLuint aVel = glGetAttribLocation(m_FillAllShader, "a_Vel");
	GLuint Value = glGetAttribLocation(m_FillAllShader, "Value");
	
	glEnableVertexAttribArray(aPos);
	glEnableVertexAttribArray(aStartLife);
	glEnableVertexAttribArray(ratio_amp);
	glEnableVertexAttribArray(aVel);
	glEnableVertexAttribArray(Value);

	
	glBindBuffer(GL_ARRAY_BUFFER, m_QuadRect);
	glVertexAttribPointer(aPos, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 11, 0);
	glVertexAttribPointer(aVel, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 11, (GLvoid*)(sizeof(float) * 3));
	glVertexAttribPointer(aStartLife, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 11, (GLvoid*)(sizeof(float) * 6));	
	glVertexAttribPointer(ratio_amp, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 11, (GLvoid*)(sizeof(float) * 8));
	glVertexAttribPointer(Value, 1, GL_FLOAT, GL_FALSE, sizeof(float) * 11, (GLvoid*)(sizeof(float) * 10));

	glDrawArrays(GL_TRIANGLES, 0, quad_vertex_count);
	//glDrawArrays(GL_LINE_STRIP, 0, 6 * Quad_num * 3);

	glDisableVertexAttribArray(aPos);
	glDisableVertexAttribArray(aStartLife);
	glDisableVertexAttribArray(ratio_amp);
	glDisableVertexAttribArray(aVel);
	glDisableVertexAttribArray(Value);
}

void Renderer::Lecture7()
{
	glUseProgram(m_FillAllShader);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	GLuint uTime = glGetUniformLocation(m_FillAllShader, "u_Time");
	glUniform1f(uTime, g_Time);
	g_Time += 0.0001f;

	GLuint aPos = glGetAttribLocation(m_FillAllShader, "a_Position");
	GLuint ratio_amp = glGetAttribLocation(m_FillAllShader, "ratio_amp");
	GLuint aStartLife = glGetAttribLocation(m_FillAllShader, "a_StartLife");
	GLuint aVel = glGetAttribLocation(m_FillAllShader, "a_Vel");
	GLuint Value = glGetAttribLocation(m_FillAllShader, "Value");
	GLuint Color = glGetAttribLocation(m_FillAllShader, "a_color");

	glEnableVertexAttribArray(aPos);
	glEnableVertexAttribArray(aStartLife);
	glEnableVertexAttribArray(ratio_amp);
	glEnableVertexAttribArray(aVel);
	glEnableVertexAttribArray(Value);
	glEnableVertexAttribArray(Color);


	glBindBuffer(GL_ARRAY_BUFFER, m_QuadRect);
	glVertexAttribPointer(aPos, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 15, 0);
	glVertexAttribPointer(aVel, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 15, (GLvoid*)(sizeof(float) * 3));
	glVertexAttribPointer(aStartLife, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 15, (GLvoid*)(sizeof(float) * 6));
	glVertexAttribPointer(ratio_amp, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 15, (GLvoid*)(sizeof(float) * 8));
	glVertexAttribPointer(Value, 1, GL_FLOAT, GL_FALSE, sizeof(float) * 15, (GLvoid*)(sizeof(float) * 10));
	glVertexAttribPointer(Color, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 15, (GLvoid*)(sizeof(float) * 11));

	glDrawArrays(GL_TRIANGLES, 0, quad_vertex_count);
	//glDrawArrays(GL_LINE_STRIP, 0, 6 * Quad_num * 3);

	glDisableVertexAttribArray(aPos);
	glDisableVertexAttribArray(aStartLife);
	glDisableVertexAttribArray(ratio_amp);
	glDisableVertexAttribArray(aVel);
	glDisableVertexAttribArray(Value);
	glDisableVertexAttribArray(Color);
}


void Renderer::Lecture8()
{
	GLfloat points[] = { 0, 0, 0.1, 0.1, 0.3, 0.3, -0.2, -0.2, -0.1, -0.1};

	GLuint uPoints = glGetUniformLocation(m_SimpleVelShader, "u_Points");
	glUniform2fv(uPoints, 5, points);

	GLuint uTime = glGetUniformLocation(m_SimpleVelShader, "u_Time");
	glUniform1f(uTime, g_Time);
	g_Time += 0.0001f;

	glUseProgram(m_SimpleVelShader);

	GLuint aPos = glGetAttribLocation(m_SimpleVelShader, "a_Position");
	GLuint aRG = glGetAttribLocation(m_SimpleVelShader, "a_RG");

	glEnableVertexAttribArray(aPos);
	glEnableVertexAttribArray(aRG);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBORect);	
	glVertexAttribPointer(aPos, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0);
	glVertexAttribPointer(aRG, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (GLvoid*)(sizeof(float) * 3));

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(aPos);
	glDisableVertexAttribArray(aRG);
}

void Renderer::FillAll()
{
	glUseProgram(m_FillAllShader);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Renderer::DrawSimpleTexture()
{
	glUseProgram(m_TextureShader);

	GLuint uTime = glGetUniformLocation(m_TextureShader, "u_Time");
	glUniform1f(uTime, g_Time);
	g_Time += 0.0001f;

	int uniformTex = glGetUniformLocation(m_TextureShader, "u_Texture");
	glUniform1i(uniformTex, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_ParticleTexture);

	GLuint aPos = glGetAttribLocation(m_TextureShader, "a_Position");
	GLuint aUV = glGetAttribLocation(m_TextureShader, "a_UV");
	

	glEnableVertexAttribArray(aPos);
	glEnableVertexAttribArray(aUV);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBOTexture);
	glVertexAttribPointer(aPos, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0);
	glVertexAttribPointer(aUV, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (GLvoid*)(sizeof(float) * 3));


	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(aPos);
	glDisableVertexAttribArray(aUV);
}

void Renderer::DrawCheckerboard()
{
	glUseProgram(m_TextureShader);

	GLuint uTime = glGetUniformLocation(m_TextureShader, "u_Time");
	glUniform1f(uTime, g_Time);
	g_Time += 0.0001f;

	int uniformTex = glGetUniformLocation(m_TextureShader, "u_Texture");
	glUniform1i(uniformTex, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_MyTexture);

	GLuint aPos = glGetAttribLocation(m_TextureShader, "a_Position");
	GLuint aUV = glGetAttribLocation(m_TextureShader, "a_UV");


	glEnableVertexAttribArray(aPos);
	glEnableVertexAttribArray(aUV);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBOTexture);
	glVertexAttribPointer(aPos, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0);
	glVertexAttribPointer(aUV, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (GLvoid*)(sizeof(float) * 3));


	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(aPos);
	glDisableVertexAttribArray(aUV);
}

void Renderer::DrawRGBTexture()
{
	glUseProgram(m_RGBTextureShader);

	GLuint uTime = glGetUniformLocation(m_RGBTextureShader, "u_Time");
	glUniform1f(uTime, g_Time);
	g_Time += 0.0001f;

	int uniformTex = glGetUniformLocation(m_RGBTextureShader, "u_Texture");
	glUniform1i(uniformTex, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_RGBTexture);

	GLuint aPos = glGetAttribLocation(m_RGBTextureShader, "a_Position");
	GLuint aUV = glGetAttribLocation(m_RGBTextureShader, "a_UV");


	glEnableVertexAttribArray(aPos);
	glEnableVertexAttribArray(aUV);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBOTexture);
	glVertexAttribPointer(aPos, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0);
	glVertexAttribPointer(aUV, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (GLvoid*)(sizeof(float) * 3));


	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(aPos);
	glDisableVertexAttribArray(aUV);
}

void Renderer::DrawMultiTexture()
{
	glUseProgram(m_RGBTextureShader);

	GLuint uTime = glGetUniformLocation(m_RGBTextureShader, "u_Time");
	glUniform1f(uTime, g_Time);
	g_Time += 0.0001f;

	int uniformTex = glGetUniformLocation(m_RGBTextureShader, "u_Texture");
	glUniform1i(uniformTex, tex_int);

	int uniformTex2 = glGetUniformLocation(m_RGBTextureShader, "u_Texture2");
	glUniform1i(uniformTex, tex_int);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_DIgimonTextures);
	
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, m_DIgimonTextures2);

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, m_DIgimonTextures3);

	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, m_DIgimonTextures4);

	if (g_Time > 1.f)
	{
		g_Time = 0.f;
		tex_int++; 

		if (tex_int > 3)
			tex_int = 0;
	}

	GLuint aPos = glGetAttribLocation(m_RGBTextureShader, "a_Position");
	GLuint aUV = glGetAttribLocation(m_RGBTextureShader, "a_UV");


	glEnableVertexAttribArray(aPos);
	glEnableVertexAttribArray(aUV);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBOTexture);
	glVertexAttribPointer(aPos, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0);
	glVertexAttribPointer(aUV, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (GLvoid*)(sizeof(float) * 3));


	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(aPos);
	glDisableVertexAttribArray(aUV);
}

void Renderer::DrawOneTexture()
{
	glUseProgram(m_OneTextureShader);

	GLuint uTime = glGetUniformLocation(m_OneTextureShader, "u_Time");
	glUniform1f(uTime, g_Time);
	g_Time += 0.0001f;

	GLuint select = glGetUniformLocation(m_OneTextureShader, "select_num");
	glUniform1i(select, select_num);	

	int uniformTex = glGetUniformLocation(m_OneTextureShader, "u_Texture");
	glUniform1i(uniformTex, 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_OneTexture);	

	if (g_Time > 0.001f)
	{
		
		g_Time = 0.f;
		select_num++;		

		if (select_num > 9)
			select_num = 0;
	}

	GLuint aPos = glGetAttribLocation(m_OneTextureShader, "a_Position");
	GLuint aUV = glGetAttribLocation(m_OneTextureShader, "a_UV");


	glEnableVertexAttribArray(aPos);
	glEnableVertexAttribArray(aUV);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBOTexture);
	glVertexAttribPointer(aPos, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0);
	glVertexAttribPointer(aUV, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (GLvoid*)(sizeof(float) * 3));


	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(aPos);
	glDisableVertexAttribArray(aUV);
}

void Renderer::DrawSprite(GLuint num)
{
	glUseProgram(m_SpriteShader);

	GLuint uTime = glGetUniformLocation(m_SpriteShader, "u_Time");
	glUniform1f(uTime, g_Time);
	g_Time += 0.0001f;

	GLuint uNumber = glGetUniformLocation(m_SpriteShader, "u_Number");
	glUniform1f(uNumber, float(num));

	GLuint Resolx = glGetUniformLocation(m_SpriteShader, "u_Resolx");
	glUniform1f(Resolx, 8.f );

	GLuint Resoly = glGetUniformLocation(m_SpriteShader, "u_Resoly");
	glUniform1f(Resoly, 8.f);
	

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_BearTexture);
	

	GLuint aPos = glGetAttribLocation(m_SpriteShader, "a_Position");
	GLuint aUV = glGetAttribLocation(m_SpriteShader, "a_UV");


	glEnableVertexAttribArray(aPos);
	glEnableVertexAttribArray(aUV);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBOTexture);
	glVertexAttribPointer(aPos, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0);
	glVertexAttribPointer(aUV, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (GLvoid*)(sizeof(float) * 3));


	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(aPos);
	glDisableVertexAttribArray(aUV);
}


void Renderer::DrawProj()
{
	glUseProgram(m_OrthoProjectionShader);

	GLfloat points[] = { 0, 0, 0.1, 0.1, 0.3, 0.3, -0.2, -0.2, -0.1, -0.1 };

	GLuint uPoints = glGetUniformLocation(m_OrthoProjectionShader, "u_Points");
	glUniform2fv(uPoints, 5, points);

	GLuint uTime = glGetUniformLocation(m_OrthoProjectionShader, "u_Time");
	glUniform1f(uTime, g_Time);
	g_Time += 0.0005f;

	GLuint uTex = glGetUniformLocation(m_OrthoProjectionShader, "u_TextureSampler");
	glUniform1i(uTex, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_HeightTexture);

	GLuint uTex2 = glGetUniformLocation(m_OrthoProjectionShader, "u_heightmap");
	glUniform1i(uTex2, 1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, m_HeightTexture);

	GLuint uTex3 = glGetUniformLocation(m_OrthoProjectionShader, "u_GrassTexture");
	glUniform1i(uTex3, 2);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, m_GrassTexture);

	GLuint uViewProjMat = glGetUniformLocation(m_OrthoProjectionShader, "u_ProjView");
	glUniformMatrix4fv(uViewProjMat, 1, GL_FALSE, &m_ViewProjMat4[0][0]);

	int attribPosition = glGetAttribLocation(m_OrthoProjectionShader, "a_Position");
	glEnableVertexAttribArray(attribPosition);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOGridMesh);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

	glDrawArrays(GL_LINE_STRIP, 0, m_GridMesh_Count);

	glDisableVertexAttribArray(0);
}

void Renderer::Cube()
{	

	glUseProgram(m_OrthoProjectionShader);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	GLuint projView = glGetUniformLocation(m_OrthoProjectionShader, "u_ProjView");

	glUniformMatrix4fv(projView, 1, GL_FALSE, &m_ViewProjMat4[0][0]);

	int attribPosition = glGetAttribLocation(m_OrthoProjectionShader, "a_Position");
	int attribNormal = glGetAttribLocation(m_OrthoProjectionShader, "a_Normal");
	int attribColor = glGetAttribLocation(m_OrthoProjectionShader, "a_Color");

	glEnableVertexAttribArray(attribPosition);
	glEnableVertexAttribArray(attribNormal);
	glEnableVertexAttribArray(attribColor);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO_Cube);

	glVertexAttribPointer(attribPosition, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 10, 0);
	glVertexAttribPointer(attribNormal, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 10, (GLvoid*)(sizeof(float) * 3));
	glVertexAttribPointer(attribColor, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 10, (GLvoid*)(sizeof(float) * 6));

	glDrawArrays(GL_TRIANGLES, 0, 36);

	glDisableVertexAttribArray(attribPosition);
	glDisableVertexAttribArray(attribNormal);
	glDisableVertexAttribArray(attribColor);
}


void Renderer::DrawHeightMap()
{
	glUseProgram(m_VertexAnimationShader);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	GLfloat Points[] = { -0.2, -0.2, 0.5, 0.5, 0.2,0.2, 0.3,0.3,-0.3 - 0.3 };
	static float gTime = 0;
	gTime += 0.0001f;

	GLuint projView = glGetUniformLocation(m_VertexAnimationShader, "u_ProjView");

	glUniformMatrix4fv(projView, 1, GL_FALSE, &m_ViewProjMat4[0][0]);

	GLuint uTex = glGetUniformLocation(m_VertexAnimationShader, "u_Texture");
	glUniform1i(uTex, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_HeightTexture);

	GLuint uHeight = glGetUniformLocation(m_VertexAnimationShader, "u_heightMapTexture");
	glUniform1i(uHeight, 1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, m_HeightTexture);

	GLuint uSnow = glGetUniformLocation(m_VertexAnimationShader, "u_snowTexture");
	glUniform1i(uSnow, 2);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, m_SnowTexture);

	GLuint uGrass = glGetUniformLocation(m_VertexAnimationShader, "u_grassTexture");
	glUniform1i(uGrass, 3);
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, m_GrassTexture);

	int attribPosition = glGetAttribLocation(m_VertexAnimationShader, "a_Position");

	GLuint uTime = glGetUniformLocation(m_VertexAnimationShader, "u_Time");
	glUniform1f(uTime, gTime);

	GLuint uPoints = glGetUniformLocation(m_VertexAnimationShader, "u_Points");
	glUniform2fv(uPoints, 5, Points);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOGridMesh);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

	glDrawArrays(GL_TRIANGLES, 0, m_GridMesh_Count);

	glDisableVertexAttribArray(0);
}
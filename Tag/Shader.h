#ifndef SHADER_H
#define SHADER_H

#include "StandardIncludes.h"

class Shader
{
public:
	Shader();
	virtual ~Shader();

	GLuint GetProgramID() { return programID; }
	GLuint GetAttrVertices() { return attrVertices; }
	GLuint GetAttrColors() { return atrrColors; }
	GLuint GetAttrTexCoords() { return attrTexCoords; }
	GLuint GetSampler1() { return sampler1;  }
	GLuint GetSampler2() { return sampler2; }
	GLuint GetAttrWVP() { return attrWVP; }

	void LoadShaders(const char* _vertexFilePath, const char* _fragmentFilePath);
	void Cleanup();

private:
	void CreateShaderProgram(const char* _vertexFilePath, const char* _fragmentFilePath);
	GLuint LoadShaderFile(const char* _filePath, GLenum _type);
	void LoadAttributes();
	void EvaluateShader(int _infoLength, GLuint _id);

	GLuint programID;
	GLuint attrVertices;
	GLuint atrrColors;
	GLuint attrTexCoords;
	GLuint sampler1;
	GLuint sampler2;
	GLuint attrWVP;
	GLint result;
	int infoLogLength;

};

#endif


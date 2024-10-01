#include "Shader.h"

Shader::Shader()
{
	programID = 0;
	attrVertices = 0;
	result = GL_FALSE;
	infoLogLength = 0;
	attrWVP = 0;
	atrrColors = 0;
}

Shader::~Shader()
{
	Cleanup();
}

void Shader::Cleanup()
{
	if (programID != 0)
	{
		glDeleteProgram(programID);
		programID = 0;
	}
}

void Shader::LoadShaders(const char* _vertexFilePath, const char* _fragmentFilePath)
{
	CreateShaderProgram(_vertexFilePath, _fragmentFilePath);
	LoadAttributes();
}

void Shader::CreateShaderProgram(const char* _vertexFilePath, const char* _fragmentFilePath)
{
	programID = glCreateProgram();
	GLuint vertexShaderID = LoadShaderFile(_vertexFilePath, GL_VERTEX_SHADER);
	GLuint fragmentShaderID = LoadShaderFile(_fragmentFilePath, GL_FRAGMENT_SHADER);
	glLinkProgram(programID);

	glGetProgramiv(programID, GL_LINK_STATUS, &result);
	glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
	EvaluateShader(infoLogLength, programID);

	glDetachShader(programID, vertexShaderID);
	glDetachShader(programID, fragmentShaderID);
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);
}

void Shader::LoadAttributes()
{
	attrVertices = glGetAttribLocation(programID, "vertices");
	atrrColors = glGetAttribLocation(programID, "colors");
	attrWVP = glGetUniformLocation(programID, "WVP");
}

void Shader::EvaluateShader(int _infoLength, GLuint _id)
{
	if (_infoLength > 0)
	{
		vector<char> errorMessage(_infoLength + 1);
		glGetShaderInfoLog(_id, _infoLength, NULL, &errorMessage[0]);
		M_ASSERT(0, ("%s\n", &errorMessage[0]));
	}
}

GLuint Shader::LoadShaderFile(const char* _filePath, GLenum _type)
{
	GLuint shaderId = glCreateShader(_type);

	string shaderCode;
	ifstream shaderStream(_filePath, ios::in);
	M_ASSERT(shaderStream.is_open(), ("Imposible to open %s, are you in right directory?\n", _filePath));
	string Line = "";

	while (getline(shaderStream, Line))
	{
		shaderCode += "\n" + Line;
	}
	shaderStream.close();

	char const* sourcePointer = shaderCode.c_str();
	glShaderSource(shaderId, 1, &sourcePointer, NULL);
	glCompileShader(shaderId);

	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);
	glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &infoLogLength);
	EvaluateShader(infoLogLength, shaderId);

	glAttachShader(programID, shaderId);

	return shaderId;
}







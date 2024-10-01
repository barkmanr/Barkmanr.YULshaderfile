#ifndef MESH_H
#define MESH_H

#include "StandardIncludes.h"
class Shader;

class Mesh //Shape
{
public:
	Mesh();
	virtual ~Mesh();

	bool getClean() { return isClean; }

	void Create(Shader* _shader);
	void Cleanup();
	void Render(glm::mat4 wvp);

	void UpdateVertex(float x, float y); //bonus

	void setBlack();
	void setNormal();
	void setBuffers();

	void Scale();


private:
	Shader* shader;
	GLuint vertexBuffer;
	GLuint indexBuffer;
	vector<GLfloat> m_vertexData; //Points
	vector<GLubyte> indexData;
	glm::mat4 world;
	bool isClean;
	float lastScaler;
	float deltaTime;
};

#endif MESH_H


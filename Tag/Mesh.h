#ifndef MESH_H
#define MESH_H

#include "StandardIncludes.h"

class Texture;
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
	void setBuffers();

private:
	Shader* shader;
	Texture* texture;
	Texture* texture2;
	GLuint vertexBuffer;
	GLuint indexBuffer;
	vector<GLfloat> m_vertexData; //Points
	vector<GLubyte> indexData;

	glm::mat4 world;
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec2 stroll;

	bool isClean;
	float lastScaler;
	float deltaTime;
};

#endif MESH_H


#include "Mesh.h"
#include "Shader.h"

Mesh::Mesh()
{
	shader = nullptr;
	vertexBuffer = 0;
	isClean = true;
	indexBuffer = 0;
	world = glm::mat4(1);
	lastScaler = 1.0f; //start with one to not mess with scale
	deltaTime = 0.0f;
}

Mesh::~Mesh() { Cleanup(); }

void Mesh::Cleanup()
{
	if (!isClean)
	{
		glDeleteBuffers(1, &vertexBuffer);
		glDeleteBuffers(1, &indexBuffer);
		isClean = true;
	}
}

void Mesh::Create(Shader* _shader)
{
	shader = _shader;

	isClean = false;

	indexData = {
		0,6,1,     0,11,6,     1,4,0,     1,8,4,
		1,10,8,    2,5,3,      2,9,5,     2,11,9,
		3,7,2,     3,10,7,     4,8,5,     4,9,0,
		5,8,3,     5,9,4,      6,10,1,    6,11,7,
		7,10,6,    7,11,2,     8,10,3,    9,11,0
	};

	setNormal();
}

///


void Mesh::Render(glm::mat4 mvp)
{
	glUseProgram(shader->GetProgramID());

	Scale();
	//world = glm::scale(world, { 0,1,0 }); //rotation
	mvp *= world; //mvp = world, view, progecion
	glUniformMatrix4fv(shader->GetAttrWVP(), 1, FALSE, &mvp[0][0]);

	glEnableVertexAttribArray(shader->GetAttrVertices());

	glVertexAttribPointer //position? don't know what these do
	(
		shader->GetAttrVertices(),
		3, //size?
		GL_FLOAT,
		GL_FALSE, //is normazlized?
		7 * sizeof(float), //stride: x,y,z,r,g,b,a skip for next vertex
		(void*)0
	);

	glEnableVertexAttribArray(shader->GetAttrColors());

	glVertexAttribPointer //color
	(
		shader->GetAttrColors(),
		4, //size?
		GL_FLOAT,
		GL_FALSE, //is normazlized?
		7 * sizeof(float), //stride: x,y,z,r,g,b,a skip for next vertex
		(void*)(3 * sizeof(float))
	);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawElements(GL_TRIANGLES, indexData.size(), GL_UNSIGNED_BYTE, (void*)0); //Shape
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDisableVertexAttribArray(shader->GetAttrVertices());
	glDisableVertexAttribArray(shader->GetAttrColors());
}


void Mesh::UpdateVertex(float x, float y) //my stuff, need to fix for new triangle
{

	//Cleanup();
	//isClean = false;


	if (x > 0.0f) //D
	{
		world = glm::rotate(world, 0.005f, { 0,1,0 });
	}
	else if (x < 0.0f) //A
	{
		world = glm::rotate(world, -0.005f, { 0,1,0 });
	}
	else if (y > 0.0f) //W
	{
		world = glm::rotate(world, 0.005f, { 1,0,0 });
	}
	else if (y < 0.0f) //S
	{
		world = glm::rotate(world, -0.005f, { 1,0,0 });
	}


	/*
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, m_vertexData.size() * sizeof(float), m_vertexData.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ARRAY_BUFFER, indexData.size() * sizeof(float), indexData.data(), GL_STATIC_DRAW);
	*/

}

void Mesh::setBlack()
{
	Cleanup();
	isClean = false;
	for (int row = 0; row < m_vertexData.size() / 7; row++)
	{
		m_vertexData[row * 7 + 3] = 0;
		m_vertexData[row * 7 + 4] = 0;
		m_vertexData[row * 7 + 5] = 0;
	}
	setBuffers();
}

void Mesh::setNormal()
{
	Cleanup();
	isClean = false;
	float a = 26.0f;
	float b = 42.0f;
	float c = 0.0f;


	m_vertexData = //points of triangle
	{  //x,   y,     z       r,    g,    b,    a    (7 floats)
		-a, c, b,	1.0f, 0.0f, 0.0f, 1.0f, //v1
		a, c, b,	1.0f, 0.549f, 0.0f, 1.0f, //v2
		-a, c, -b,	1.0f, 1.0f, 0.0f, 1.0f, //v3
		a, c, -b,	1.0f, 0.0f, 0.0f, 1.0f, //v4

		c, b, a,	0.0f, 0.0f, 1.0f, 1.0f, //v5
		c, b, -a,	0.294f, 0.0f, 0.51f, 1.0f, //v6
		c, -b, a,	0.502f, 0.0f, 0.502f, 1.0f, //v7
		c, -b, -a,	1.0f, 1.0f, 1.0f, 1.0f, //v8

		b, a, c,	0.0f, 1.0f, 1.0f, 1.0f, //v9
		-b, a, c,	0.0f, 0.0f, 0.0f, 1.0f, //v10
		b, -a, c,	0.118f, 0.565f, 1.0f, 1.0f, //v11
		-b, -a, c,	0.863f, 0.078f, 0.235f, 1.0f, //v12
		//pos			//color
	};
	setBuffers();
}

void Mesh::setBuffers()
{
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, m_vertexData.size() * sizeof(float), m_vertexData.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ARRAY_BUFFER, indexData.size() * sizeof(float), indexData.data(), GL_STATIC_DRAW);
}

void Mesh::Scale()
{
	deltaTime = glfwGetTime();
	int add = (int)deltaTime % 4;
	float cTime = deltaTime - (int)deltaTime + add - 2.0f;


	if (cTime < 0.0f)
	{
		cTime = cTime * -1.0f;
		world = glm::scale(world, { 1.0f / lastScaler, 1.0f / lastScaler, 1.0f / lastScaler }); //revert changes / set to one
		world = glm::scale(world, { cTime,cTime,cTime });
	}
	else
	{
		world = glm::scale(world, { 1.0f / lastScaler, 1.0f / lastScaler, 1.0f / lastScaler }); //revert changes / set to one
		world = glm::scale(world, { cTime,cTime,cTime });
	}
	lastScaler = cTime;

}


/*
 deltaTime = glfwGetTime();
	int add = (int)deltaTime % 2;
	float cTime = deltaTime - (int)deltaTime + add;

	if (cTime < 0.1f)
	{
		return;
	}

	world = glm::scale(world, {1.0f / lastScaler, 1.0f / lastScaler, 1.0f / lastScaler }); //revert changes / set to one
	world = glm::scale(world, {cTime,cTime,cTime});
	lastScaler = cTime;
*/
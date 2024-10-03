#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"

Mesh::Mesh()
{
	shader = nullptr;
	texture = nullptr;
	texture2 = nullptr;
	vertexBuffer = 0;
	isClean = true;
	indexBuffer = 0;
	world = glm::mat4(1);
	lastScaler = 1.0f; //start with one to not mess with scale
	deltaTime = 0.0f;
}

Mesh::~Mesh() 
{ 
	Cleanup();
	if (texture != nullptr) 
	{
		delete texture;
		texture = nullptr;
	}
	if (texture2 != nullptr)
	{
		delete texture2;
		texture2 = nullptr;
	}
}

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
	texture = new Texture();
	texture->LoadTexture("../Assets/Textures/DeVito.jpg");

	texture2 = new Texture();
	texture2->LoadTexture("../Assets/Textures/Tacos.jpg");

	isClean = false;

	indexData = {
		2,0,3,	2,1,0,
		2,3,0,	2,0,1
	};

	setNormal();
}

///


void Mesh::Render(glm::mat4 mvp)
{
	glUseProgram(shader->GetProgramID());

	Scale(); //up + down
	mvp *= world; //mvp = world, view, progecion

	glUniformMatrix4fv(shader->GetAttrWVP(), 1, FALSE, &mvp[0][0]);
	glEnableVertexAttribArray(shader->GetAttrVertices());

	glVertexAttribPointer //position? don't know what these do
	(
		shader->GetAttrVertices(),
		3, //size?
		GL_FLOAT,
		GL_FALSE, //is normazlized?
		8 * sizeof(float), //stride: x,y,z,r,g,b,a skip for next vertex
		(void*)0
	);

	glEnableVertexAttribArray(shader->GetAttrColors());

	glVertexAttribPointer //color
	(
		shader->GetAttrColors(),
		4, //size?
		GL_FLOAT,
		GL_FALSE, //is normazlized?
		8 * sizeof(float), //stride: x,y,z,r,g,b,a skip for next vertex
		(void*)(3 * sizeof(float))
	);

	glEnableVertexAttribArray(shader->GetAttrTexCoords());
	glVertexAttribPointer(
		shader->GetAttrTexCoords(),
		2, GL_FLOAT, GL_FALSE,
		8 * sizeof(float),
		(void*)(6 * sizeof(float))
	);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->GetTexture());
	glUniform1i(shader->GetSampler1(), 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2->GetTexture());
	glUniform1i(shader->GetSampler2(), 1);

	glDrawElements(GL_TRIANGLES, indexData.size(), GL_UNSIGNED_BYTE, (void*)0); //Shape
	glDisableVertexAttribArray(shader->GetAttrVertices());
	glDisableVertexAttribArray(shader->GetAttrColors());
	glDisableVertexAttribArray(shader->GetAttrTexCoords());
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


	m_vertexData = //points of triangle
	{  //x,   y,     z       r,    g,    b,        (8 floats)
		50.0f, 50.0f, 0.0f,		1.0f, 0.0f, 0.0f,	 1.0f, 1.0f,
		50.0f, -50.0f, 0.0f,	0.0f, 1.0f, 0.0f,	 1.0f, 0.0f,
		-50.0f, -50.0f, 0.0f,	0.0f, 0.0f, 1.0f,	 0.0f, 0.0f,
		-50.0f, 50.0f, 0.0f,	1.0f, 1.0f, 1.0f,	 0.0f, 1.0f
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
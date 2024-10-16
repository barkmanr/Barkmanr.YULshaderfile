#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
//#define GLM_ENABLE_EXPERIMENTAL

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
	stroll = glm::vec2(0, 0);
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
	texture2->LoadTexture("../Assets/Textures/Checkerboard.jpg");

	isClean = false;

	m_vertexData = //points of triangle
	{  //x,   y,     z       r,    g,    b,        texcoords
		50.0f, 50.0f, 0.0f,		1.0f, 1.0f, 1.0f,	 1.0f, 1.0f,
		50.0f, -50.0f, 0.0f,	1.0f, 1.0f, 1.0f,	 1.0f, 0.0f,
		-50.0f, -50.0f, 0.0f,	1.0f, 1.0f, 1.0f,	 0.0f, 0.0f,
		-50.0f, 50.0f, 0.0f,	1.0f, 1.0f, 1.0f,	 0.0f, 1.0f
	};
	

	indexData = {
		2,0,3,	2,1,0,
		2,3,0,	2,0,1
	};

	setBuffers();
}

///


void Mesh::Render(glm::mat4 mvp)
{
	glUseProgram(shader->GetProgramID());
	mvp *= world; //mvp = world, view, progecion

	glUniformMatrix4fv(shader->GetAttrWVP(), 1, FALSE, &mvp[0][0]);
	glEnableVertexAttribArray(shader->GetAttrVertices());

	glVertexAttribPointer //position? don't know what these do
	(
		shader->GetAttrVertices(),
		3, //size. amount of items in vertex shit
		GL_FLOAT,
		GL_FALSE, //is normazlized?
		8 * sizeof(float), //stride: x,y,z,r,g,b,a skip for next vertex
		(void*)0
	);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

	glEnableVertexAttribArray(shader->GetAttrColors());

	glVertexAttribPointer //color
	(
		shader->GetAttrColors(),
		3, //size not 4, no more alpha
		GL_FLOAT,
		GL_FALSE, //is normazlized?
		8 * sizeof(float), //stride: x,y,z,r,g,b,a skip for next vertex
		(void*)(3 * sizeof(float))
	);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

	glEnableVertexAttribArray(shader->GetAttrTexCoords());
	glVertexAttribPointer(
		shader->GetAttrTexCoords(),
		2, GL_FLOAT, GL_FALSE,
		8 * sizeof(float),
		(void*)(6 * sizeof(float)) //offset = start at item 6
	);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->GetTexture());
	glUniform1i(shader->GetSampler1(), 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2->GetTexture());
	glUniform1i(shader->GetSampler2(), 1);

	glVertexAttrib2fv(shader->GetAttrItemAdd(), glm::value_ptr(stroll));

	

	glDrawElements(GL_TRIANGLES, indexData.size(), GL_UNSIGNED_BYTE, (void*)0); //Shape
	glDisableVertexAttribArray(shader->GetAttrVertices());
	glDisableVertexAttribArray(shader->GetAttrColors());
	glDisableVertexAttribArray(shader->GetAttrTexCoords());
}


void Mesh::UpdateVertex(float x, float y) //my stuff, need to fix for new triangle
{
	if (x > 0.0f) //D
	{
		stroll.x += 0.001f;
	}
	else if (x < 0.0f) //A
	{
		stroll.x -= 0.001f;
	}
	else if (y > 0.0f) //W
	{
		stroll.y += 0.001f;
	}
	else if (y < 0.0f) //S
	{
	    stroll.y -= 0.001f;
	}

	if (stroll.x > 1.0f)
	{
		stroll.x = 0.0f;
	}
	else if (stroll.x < 0.0f)
	{
		stroll.x = 1.0f;
	}

	if (stroll.y > 1.0f)
	{
		stroll.y = 0.0f;
	}
	else if (stroll.y < 0.0f)
	{
		stroll.y = 1.0f;
	}
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

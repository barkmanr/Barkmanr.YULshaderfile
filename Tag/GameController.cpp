#include "GameController.h"
#include "WindowController.h"
#include "Mesh.h"
#include "Shader.h"
#include "ToolWindow.h"
#include "Camera.h"

GameController::GameController()
{
	mesh = nullptr;
	shader = nullptr;
	curentCamera = 0;
	held = false;
	held2 = false;
	Initialize();
}


GameController::~GameController()
{
	if (mesh != nullptr)
	{
		delete mesh;
	}
	if (shader != nullptr)
	{
		delete shader;
	}
	for (Camera* cam : cameras)
	{
		delete cam;
	}
	cameras.clear();

}

void GameController::Initialize()
{
	GLFWwindow* window = WindowController::Instance().GetWindow();
	M_ASSERT(glewInit() == GLEW_OK, "Failed to initialize GLEW.");
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f); //RGBA
	glEnable(GL_CULL_FACE);

	cameras.push_back(new Camera(WindowController::Instance().GetResolution(), glm::vec3(100, 100, 100)));
	curentCamera = 0;
}

void GameController::HandleKeys()
{
	if (glfwGetKey(WindowController::Instance().GetWindow(), GLFW_KEY_W) == GLFW_PRESS)
	{
		mesh->UpdateVertex(0.0f, 1.0f);
	}
	if (glfwGetKey(WindowController::Instance().GetWindow(), GLFW_KEY_A) == GLFW_PRESS)
	{
		mesh->UpdateVertex(-1.0f, 0.0f);
	}
	if (glfwGetKey(WindowController::Instance().GetWindow(), GLFW_KEY_S) == GLFW_PRESS)
	{
		mesh->UpdateVertex(0.0f, -1.0f);
	}
	if (glfwGetKey(WindowController::Instance().GetWindow(), GLFW_KEY_D) == GLFW_PRESS)
	{
		mesh->UpdateVertex(1.0f, 0.0f);
	}

	if (glfwGetKey(WindowController::Instance().GetWindow(), GLFW_KEY_C) == GLFW_PRESS)
	{
		held = true;
	}
	else if (held == true)
	{
		held = false;
		curentCamera++;
		if (curentCamera >= (int)cameras.size()) { curentCamera = 0; }
	}

	if (glfwGetKey(WindowController::Instance().GetWindow(), GLFW_KEY_V) == GLFW_PRESS)
	{
		held2 = true;
	}
	else if (held2 == true)
	{
		held2 = false;
		cameras[curentCamera]->ChangeFov();
	}
}

void GameController::RunGame()
{
	Tag::ToolWindow^ sidewind = gcnew Tag::ToolWindow(); //Side window
	sidewind->Show();

	shader = new Shader();
	shader->LoadShaders("SVS.vertexShader", "SFS.fragmentshader");
	mesh = new Mesh();
	mesh->Create(shader);

	GLFWwindow* window = WindowController::Instance().GetWindow();
	do
	{
		System::Windows::Forms::Application::DoEvents(); //CLI

		//tool window stuff
		GLint location = 0;
		location = glGetUniformLocation(shader->GetProgramID(), "RenderValueY");
		glUniform1i(location, Tag::ToolWindow::RenderValueY);
		location = glGetUniformLocation(shader->GetProgramID(), "RenderValueU");
		glUniform1i(location, Tag::ToolWindow::RenderValueU);
		location = glGetUniformLocation(shader->GetProgramID(), "RenderValueV");
		glUniform1i(location, Tag::ToolWindow::RenderValueV);

		glClear(GL_COLOR_BUFFER_BIT);
		mesh->Render(cameras[curentCamera]->GetProjection() * cameras[curentCamera]->GetView()); //p * v * w
		glfwSwapBuffers(window); //swap the front and back
		glfwPollEvents();

		HandleKeys(); //my own input

	} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);

	mesh->Cleanup();
	shader->Cleanup();
}

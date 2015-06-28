#include "Game.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "FlyCamera.h"
#include "glm/gtc/type_ptr.hpp"
#include "Input.h"

using glm::vec3;
using glm::vec4;
using glm::mat4;

void Game::Load()
{
	// Initialize camera
	camera = new FlyCamera();
	camera->SetPerspective(glm::pi<float>() * 0.25f, 16 / 9.f, 0.1f, 10000.0f);
	camera->transform->Translate(0, 1, -5);

	model = new Model("Resources/Models/nanosuit/nanosuit2.obj");

	modelMat = new ShaderProgram();
	modelMat->CompileShader("Resources/Shaders/BRDFVert.glsl", OpenGLShader::VERTEX);
	modelMat->CompileShader("Resources/Shaders/BRDFFrag.glsl", OpenGLShader::FRAGMENT);
	modelMat->Link();
	modelMat->Validate();

	// Setting up tweak bar
	bar = TwNewBar("Debug Console");
	TwAddVarRO(bar, "FPS", TW_TYPE_FLOAT, &fps, "group=Performance");
}

void Game::Update(float deltaTime)
{
	camera->Update(deltaTime);
	fps = 1.0f / deltaTime;

	if (Input::GetKeyPressed(GLFW_KEY_SPACE))
		modelMat->Reload();
}

void Game::Draw(float deltaTime)
{
	modelMat->Use();
	modelMat->SetUniform("viewProjection", camera->GetProjectionView());
	modelMat->SetUniform("cameraPos", camera->transform->GetPosition());
	model->Draw(*modelMat);
}

void Game::Unload()
{
	delete camera;
	delete model;
	delete modelMat;
}
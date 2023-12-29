#include "Game.h"
#include "Cameras/CameraBase.h"
#include "Cameras/FPSCamera.h"
#include "InputManager.h"
#include "World.h"
#include "glm/gtc/matrix_transform.hpp"
#include "mGL/MeshFactory.h"

namespace mFPS
{
	Game::Game() : mDeltaTime(0.0f), mLastFrame(0.0f)
	{
		mWorld = std::shared_ptr<World>(new World());
		mRenderer = std::shared_ptr<mGL::Renderer>(new mGL::Renderer());
		mCamera = std::shared_ptr<CameraBase>(new FPSCamera());
		mInputManager = std::shared_ptr<InputManager>(new InputManager());
	}

	Game::~Game()
	{
		mRenderer.get()->Terminate();
		mRenderer.reset();
		mCamera.reset();
	}

	int Game::Initialize(const int& width, const int& height)
	{
		mWindow = mRenderer.get()->InitializeRenderer(width, height);
		if (mWindow == nullptr) {
			return 1;
		}

		mCamera.get()->SetProjection(glm::perspective(glm::radians(75.0f), (float)width / (float)height, 0.1f, 100.0f));
		mCamera->SetPosition(glm::vec3(0.0f, 0.0f, -10.0f));

		mInputManager->SetCursorMode(mWindow);

		// Add objects (TEMP)
		//mGL::RenderableObject* ro1 = mGL::MeshFactory::LoadObj("test_alex.obj");
		//auto matrix1 = ro1->GetMatrix();
		//*matrix1 = glm::translate(*matrix1, glm::vec3(0.0f, -10.0f, 0.0f));
		//*matrix1 = glm::rotate(*matrix, glm::radians(-45.0f), glm::vec3(1.0, 0.0, 0.0));
		//mWorld->AddRenderableObject(ro1);
		//mWorld->AddRenderableObject(mGL::MeshFactory::LoadObj("tree_thin_dark.obj"));
		//auto ro1 = mGL::MeshFactory::LoadObj("gas-station.obj");
		//auto ro2 = mGL::MeshFactory::LoadObj("house-country.obj");
		//auto ro3 = mGL::MeshFactory::LoadObj("house-hill-normal.obj");
		//auto ro4 = mGL::MeshFactory::LoadObj("house-hill-small.obj");
		//auto ro5 = mGL::MeshFactory::LoadObj("house-luxurious.obj");
		//*ro1->GetMatrix() = glm::translate(*ro1->GetMatrix(), glm::vec3(0.0f, 0.0f, 0.0f));
		//*ro2->GetMatrix() = glm::translate(*ro2->GetMatrix(), glm::vec3(10.0f, 0.0f, 0.0f));
		//*ro3->GetMatrix() = glm::translate(*ro3->GetMatrix(), glm::vec3(0.0f, 0.0f, 10.0f));
		//*ro4->GetMatrix() = glm::translate(*ro4->GetMatrix(), glm::vec3(10.0f, 0.0f, 10.0f));
		//*ro5->GetMatrix() = glm::translate(*ro5->GetMatrix(), glm::vec3(0.0f, 0.0f, 30.0f));
		//mWorld->AddRenderableObject(ro1);
		//mWorld->AddRenderableObject(ro2);
		//mWorld->AddRenderableObject(ro3);
		//mWorld->AddRenderableObject(ro4);
		//mWorld->AddRenderableObject(ro5);
		mWorld->FromXML("TestWorld.xml");
		return 0;
	}

	bool Game::Update()
	{
		float currentFrame = glfwGetTime();
		mDeltaTime = currentFrame - mLastFrame;
		mLastFrame = currentFrame;

		mInputManager->ProcessInput(mWindow);

		mCamera.get()->Update(mDeltaTime, mInputManager.get());

		mRenderer.get()->Render(mWorld->GetRenderableObjects(), mCamera->GetProjection(), mCamera->GetView());

		return !glfwWindowShouldClose(mWindow) && !mInputManager->IsKeyDown(GLFW_KEY_ESCAPE);
	}
}
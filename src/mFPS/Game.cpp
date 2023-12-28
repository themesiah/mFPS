#include "Game.h"
#include "Cameras/FPSCamera.h"
#include "InputManager.h"

namespace mFPS
{
	Game::Game() : mDeltaTime(0.0f), mLastFrame(0.0f)
	{
		mRenderer = std::shared_ptr<mGL::Renderer>(new mGL::Renderer());
		mCamera = std::shared_ptr<FPSCamera>(new FPSCamera());
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
		return 0;
	}

	bool Game::Update()
	{
		float currentFrame = glfwGetTime();
		mDeltaTime = currentFrame - mLastFrame;
		mLastFrame = currentFrame;

		mInputManager->ProcessInput(mWindow);

		mCamera.get()->Update(mDeltaTime, mInputManager.get());

		mRenderer.get()->Render(mCamera->GetProjection(), mCamera->GetView());

		return !glfwWindowShouldClose(mWindow) && !mInputManager->IsKeyDown(GLFW_KEY_ESCAPE);
	}
}
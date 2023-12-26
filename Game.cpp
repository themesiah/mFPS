#include "Game.h"
#include "mGL/FPSCamera.h"
#include "InputManager.h"

namespace mFPS
{
	Game::Game() : mDeltaTime(0.0f), mLastFrame(0.0f)
	{
		mRenderer = std::shared_ptr<mGL::Renderer>(new mGL::Renderer());
		mCamera = std::shared_ptr<mGL::FPSCamera>(new mGL::FPSCamera());
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

		// CAMERA INPUT START -- TODO: Move to camera?
		glm::vec2 lookDelta = mInputManager->GetMouseDelta();
		mCamera->Rotate(lookDelta.x * 3.0f * mDeltaTime, lookDelta.y * 3.0f * mDeltaTime);
		glm::vec3 movementDelta = glm::vec3(0.0f,0.0f,0.0f);
		if (mInputManager->IsKeyDown(GLFW_KEY_A))
		{
			movementDelta.x = -100.0f * mDeltaTime;
		}
		if (mInputManager->IsKeyDown(GLFW_KEY_D))
		{
			movementDelta.x = 100.0f * mDeltaTime;
		}
		if (mInputManager->IsKeyDown(GLFW_KEY_W))
		{
			movementDelta.z = 100.0f * mDeltaTime;
		}
		if (mInputManager->IsKeyDown(GLFW_KEY_S))
		{
			movementDelta.z = -100.0f * mDeltaTime;
		}
		mCamera->Translate(movementDelta);
		// CAMERA INPUT END

		mCamera.get()->Update(mDeltaTime);

		mRenderer.get()->Render(mCamera.get());

		return !glfwWindowShouldClose(mWindow) && !mInputManager->IsKeyDown(GLFW_KEY_ESCAPE);
	}
}
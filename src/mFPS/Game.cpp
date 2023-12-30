#include "Game.h"
#include "Cameras/CameraBase.h"
#include "Cameras/FPSCamera.h"
#include "Input/InputManager.h"
#include "Input/ActionManager.h"
#include "World.h"
#include "glm/gtc/matrix_transform.hpp"
#include "mGL/MeshFactory.h"

#ifdef _DEBUG
#include "mBase/ImGui/imgui.h"
#include "mBase/ImGui/imgui_impl_glfw.h"
#include "mBase/ImGui/imgui_impl_opengl3.h"
#endif

namespace mFPS
{
	Game::Game() : mDeltaTime(0.0f), mLastFrame(0.0f)
	{
		mWorld = std::shared_ptr<World>(new World());
		mRenderer = std::shared_ptr<mGL::Renderer>(new mGL::Renderer());
		mCamera = std::shared_ptr<CameraBase>(new FPSCamera());
		mInputManager = std::shared_ptr<InputManager>(new InputManager());
		mActionManager = std::shared_ptr<ActionManager>(new ActionManager(mInputManager));
	}

	Game::~Game()
	{
		mRenderer->Terminate();
		mRenderer.reset();
		mCamera.reset();
	}

	int Game::Initialize(const int& width, const int& height)
	{
		mWindow = mRenderer->InitializeRenderer(width, height);
		if (mWindow == nullptr) {
			return 1;
		}

		mCamera->SetProjection(glm::perspective(glm::radians(75.0f), (float)width / (float)height, 0.1f, 100.0f));
		mCamera->SetPosition(glm::vec3(0.0f, 0.0f, -10.0f));

		mInputManager->SetCursorMode(mWindow);
		mActionManager->LoadActions("Data/InputActions.xml");

		mWorld->FromXML("TestWorld.xml");

#ifdef _DEBUG
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
		ImGui_ImplGlfw_InitForOpenGL(mWindow, true);
		ImGui_ImplOpenGL3_Init();
#endif
		return 0;
	}

	bool Game::Update()
	{
		float currentFrame = glfwGetTime();
		mDeltaTime = currentFrame - mLastFrame;
		mLastFrame = currentFrame;
		glfwPollEvents();
		mInputManager->ProcessInput(mWindow);
		if (mInputManager->IsKeyDown(GLFW_KEY_ESCAPE))
		{
			mInputManager->UnsetCursorMode(mWindow);
		}
		if (mInputManager->IsKeyDown(GLFW_KEY_TAB))
		{
			mInputManager->SetCursorMode(mWindow);
		}

		mCamera->Update(mDeltaTime, mActionManager.get());

#ifdef _DEBUG
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		//ImGui::ShowDemoWindow();
		if (ImGui::Begin("Main Window")) {
			mCamera->ShowImGui();
		}
		ImGui::End();
#endif

		mRenderer->Render(mWorld->GetRenderableObjects(), mCamera->GetProjection(), mCamera->GetView());

#ifdef _DEBUG
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
#endif

		mRenderer->EndFrame();

		return !glfwWindowShouldClose(mWindow);
	}
}
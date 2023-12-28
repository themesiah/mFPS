#ifndef MFPS_GAME
#define MFPS_GAME

#include <memory>
#include <GL/glew.h> // include GLEW and new version of GL on Windows

#include "mGL/Renderer.h"
#include "Cameras/FPSCamera.h"

namespace mFPS
{
	class InputManager;
	class Game
	{
	public:
		Game();
		~Game();
		int Initialize(const int &width, const int &height);
		bool Update();
	private:
		std::shared_ptr<FPSCamera> mCamera;
		std::shared_ptr<mGL::Renderer> mRenderer;
		std::shared_ptr<InputManager> mInputManager;
		GLFWwindow* mWindow;

		float mDeltaTime;
		float mLastFrame;
	};
}

#endif

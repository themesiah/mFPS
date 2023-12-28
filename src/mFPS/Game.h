#ifndef MFPS_GAME
#define MFPS_GAME

#include <memory>
#include <GL/glew.h>

#include "mGL/Renderer.h"

namespace mFPS
{
	class InputManager;
	class World;
	class FPSCamera;
	class Game
	{
	public:
		Game();
		~Game();
		int Initialize(const int &width, const int &height);
		bool Update();
	private:
		std::shared_ptr<World> mWorld;
		std::shared_ptr<FPSCamera> mCamera;
		std::shared_ptr<mGL::Renderer> mRenderer;
		std::shared_ptr<InputManager> mInputManager;
		GLFWwindow* mWindow;

		float mDeltaTime;
		float mLastFrame;
	};
}

#endif

#ifndef MFPS_GAME
#define MFPS_GAME

#include <memory>
#include <GL/glew.h>

#include "mGL/Renderer.h"

namespace mFPS
{
	class InputManager;
	class ActionManager;
	class World;
	class CameraBase;
	class Game
	{
	public:
		Game();
		~Game();
		int Initialize(const int &width, const int &height);
		bool Update();
	private:
		std::shared_ptr<World> mWorld;
		std::shared_ptr<CameraBase> mCamera;
		std::shared_ptr<mGL::Renderer> mRenderer;
		std::shared_ptr<InputManager> mInputManager;
		std::shared_ptr<ActionManager> mActionManager;
		GLFWwindow* mWindow;

		float mDeltaTime;
		float mLastFrame;
	};
}

#endif

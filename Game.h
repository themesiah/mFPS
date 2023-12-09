#ifndef MFPS_GAME
#define MFPS_GAME

#include <memory>
#include <GL/glew.h> // include GLEW and new version of GL on Windows

#include "mGL/Renderer.h"
#include "mGL/CameraBase.h"

namespace mFPS
{
	class Game
	{
	public:
		Game();
		~Game();
		int Initialize(const int &width, const int &height);
		bool Update();
	private:
		std::shared_ptr<mGL::CameraBase> mCamera;
		std::shared_ptr<mGL::Renderer> mRenderer;
		GLFWwindow* mWindow;

		float mDeltaTime;
		float mLastFrame;
	};
}

#endif

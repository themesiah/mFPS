#ifndef MFPS_INPUT_MANAGER
#define MFPS_INPUT_MANAGER

#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "InputDefinitions.h"

namespace mFPS
{
	class InputManager
	{
	public:
		InputManager();
		void ProcessInput(GLFWwindow *window);
		bool IsKeyDown(const int &key) const;
		bool IsKeyPressed(const int &key) const;
		bool IsKeyReleased(const int &key) const;
		bool IsMouseButtonDown(const int &key) const;
		bool IsMouseButtonPressed(const int &key) const;
		bool IsMouseButtonReleased(const int &key) const;
		void SetCursorMode(GLFWwindow *window);
		void UnsetCursorMode(GLFWwindow *window);
		const glm::vec2 GetMouseDelta() const;
		const glm::vec2 GetMousePosition() const;

	private:
		Input mLastInput;
		Input mCurrentInput;
	};
}

#endif

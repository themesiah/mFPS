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
		void ProcessInput(GLFWwindow* window);
		const bool IsKeyDown(const int& key) const;
		const bool IsKeyPressed(const int& key) const;
		const bool IsKeyReleased(const int& key) const;
		const bool IsMouseButtonDown(const int& key) const;
		const bool IsMouseButtonPressed(const int& key) const;
		const bool IsMouseButtonReleased(const int& key) const;
		const void SetCursorMode(GLFWwindow* window);
		const void UnsetCursorMode(GLFWwindow* window);
		const glm::vec2 GetMouseDelta() const;
		const glm::vec2 GetMousePosition() const;
	private:
		Input mLastInput;
		Input mCurrentInput;
	};
}

#endif

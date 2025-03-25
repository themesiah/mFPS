#include "InputManager.h"

#include <iostream>

namespace mFPS
{
	InputManager::InputManager() : mLastInput({}), mCurrentInput({}) {}

	void InputManager::ProcessInput(GLFWwindow *window)
	{
		// Keyboard input
		mLastInput = mCurrentInput;
		mCurrentInput = {};
		for (int i = 0; i < GLFW_KEY_LAST; ++i)
		{
			mCurrentInput.Keyboard[i] = glfwGetKey(window, i);
		}

		for (int i = 0; i < GLFW_MOUSE_BUTTON_LAST; ++i)
		{
			mCurrentInput.MouseButtons[i] = glfwGetMouseButton(window, i);
		}

		if (glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED) // Cursor disabled means we activated the mouse motion
		{
			// Mouse input
			double xpos, ypos;
			glfwGetCursorPos(window, &xpos, &ypos);
			mCurrentInput.MousePosition.x = static_cast<float>(xpos);
			mCurrentInput.MousePosition.y = static_cast<float>(ypos);
		}
	}

	void InputManager::SetCursorMode(GLFWwindow *window)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		mLastInput.MousePosition = mCurrentInput.MousePosition;
	}

	void InputManager::UnsetCursorMode(GLFWwindow *window)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		mLastInput.MousePosition = mCurrentInput.MousePosition;
	}

	bool InputManager::IsKeyDown(const int &key) const
	{
		if (key < 0 || key > GLFW_KEY_LAST)
			return false;
		return mCurrentInput.Keyboard[key];
	}

	bool InputManager::IsKeyPressed(const int &key) const
	{
		if (key < 0 || key > GLFW_KEY_LAST)
			return false;
		return mCurrentInput.Keyboard[key] && !mLastInput.Keyboard[key];
	}

	bool InputManager::IsKeyReleased(const int &key) const
	{
		if (key < 0 || key > GLFW_KEY_LAST)
			return false;
		return !mCurrentInput.Keyboard[key] && mLastInput.Keyboard[key];
	}

	bool InputManager::IsMouseButtonDown(const int &key) const
	{
		if (key < 0 || key > GLFW_MOUSE_BUTTON_LAST)
			return false;
		return mCurrentInput.MouseButtons[key];
	}

	bool InputManager::IsMouseButtonPressed(const int &key) const
	{
		if (key < 0 || key > GLFW_MOUSE_BUTTON_LAST)
			return false;
		return mCurrentInput.MouseButtons[key] && !mLastInput.MouseButtons[key];
	}

	bool InputManager::IsMouseButtonReleased(const int &key) const
	{
		if (key < 0 || key > GLFW_MOUSE_BUTTON_LAST)
			return false;
		return !mCurrentInput.MouseButtons[key] && mLastInput.MouseButtons[key];
	}

	const glm::vec2 InputManager::GetMouseDelta() const
	{
		return {mCurrentInput.MousePosition.x - mLastInput.MousePosition.x, mLastInput.MousePosition.y - mCurrentInput.MousePosition.y};
	}

	const glm::vec2 InputManager::GetMousePosition() const
	{
		return mCurrentInput.MousePosition;
	}
}
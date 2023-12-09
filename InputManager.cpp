#include "InputManager.h"

#include <iostream>

namespace mFPS
{
	InputManager::InputManager() : mCurrentInput({}), mLastInput({}){}

	void InputManager::ProcessInput(GLFWwindow* window)
	{
		mLastInput = mCurrentInput;
		mCurrentInput = {};
		for (int i = 0; i < GLFW_KEY_LAST; ++i)
		{
			mCurrentInput.Keyboard[i] = glfwGetKey(window, i);
			if (mCurrentInput.Keyboard[i] == true)
			{
				std::cout << "Key with index " << i << " is pressed" << std::endl;
			}
		}
	}

	const bool InputManager::IsKeyDown(const int& key) const
	{
		if (key < 0 || key > GLFW_KEY_LAST) return false;
		return mCurrentInput.Keyboard[key];
	}

	const bool InputManager::IsKeyPressed(const int& key) const
	{
		if (key < 0 || key > GLFW_KEY_LAST) return false;
		return mCurrentInput.Keyboard[key] && !mLastInput.Keyboard[key];
	}

	const bool InputManager::IsKeyReleased(const int& key) const
	{
		if (key < 0 || key > GLFW_KEY_LAST) return false;
		return !mCurrentInput.Keyboard[key] && mLastInput.Keyboard[key];
	}
}
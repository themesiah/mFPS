#ifndef MFPS_INPUT_DEFINITIONS
#define MFPS_INPUT_DEFINITIONS

#include <GLFW/glfw3.h>
#include "glm/glm.hpp"

namespace mFPS {
	struct Input
	{
		bool Keyboard[GLFW_KEY_LAST];
		glm::vec2 MousePosition;
	};

	enum TriggerType
	{
		Keyboard = 0,
		Mouse = 1,
		MouseLook = 2
	};

	enum TriggerActionType
	{
		Down = 0,
		Pressed = 1,
		Released = 2
	};

	enum MouseAxis
	{
		X = 0,
		Y = 1,
		DX = 2,
		DY = 3
	};

	enum MouseButton
	{
		Left = 0,
		Right = 1,
		Middle = 2
	};
}

#endif

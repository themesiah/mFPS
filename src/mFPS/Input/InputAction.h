#ifndef MFPS_INPUTACTION
#define MFPS_INPUTACTION

#include <vector>
#include <string>

#include "InputDefinitions.h"
#include "mBase/XML/tinyxml2.h"

namespace mFPS
{
	class InputManager;
	struct Trigger
	{
		TriggerType triggerType;
		union {
			struct {
				TriggerActionType triggerActionType;
				int keyCode;
				float value;
			} keyboard;
			struct {
				TriggerActionType triggerActionType;
				MouseButton mouseButton;
				float value;
			} mouseButton;
			struct {
				MouseAxis mouseAxis;
				float sensitivity;
			} mouseLook;
		};
	};

	class InputAction
	{
	public:
		InputAction(const std::string& name);
		~InputAction();
		tinyxml2::XMLError AddTrigger(tinyxml2::XMLElement* element);
		float GetValue(InputManager* inputManager);
		int GetKeyCodeFromString(const char* str);
	private:
		std::string mName;
		std::vector<Trigger> mTriggers;
	};
}

#endif
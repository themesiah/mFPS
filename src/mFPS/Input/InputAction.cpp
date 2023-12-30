#include "InputAction.h"
#include "InputManager.h"

namespace mFPS
{
	InputAction::InputAction(const std::string& name) : mName(name){}

	InputAction::~InputAction()
	{

	}

	tinyxml2::XMLError InputAction::AddTrigger(tinyxml2::XMLElement* element)
	{
		const char* type;
		tinyxml2::XMLError result = element->QueryStringAttribute("type", &type);
		if (result != tinyxml2::XML_SUCCESS) return result;

		Trigger trigger;

		if (strcmp(type ,"Keyboard") == 0)
		{
			trigger.triggerType = TriggerType::Keyboard;
			const char* actionType;
			result = element->QueryStringAttribute("action_type", &actionType);
			if (result != tinyxml2::XML_SUCCESS) return result;
			if (strcmp(actionType, "Down") == 0)
			{
				trigger.keyboard.triggerActionType = TriggerActionType::Down;
			}
			else if (strcmp(actionType, "Pressed") == 0)
			{
				trigger.keyboard.triggerActionType = TriggerActionType::Pressed;
			}
			else if (strcmp(actionType, "Released") == 0)
			{
				trigger.keyboard.triggerActionType = TriggerActionType::Released;
			}
			else
			{
				return tinyxml2::XML_ERROR_PARSING_ATTRIBUTE;
			}
			float value;
			result = element->QueryFloatAttribute("value", &value);
			if (result != tinyxml2::XML_SUCCESS) return result;
			trigger.keyboard.value = value;

			const char* keyCode;
			result = element->QueryStringAttribute("key_code", &keyCode);
			if (result != tinyxml2::XML_SUCCESS) return result;
			trigger.keyboard.keyCode = GetKeyCodeFromString(keyCode);
		}
		else if (strcmp(type, "MouseButton") == 0)
		{
			trigger.triggerType = TriggerType::Mouse;
			const char* actionType;
			result = element->QueryStringAttribute("action_type", &actionType);
			if (result != tinyxml2::XML_SUCCESS) return result;
			if (strcmp(actionType, "Down") == 0)
			{
				trigger.mouseButton.triggerActionType = TriggerActionType::Down;
			}
			else if (strcmp(actionType, "Pressed") == 0)
			{
				trigger.mouseButton.triggerActionType = TriggerActionType::Pressed;
			}
			else if (strcmp(actionType, "Released") == 0)
			{
				trigger.mouseButton.triggerActionType = TriggerActionType::Released;
			}
			else
			{
				return tinyxml2::XML_ERROR_PARSING_ATTRIBUTE;
			}

			const char* mouseButton;
			result = element->QueryStringAttribute("mouse_button", &mouseButton);
			if (result != tinyxml2::XML_SUCCESS) return result;
			if (strcmp(mouseButton, "Left") == 0)
			{
				trigger.mouseButton.mouseButton = MouseButton::Left;
			}
			else if (strcmp(mouseButton, "Right") == 0)
			{
				trigger.mouseButton.mouseButton = MouseButton::Right;
			}
			else if (strcmp(mouseButton, "Middle") == 0)
			{
				trigger.mouseButton.mouseButton = MouseButton::Middle;
			}
			else {
				return tinyxml2::XML_ERROR_PARSING_ATTRIBUTE;
			}

			float value;
			result = element->QueryFloatAttribute("value", &value);
			if (result != tinyxml2::XML_SUCCESS) return result;
			trigger.mouseButton.value = value;
		}
		else if (strcmp(type, "MouseLook") == 0)
		{
			trigger.triggerType = TriggerType::MouseLook;
			const char* axis;
			result = element->QueryStringAttribute("mouse_axis", &axis);
			if (result != tinyxml2::XML_SUCCESS) return result;
			if (strcmp(axis, "X") == 0)
			{
				trigger.mouseLook.mouseAxis = MouseAxis::X;
			}
			else if (strcmp(axis, "Y") == 0)
			{
				trigger.mouseLook.mouseAxis = MouseAxis::Y;
			}
			else if (strcmp(axis, "DX") == 0)
			{
				trigger.mouseLook.mouseAxis = MouseAxis::DX;
			}
			else if (strcmp(axis, "DY") == 0)
			{
				trigger.mouseLook.mouseAxis = MouseAxis::DY;
			}
			trigger.mouseLook.sensitivity = 1.0f;
			float sensitivity;
			result = element->QueryFloatAttribute("sensitivity", &sensitivity);
			if (result == tinyxml2::XML_SUCCESS) // OPTIONAL
			{
				trigger.mouseLook.sensitivity = sensitivity;
			}
		}
		else {
			return tinyxml2::XML_ERROR_PARSING_ATTRIBUTE;
		}

		mTriggers.push_back(trigger);
		return tinyxml2::XML_SUCCESS;
	}

	float InputAction::GetValue(InputManager* inputManager)
	{
		float value = 0.0f;
		for(int i = 0; i < mTriggers.size(); ++i)
		{
			switch (mTriggers[i].triggerType)
			{
			case TriggerType::Keyboard:
				switch (mTriggers[i].keyboard.triggerActionType)
				{
				case TriggerActionType::Down:
					if (inputManager->IsKeyDown(mTriggers[i].keyboard.keyCode)) value += mTriggers[i].keyboard.value;
					break;
				case TriggerActionType::Pressed:
					if (inputManager->IsKeyPressed(mTriggers[i].keyboard.keyCode)) value += mTriggers[i].keyboard.value;
					break;
				case TriggerActionType::Released:
					if (inputManager->IsKeyReleased(mTriggers[i].keyboard.keyCode)) value += mTriggers[i].keyboard.value;
					break;
				}
				break;
			case TriggerType::Mouse:
				switch (mTriggers[i].mouseButton.triggerActionType)
				{
				case TriggerActionType::Down:
					if (inputManager->IsMouseButtonDown(mTriggers[i].mouseButton.mouseButton)) value += mTriggers[i].mouseButton.value;
					break;
				case TriggerActionType::Pressed:
					if (inputManager->IsMouseButtonPressed(mTriggers[i].mouseButton.mouseButton)) value += mTriggers[i].mouseButton.value;
					break;
				case TriggerActionType::Released:
					if (inputManager->IsMouseButtonReleased(mTriggers[i].mouseButton.mouseButton)) value += mTriggers[i].mouseButton.value;
					break;
				}
				break;
			case TriggerType::MouseLook:
				switch (mTriggers[i].mouseLook.mouseAxis)
				{
				case MouseAxis::X:
					value += inputManager->GetMousePosition().x * mTriggers[i].mouseLook.sensitivity;
					break;
				case MouseAxis::Y:
					value += inputManager->GetMousePosition().y * mTriggers[i].mouseLook.sensitivity;
					break;
				case MouseAxis::DX:
					value += inputManager->GetMouseDelta().x * mTriggers[i].mouseLook.sensitivity;
					break;
				case MouseAxis::DY:
					value += inputManager->GetMouseDelta().y * mTriggers[i].mouseLook.sensitivity;
					break;
				}
				break;
			}
		}
		return value;
	}

	int InputAction::GetKeyCodeFromString(const char* str)
	{
		if (str == NULL) return -1;
		if (strlen(str) == 1 && (str[0] >= 'A' && str[0] <= 'Z') || (str[0] >= '0' && str[0] <= '9'))
		{
			return str[0];
		}
		else if (strlen(str) == 1 && (str[0] >= 'a' && str[0] <= 'z'))
		{
			return str[0] - 32; // Lowercase is 32 more than their uppercase counterpart
		}
		else if (strcmp(str, "SPACE"))
		{
			return GLFW_KEY_SPACE;
		}
		else if (strcmp(str, "ESC"))
		{
			return GLFW_KEY_ESCAPE;
		}
		else if (strcmp(str, "LCTRL"))
		{
			return GLFW_KEY_LEFT_CONTROL;
		}
		else if (strcmp(str, "LSHIFT"))
		{
			return GLFW_KEY_LEFT_SHIFT;
		}
		else if (strcmp(str, "LALT"))
		{
			return GLFW_KEY_LEFT_ALT;
		}
		else if (strcmp(str, "TAB"))
		{
			return GLFW_KEY_TAB;
		}
		else if (strcmp(str, "ENTER"))
		{
			return GLFW_KEY_ENTER;
		}
	}
}
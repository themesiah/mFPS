#include "ActionManager.h"
#include "XML/tinyxml2.h"
#include "Logger.h"
#include "InputAction.h"
#include "CheckedDelete.h"

namespace mFPS
{
	ActionManager::ActionManager(std::shared_ptr<InputManager> inputManager) : mInputManager(inputManager), mInputActions() {}

	ActionManager::~ActionManager()
	{
		mInputActions.Destroy();
	}

	void ActionManager::LoadActions(const std::string &path)
	{
		tinyxml2::XMLDocument doc;
		Logger::Log("Action Manager", "Loading actions data on path " + path);
		doc.LoadFile(path.c_str());
		if (doc.ErrorID() == tinyxml2::XML_SUCCESS)
		{
			tinyxml2::XMLElement *action = doc.FirstChildElement("actions")->FirstChildElement("action");
			while (action != NULL)
			{
				const char *actionName;
				action->QueryStringAttribute("name", &actionName);
				tinyxml2::XMLElement *trigger = action->FirstChildElement("trigger");
				std::shared_ptr<InputAction> inputAction = std::make_shared<InputAction>(std::string(actionName));
				while (trigger != NULL)
				{
					inputAction->AddTrigger(trigger);
					trigger = trigger->NextSiblingElement();
				}
				mInputActions.Add(std::string(actionName), inputAction);
				action = action->NextSiblingElement();
			}
		}
		else
		{
			Logger::Error("Action Manager", "Error when loading actions data");
		}
	}

	bool ActionManager::IsPerforming(const std::string &actionName)
	{
		assert(mInputActions.Exist(actionName));
		return mInputActions(actionName)->GetValue(mInputManager.get()) != 0.0f;
	}

	float ActionManager::GetValue(const std::string &actionName)
	{
		assert(mInputActions.Exist(actionName));
		return mInputActions(actionName)->GetValue(mInputManager.get());
	}
}
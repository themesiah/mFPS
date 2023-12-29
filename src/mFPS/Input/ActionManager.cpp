#include "ActionManager.h"
#include "mBase/XML/tinyxml2.h"
#include "mBase/Logger.h"
#include "InputAction.h"
#include "mBase/CheckedDelete.h"

namespace mFPS {
	ActionManager::ActionManager(std::shared_ptr<InputManager> inputManager) : mInputManager(inputManager){}

	ActionManager::~ActionManager()
	{
		for (int i = 0; i < mInputActions.size(); ++i)
		{
			mBase::CheckedDelete(mInputActions[i]);
		}
	}

	void ActionManager::LoadActions(const std::string& path)
	{
		tinyxml2::XMLDocument doc;
		Logger::Log("Action Manager", "Loading actions data on path " + path);
		doc.LoadFile(path.c_str());
		if (doc.ErrorID() == tinyxml2::XML_SUCCESS)
		{
			tinyxml2::XMLElement* action = doc.FirstChildElement("actions")->FirstChildElement("action");
			while (action != NULL)
			{
				const char* actionName;
				action->QueryStringAttribute("name", &actionName);
				tinyxml2::XMLElement* trigger = action->FirstChildElement("trigger");
				InputAction* inputAction = new InputAction(std::string(actionName));
				while (trigger != NULL)
				{
					inputAction->AddTrigger(trigger);
					trigger = trigger->NextSiblingElement();
				}
				mInputActions.push_back(inputAction);
				action = action->NextSiblingElement();
			}
		}
		else {
			Logger::Log("Action Manager", "Error when loading actions data");
		}
	}
}
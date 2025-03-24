#ifndef MFPS_ACTIONMANAGER
#define MFPS_ACTIONMANAGER

#include <string>
#include <vector>
#include <memory>

#include "TemplatedMapVector.h"

namespace mFPS
{
	class InputManager;
	class InputAction;
	class ActionManager
	{
	public:
		ActionManager(std::shared_ptr<InputManager> inputManager);
		~ActionManager();
		void LoadActions(const std::string &path);
		const bool IsPerforming(const std::string &actionName);
		const float GetValue(const std::string &actionName);

	private:
		std::shared_ptr<InputManager> mInputManager;
		mBase::TemplatedMapVector<InputAction> mInputActions;
	};
}

#endif
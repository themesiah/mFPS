#ifndef MFPS_ACTIONMANAGER
#define MFPS_ACTIONMANAGER

#include <string>
#include <vector>
#include <memory>


namespace mFPS {
	class InputManager;
	class InputAction;
	class ActionManager
	{
	public:
		ActionManager(std::shared_ptr<InputManager> inputManager);
		~ActionManager();
		void LoadActions(const std::string& path);
	private:
		std::shared_ptr<InputManager> mInputManager;
		std::vector<InputAction*> mInputActions;
	};
}

#endif
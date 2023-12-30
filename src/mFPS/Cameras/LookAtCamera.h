#ifndef MGL_LOOKAT_CAMERA
#define MGL_LOOKAT_CAMERA

#include "CameraBase.h"

namespace mFPS
{
	class LookAtCamera : public CameraBase
	{
	public:
		LookAtCamera();
		void Update (const float& deltaTime, ActionManager* actionManager) override;
		void SetTarget(const glm::vec3& target);
		const glm::vec3 GetTarget() const;
		glm::vec3 GetForward() override;
#ifdef _DEBUG
		void ShowImGui() override;
#endif
	private:
		glm::vec3 mTarget;
	};
}


#endif

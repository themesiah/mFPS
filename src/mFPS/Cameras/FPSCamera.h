#ifndef MGL_FPS_CAMERA
#define MGL_FPS_CAMERA

#include "CameraBase.h"

namespace mFPS
{
	class FPSCamera : public CameraBase
	{
	public:
		FPSCamera();
		void Rotate(const float& yaw, const float& pitch);
		void Update(const float& deltaTime, ActionManager* actionManager) override;
		glm::vec3 GetForward() override;
#ifdef _DEBUG
		void ShowImGui() override;
#endif
	private:
		glm::vec3 mEuler; // x is pitch, y is yaw, z is roll
	};
}

#endif

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
		void Update(const float& deltaTime, InputManager* inputManager) override;
		glm::vec3 GetForward() override;
	private:
		float mYaw;
		float mPitch;
	};
}

#endif

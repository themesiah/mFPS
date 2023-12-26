#ifndef MGL_FPS_CAMERA
#define MGL_FPS_CAMERA

#include "CameraBase.h"

namespace mGL
{
	class FPSCamera : public CameraBase
	{
	public:
		FPSCamera();
		void Rotate(const float& yaw, const float& pitch);
		void Update(const float& deltaTime) override;
		glm::vec3 GetForward() override;
	private:
		float mYaw;
		float mPitch;
	};
}

#endif

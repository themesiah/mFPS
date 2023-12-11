#ifndef MGL_LOOKAT_CAMERA
#define MGL_LOOKAT_CAMERA

#include "CameraBase.h"

namespace mGL
{
	class LookAtCamera : public CameraBase
	{
	public:
		LookAtCamera();
		void Update (const float& deltaTime) override;
		void SetTarget(const glm::vec3& target);
		const glm::vec3 GetTarget() const;
	private:
		glm::vec3 mTarget;
	};
}


#endif
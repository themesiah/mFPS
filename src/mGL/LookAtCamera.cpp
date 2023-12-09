#include "LookAtCamera.h"
#include "glm/gtc/matrix_transform.hpp"

namespace mGL
{
	LookAtCamera::LookAtCamera() : mTarget(), CameraBase() {}

	void LookAtCamera::Update(const float& deltaTime)
	{
		mView = glm::lookAt(mPosition, mTarget, mUp);
	}

	void LookAtCamera::SetTarget(const glm::vec3& target)
	{
		mTarget = target;
	}

	const glm::vec3 LookAtCamera::GetTarget() const
	{
		return mTarget;
	}
}
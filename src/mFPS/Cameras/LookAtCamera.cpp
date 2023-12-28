#include "LookAtCamera.h"
#include "glm/gtc/matrix_transform.hpp"
#include "../InputManager.h"

namespace mFPS
{
	LookAtCamera::LookAtCamera() : mTarget(), CameraBase() {}

	void LookAtCamera::Update(const float& deltaTime, InputManager* inputManager)
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

	glm::vec3 LookAtCamera::GetForward()
	{
		return glm::normalize(mTarget - mPosition);
	}
}
#include "LookAtCamera.h"
#include "glm/gtc/matrix_transform.hpp"
#include "../Input/InputManager.h"

namespace mFPS
{
	LookAtCamera::LookAtCamera() : mTarget(), CameraBase() {}

	void LookAtCamera::Update(const float& deltaTime, ActionManager* actionManager)
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

#ifdef _DEBUG
	void LookAtCamera::ShowImGui()
	{}
#endif
}
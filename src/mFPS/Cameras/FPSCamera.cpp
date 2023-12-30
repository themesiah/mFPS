#include "FPSCamera.h"
#include "glm/gtc/matrix_transform.hpp"
#include "../Input/ActionManager.h"

namespace mFPS
{
	FPSCamera::FPSCamera() : mYaw(90.0f), mPitch(0.0f), CameraBase() {}

	void FPSCamera::Rotate(const float& yaw, const float& pitch)
	{
		mYaw += yaw;
		mPitch += pitch;
		if (mPitch > 80.0f)
			mPitch = 80.0f;
		if (mPitch < -80.0f)
			mPitch = -80.0f;
	}

	void FPSCamera::Update(const float& deltaTime, ActionManager* actionManager)
	{
		glm::vec2 lookDelta;
		glm::vec3 movementDelta = glm::vec3(0.0f, 0.0f, 0.0f);
		lookDelta.x = actionManager->GetValue("LookX");
		lookDelta.y = actionManager->GetValue("LookY");
		movementDelta.x = actionManager->GetValue("MoveX");
		movementDelta.z = actionManager->GetValue("MoveY");
		lookDelta *= deltaTime;
		movementDelta = movementDelta * 100.0f * deltaTime;
		Rotate(lookDelta.x, lookDelta.y);
		Translate(movementDelta);

		glm::vec3 forward = GetForward();

		mView = glm::lookAt(mPosition, mPosition + forward, mUp);
	}

	glm::vec3 FPSCamera::GetForward()
	{
		glm::vec3 direction;
		direction.x = cos(glm::radians(mYaw)) * cos(glm::radians(mPitch));
		direction.y = sin(glm::radians(mPitch));
		direction.z = sin(glm::radians(mYaw)) * cos(glm::radians(mPitch));
		glm::vec3 forward = glm::normalize(direction);
		return forward;
	}
}
#include "FPSCamera.h"
#include "glm/gtc/matrix_transform.hpp"

namespace mGL
{
	FPSCamera::FPSCamera() : mYaw(90.0f), mPitch(0.0f), CameraBase() {}

	void FPSCamera::Rotate(const float& yaw, const float& pitch)
	{
		mYaw += yaw;
		mPitch += pitch;
	}

	void FPSCamera::Update(const float& deltaTime)
	{
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
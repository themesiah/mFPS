#include "FPSCamera.h"
#include "glm/gtc/matrix_transform.hpp"
#include "../InputManager.h"

namespace mFPS
{
	FPSCamera::FPSCamera() : mYaw(90.0f), mPitch(0.0f), CameraBase() {}

	void FPSCamera::Rotate(const float& yaw, const float& pitch)
	{
		mYaw += yaw;
		mPitch += pitch;
	}

	void FPSCamera::Update(const float& deltaTime, InputManager* inputManager)
	{
		glm::vec2 lookDelta = inputManager->GetMouseDelta();
		Rotate(lookDelta.x * 3.0f * deltaTime, lookDelta.y * 3.0f * deltaTime);
		glm::vec3 movementDelta = glm::vec3(0.0f, 0.0f, 0.0f);
		if (inputManager->IsKeyDown(GLFW_KEY_A))
		{
			movementDelta.x = -100.0f * deltaTime;
		}
		if (inputManager->IsKeyDown(GLFW_KEY_D))
		{
			movementDelta.x = 100.0f * deltaTime;
		}
		if (inputManager->IsKeyDown(GLFW_KEY_W))
		{
			movementDelta.z = 100.0f * deltaTime;
		}
		if (inputManager->IsKeyDown(GLFW_KEY_S))
		{
			movementDelta.z = -100.0f * deltaTime;
		}
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
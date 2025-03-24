#include "FPSCamera.h"
#include "glm/gtc/matrix_transform.hpp"
#include "../Input/ActionManager.h"
#include "ImGui/imgui.h"

namespace mFPS
{
	FPSCamera::FPSCamera() : mEuler({0.0f, 90.0f, 0.0f}), CameraBase() {}

	void FPSCamera::Rotate(const float &yaw, const float &pitch)
	{
		mEuler.y += yaw;
		mEuler.x += pitch;
		if (mEuler.x > 80.0f)
			mEuler.x = 80.0f;
		if (mEuler.x < -80.0f)
			mEuler.x = -80.0f;
		if (mEuler.y > 180.0f)
			mEuler.y -= 360.0f;
		if (mEuler.y < -180.0f)
			mEuler.y += 360.0f;
	}

	void FPSCamera::Update(const float &deltaTime, ActionManager *actionManager)
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

#ifdef _DEBUG
	void FPSCamera::ShowImGui()
	{
		if (ImGui::CollapsingHeader("Camera"))
		{
			ImGui::Indent(1.0f);
			ImGui::SliderFloat3("Position", &mPosition[0], -1000.0f, 1000.0f);
			ImGui::SliderFloat3("Rotation", &mEuler[0], -180.0f, 180.0f);
			ImGui::Unindent(1.0f);
		}
	}
#endif

	glm::vec3 FPSCamera::GetForward()
	{
		glm::vec3 direction;
		direction.x = cos(glm::radians(mEuler.y)) * cos(glm::radians(mEuler.x));
		direction.y = sin(glm::radians(mEuler.x));
		direction.z = sin(glm::radians(mEuler.y)) * cos(glm::radians(mEuler.x));
		glm::vec3 forward = glm::normalize(direction);
		return forward;
	}
}
#include "CameraBase.h"
#include <glm/gtc/matrix_transform.hpp>

namespace mGL
{
	CameraBase::CameraBase() : mPosition(glm::vec3(0.0f,0.0f,-5.0f)), mUp(glm::vec3(0.0f,1.0f,0.0f)), mView(), mProjection()
	{
	}

	void CameraBase::SetPosition(const glm::vec3 &position)
	{
		mPosition = position;
	}

	void CameraBase::Translate(const glm::vec3 &movement)
	{
		glm::vec3 forward = GetForward();
		glm::vec3 right = glm::cross(forward, mUp);
		mPosition = mPosition + GetForward() * movement.z + mUp * movement.y + right * movement.x;
	}

	void CameraBase::SetUp(const glm::vec3& up)
	{
		mUp = up;
	}

	void CameraBase::SetProjection(const glm::mat4 projection)
	{
		mProjection = projection;
	}

	const glm::vec3 CameraBase::GetPosition() const
	{
		return mPosition;
	}

	const glm::mat4 CameraBase::GetView() const
	{
		return mView;
	}

	const glm::mat4 CameraBase::GetProjection() const
	{
		return mProjection;
	}
}
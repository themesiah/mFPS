#include "CameraBase.h"

namespace mGL
{
	CameraBase::CameraBase() : mPosition(glm::vec3(0.0f,0.0f,-5.0f)), mUp(glm::vec3(0.0f,1.0f,0.0f)), mView(), mProjection()
	{
	}

	void CameraBase::SetPosition(const glm::vec3& position)
	{
		mPosition = position;
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
#include "CameraBase.h"
#include "glm/gtc/matrix_transform.hpp"

namespace mGL
{
	CameraBase::CameraBase() : mPosition(glm::vec3(0.0f,0.0f,-5.0f)), mUp(glm::vec3(0.0f,1.0f,0.0f)), mTarget(), mView(), mProjection()
	{
	}

	void CameraBase::SetPosition(const glm::vec3& position)
	{
		mPosition = position;
	}

	void CameraBase::SetTarget(const glm::vec3& target)
	{
		mTarget = target;
	}

	void CameraBase::SetUp(const glm::vec3& up)
	{
		mUp = up;
	}

	void CameraBase::SetProjection(const glm::mat4 projection)
	{
		mProjection = projection;
	}

	void CameraBase::Update(const float& deltaTime)
	{
		mView = glm::lookAt(mPosition, mTarget, mUp);
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
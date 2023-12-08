#ifndef MGL_CAMERA_BASE
#define MGL_CAMERA_BASE

#include "glm/glm.hpp"

namespace mGL
{
	class CameraBase
	{
	public:
		CameraBase();
		void SetTarget(const glm::vec3 &target);
		void SetPosition(const glm::vec3 &position);
		void SetUp(const glm::vec3 &up);
		void SetProjection(const glm::mat4 projection);
		virtual void Update(const float &deltaTime);
		const glm::mat4 GetView() const;
		const glm::mat4 GetProjection() const;
	private:
		glm::vec3 mPosition;
		glm::vec3 mTarget;
		glm::vec3 mUp;
		glm::mat4 mView;
		glm::mat4 mProjection;
	};
}

#endif

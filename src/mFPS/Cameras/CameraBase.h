#ifndef MGL_CAMERA_BASE
#define MGL_CAMERA_BASE

#include "glm/glm.hpp"

namespace mFPS
{
	class InputManager;
	class CameraBase
	{
	public:
		CameraBase();
		void SetPosition(const glm::vec3 &position);
		void Translate(const glm::vec3 &movement);
		void SetUp(const glm::vec3 &up);
		void SetProjection(const glm::mat4 projection);
		const glm::vec3 GetPosition() const;
		virtual void Update(const float &deltaTime, InputManager* inputManager) = 0;
		virtual glm::vec3 GetForward() = 0;
		const glm::mat4 GetView() const;
		const glm::mat4 GetProjection() const;
	protected:
		glm::vec3 mPosition;
		glm::vec3 mUp;
		glm::mat4 mView;
		glm::mat4 mProjection;
	};
}

#endif

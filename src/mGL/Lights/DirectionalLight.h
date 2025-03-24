#ifndef MGL_DIRLIGHT
#define MGL_DIRLIGHT

#include "Light.h"

namespace mGL
{
	class DirectionalLight : public Light
	{
	public:
		DirectionalLight(tinyxml2::XMLElement *element);
		virtual ~DirectionalLight();
		void Set() override;

	protected:
#ifdef EDITOR_MODE
		virtual void ShowImGui() override;
#endif
	private:
		glm::vec4 mDirection;
	};
}

#endif
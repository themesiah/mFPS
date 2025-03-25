#ifndef MGL_AMBIENTLIGHT
#define MGL_AMBIENTLIGHT

#include "Light.h"

namespace mGL
{
	class AmbientLight : public Light
	{
	public:
		AmbientLight(tinyxml2::XMLElement *element);
		virtual ~AmbientLight();
		void Set() override;

	protected:
#ifdef EDITOR_MODE
		virtual bool ShowImGui() override;
#endif
	};
}

#endif
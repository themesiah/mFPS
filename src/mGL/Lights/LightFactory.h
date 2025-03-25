#ifndef MGL_LIGHTFACTORY
#define MGL_LIGHTFACTORY

#include <memory>

namespace tinyxml2
{
	class XMLElement;
}

namespace mGL
{
	class Light;
	class LightFactory
	{
	public:
		static std::shared_ptr<Light> GetLight(tinyxml2::XMLElement *element);
	};
}

#endif
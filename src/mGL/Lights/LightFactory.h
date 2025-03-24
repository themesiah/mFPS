#ifndef MGL_LIGHTFACTORY
#define MGL_LIGHTFACTORY

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
		static Light *GetLight(tinyxml2::XMLElement *element);
	};
}

#endif
#include "LightFactory.h"

#include "Light.h"
#include "DirectionalLight.h"
#include "AmbientLight.h"
#include "XML/tinyxml2.h"
#include "XML/XML.h"

namespace mGL
{
	Light *LightFactory::GetLight(tinyxml2::XMLElement *element)
	{
		Light *light = nullptr;
		const char *type;
		if (element->QueryStringAttribute("type", &type) != tinyxml2::XML_SUCCESS)
			return light;

		if (strcmp(type, "Directional") == 0)
		{
			light = new DirectionalLight(element);
		}
		else if (strcmp(type, "Point") == 0)
		{
			// TODO
		}
		else if (strcmp(type, "Ambient") == 0)
		{
			light = new AmbientLight(element);
		}
		return light;
	}
}
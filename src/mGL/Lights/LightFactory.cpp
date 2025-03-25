#include "LightFactory.h"

#include "Light.h"
#include "DirectionalLight.h"
#include "AmbientLight.h"
#include "PointLight.h"
#include "XML/tinyxml2.h"
#include "XML/XML.h"

namespace mGL
{
	std::shared_ptr<Light> LightFactory::GetLight(tinyxml2::XMLElement *element)
	{
		std::shared_ptr<Light> light = nullptr;
		const char *type;
		if (element->QueryStringAttribute("type", &type) != tinyxml2::XML_SUCCESS)
			return light;

		if (strcmp(type, "Directional") == 0)
		{
			light = std::make_shared<DirectionalLight>(element);
		}
		else if (strcmp(type, "Point") == 0)
		{
			light = std::make_shared<PointLight>(element);
		}
		else if (strcmp(type, "Ambient") == 0)
		{
			light = std::make_shared<AmbientLight>(element);
		}
		return light;
	}
}
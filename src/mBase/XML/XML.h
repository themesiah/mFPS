#ifndef MBASE_XML
#define MBASE_XML

#include "tinyxml2.h"
#include "glm/glm.hpp"

namespace tinyxml2
{
	XMLError QueryVec2Attribute(const XMLElement* element, const char* attName, glm::vec2* vec);
	XMLError QueryVec3Attribute(const XMLElement* element, const char* attName, glm::vec3* vec);
	XMLError QueryVec4Attribute(const XMLElement* element, const char* attName, glm::vec4* vec);
}

#endif
#include "XML.h"

#include <string>
#include <vector>

#include "../StringUtils.h"

namespace tinyxml2
{
	XMLError QueryVec2Attribute(const XMLElement* element, const char* attName, glm::vec2* vec)
	{
		const XMLAttribute* a = element->FindAttribute(attName);
		if (!a) {
			return XML_NO_ATTRIBUTE;
		}
		std::string value = a->Value();
		std::vector<std::string> values;
		mBase::Strings::Split(value, values, " ");
		if (values.size() < 2)
			return XML_WRONG_ATTRIBUTE_TYPE;
		if (!XMLUtil::ToFloat(values[0].c_str(), &vec->x) || !XMLUtil::ToFloat(values[1].c_str(), &vec->y))
			return XML_WRONG_ATTRIBUTE_TYPE;

		return XML_SUCCESS;
	}

	XMLError QueryVec3Attribute(const XMLElement* element, const char* attName, glm::vec3* vec)
	{
		const XMLAttribute* a = element->FindAttribute(attName);
		if (!a) {
			return XML_NO_ATTRIBUTE;
		}
		std::string value = a->Value();
		std::vector<std::string> values;
		mBase::Strings::Split(value, values, " ");
		if (values.size() < 3)
			return XML_WRONG_ATTRIBUTE_TYPE;
		if (!XMLUtil::ToFloat(values[0].c_str(), &vec->x) || !XMLUtil::ToFloat(values[1].c_str(), &vec->y) || !XMLUtil::ToFloat(values[2].c_str(), &vec->z))
			return XML_WRONG_ATTRIBUTE_TYPE;

		return XML_SUCCESS;
	}

	XMLError QueryVec4Attribute(const XMLElement* element, const char* attName, glm::vec4* vec)
	{
		const XMLAttribute* a = element->FindAttribute(attName);
		if (!a) {
			return XML_NO_ATTRIBUTE;
		}
		std::string value = a->Value();
		std::vector<std::string> values;
		mBase::Strings::Split(value, values, " ");
		if (values.size() < 4)
			return XML_WRONG_ATTRIBUTE_TYPE;
		if (!XMLUtil::ToFloat(values[0].c_str(), &vec->x) || !XMLUtil::ToFloat(values[1].c_str(), &vec->y)
			|| !XMLUtil::ToFloat(values[2].c_str(), &vec->z) || !XMLUtil::ToFloat(values[3].c_str(), &vec->w))
			return XML_WRONG_ATTRIBUTE_TYPE;

		return XML_SUCCESS;
	}
}
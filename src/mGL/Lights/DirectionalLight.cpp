#include "DirectionalLight.h"

#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>

#include "XML/tinyxml2.h"
#include "XML/XML.h"
#ifdef EDITOR_MODE
#include "ImGui/imgui.h"
#endif

namespace mGL
{
	DirectionalLight::DirectionalLight(tinyxml2::XMLElement *element) : Light(element)
	{
		tinyxml2::XMLElement *transformElement = element->FirstChildElement("transform");
		if (transformElement != NULL)
		{
			glm::vec3 euler = {0.0f, 0.0f, 0.0f};
			if (tinyxml2::QueryVec3Attribute(transformElement, "rotation", &euler) == tinyxml2::XML_SUCCESS)
			{
				mDirection.x = cos(glm::radians(euler.y)) * cos(glm::radians(euler.x));
				mDirection.y = sin(glm::radians(euler.y)) * cos(glm::radians(euler.x));
				mDirection.z = sin(glm::radians(euler.x));
			}
		}
	}

	DirectionalLight::~DirectionalLight()
	{
	}

	void DirectionalLight::Set(const size_t &offset)
	{
		DirectionalLightBuffer data;

		data.direction = mDirection;
		data.direction.y *= -1.0f;
		data.colorIntensity.x = mColor.x;
		data.colorIntensity.y = mColor.y;
		data.colorIntensity.z = mColor.z;
		data.colorIntensity.w = mIntensity;

		glBufferSubData(GL_SHADER_STORAGE_BUFFER, offset, sizeof(data), &data);
	}

#ifdef EDITOR_MODE
	bool DirectionalLight::ShowImGui()
	{
		bool dirty = false;
		if (ImGui::SliderFloat3("Direction", &mDirection[0], -1.0f, 1.0f))
		{
			dirty = true;
		}
		return dirty;
	}
#endif
}
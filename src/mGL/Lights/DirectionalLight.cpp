#include <glm/gtc/matrix_transform.hpp>
#include "GL/glew.h"

#include "DirectionalLight.h"
#include "mBase/XML/tinyxml2.h"
#include "mBase/XML/XML.h"
#ifdef _DEBUG
#include "mBase/ImGui/imgui.h"
#endif

namespace mGL
{
	DirectionalLight::DirectionalLight(tinyxml2::XMLElement* element)
	{
		mMatrix = std::shared_ptr<glm::mat4>(new glm::mat4(1.0f));
		tinyxml2::XMLElement* transformElement = element->FirstChildElement("transform");
		glm::vec3 pos = { 0.0f, 0.0f, 0.0f };
		if (tinyxml2::QueryVec3Attribute(transformElement, "position", &pos) == tinyxml2::XML_SUCCESS)
		{
			*mMatrix = glm::translate(*mMatrix, pos);
		}
		glm::vec3 scale = { 1.0f, 1.0f, 1.0f };
		if (tinyxml2::QueryVec3Attribute(transformElement, "scale", &scale) == tinyxml2::XML_SUCCESS)
		{
			*mMatrix = glm::scale(*mMatrix, scale);
		}
		glm::vec3 euler = { 0.0f, 0.0f, 0.0f };
		if (tinyxml2::QueryVec3Attribute(transformElement, "rotation", &euler) == tinyxml2::XML_SUCCESS)
		{
			*mMatrix = glm::rotate(*mMatrix, glm::radians(euler.x), { 1.0f, 0.0f, 0.0f });
			*mMatrix = glm::rotate(*mMatrix, glm::radians(euler.y), { 0.0f, 1.0f, 0.0f });
			*mMatrix = glm::rotate(*mMatrix, glm::radians(euler.z), { 0.0f, 0.0f, 1.0f });
			mDirection.x = cos(glm::radians(euler.y)) * cos(glm::radians(euler.x));
			mDirection.y = sin(glm::radians(euler.y)) * cos(glm::radians(euler.x));
			mDirection.z = sin(glm::radians(euler.x));
		}

		tinyxml2::XMLElement* dataElement = element->FirstChildElement("data");
		glm::vec3 color;
		if (tinyxml2::QueryVec3Attribute(dataElement, "color", &color) == tinyxml2::XML_SUCCESS)
		{
			mColor = color;
		}
		float intensity;
		if (dataElement->QueryFloatAttribute("intensity", &intensity) == tinyxml2::XML_SUCCESS)
		{
			mIntensity = intensity;
		}

		glGenBuffers(1, &mSSBO);
	}

	std::shared_ptr<glm::mat4> DirectionalLight::GetMatrix() const
	{
		return mMatrix;
	}

	void DirectionalLight::Set()
	{
		struct {
			glm::vec4 direction;
			glm::vec4 colorIntensity;
		} data;

		data.direction = mDirection;
		data.direction.y *= -1.0f;
		data.colorIntensity.x = mColor.x;
		data.colorIntensity.y = mColor.y;
		data.colorIntensity.z = mColor.z;
		data.colorIntensity.w = mIntensity;

		glBindBuffer(GL_SHADER_STORAGE_BUFFER, mSSBO);
		glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(data), &data, GL_STATIC_DRAW);
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 3, mSSBO);
	}

#ifdef _DEBUG
	void DirectionalLight::ShowImGui()
	{
		if (ImGui::TreeNode("Directional Light"))
		{
			if (ImGui::SliderFloat3("Direction", &mDirection[0], -1.0f, 1.0f))
			{
				Set();
			}
			ImGui::TreePop();
			ImGui::Spacing();
		}
	}
#endif
}
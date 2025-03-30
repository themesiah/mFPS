#include "Light.h"
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include "../MeshFactory.h"
#include "../Renderable/RenderableObject.h"
#include "../Renderable/RenderableModel.h"
#include "../Material/Material.h"
#include "../Material/MaterialColorParameter.h"

#include "XML/tinyxml2.h"
#include "XML/XML.h"
#ifdef EDITOR_MODE
#include "ImGui/imgui.h"
#endif

namespace mGL
{
	Light::Light(tinyxml2::XMLElement *element)
	{
		const char *name;
		auto result = element->QueryStringAttribute("name", &name);
		assert(result == tinyxml2::XML_SUCCESS);
		mName = std::string(name);

		mMatrix = std::shared_ptr<glm::mat4>(new glm::mat4(1.0f));
		tinyxml2::XMLElement *transformElement = element->FirstChildElement("transform");
		if (transformElement != NULL)
		{
			glm::vec3 pos = {0.0f, 0.0f, 0.0f};
			if (tinyxml2::QueryVec3Attribute(transformElement, "position", &pos) == tinyxml2::XML_SUCCESS)
			{
				*mMatrix = glm::translate(*mMatrix, pos);
			}
			glm::vec3 scale = {1.0f, 1.0f, 1.0f};
			if (tinyxml2::QueryVec3Attribute(transformElement, "scale", &scale) == tinyxml2::XML_SUCCESS)
			{
				*mMatrix = glm::scale(*mMatrix, scale);
			}
			glm::vec3 euler = {0.0f, 0.0f, 0.0f};
			if (tinyxml2::QueryVec3Attribute(transformElement, "rotation", &euler) == tinyxml2::XML_SUCCESS)
			{
				*mMatrix = glm::rotate(*mMatrix, glm::radians(euler.x), {1.0f, 0.0f, 0.0f});
				*mMatrix = glm::rotate(*mMatrix, glm::radians(euler.y), {0.0f, 1.0f, 0.0f});
				*mMatrix = glm::rotate(*mMatrix, glm::radians(euler.z), {0.0f, 0.0f, 1.0f});
			}
		}

		tinyxml2::XMLElement *dataElement = element->FirstChildElement("data");
		mColor = glm::vec3(1, 1, 1);
		tinyxml2::QueryVec3Attribute(dataElement, "color", &mColor);
		mIntensity = 0;
		dataElement->QueryFloatAttribute("intensity", &mIntensity);

		glGenBuffers(1, &mSSBO);

		mIcon = std::static_pointer_cast<RenderableModel>(MeshFactory::LoadObj("CommonResources/Light.obj"));
	}

	Light::~Light()
	{
		glDeleteBuffers(1, &mSSBO);
	}

	std::shared_ptr<glm::mat4> Light::GetMatrix() const
	{
		return mMatrix;
	}

	std::string Light::GetName() const
	{
		return mName;
	}

	void Light::SetColor(const glm::vec3 &color)
	{
		mColor = color;
	}

	void Light::SetIntensity(const float &intensity)
	{
		mIntensity = intensity;
	}

#ifdef EDITOR_MODE
	bool Light::StartImGui()
	{
		bool dirty = false;
		if (ImGui::TreeNode(mName.c_str()))
		{
			ImGui::Indent(10.0f);
			if (ImGui::SliderFloat3("Position", &(*mMatrix)[3][0], -100.0f, 100.0f))
			{
				dirty = true;
			}

			if (ImGui::SliderFloat("Intensity", &mIntensity, 0.0f, 1.0f))
			{
				dirty = true;
			}

			if (ImGui::SliderFloat3("Color", &mColor[0], 0.0f, 1.0f))
			{
				dirty = true;
			}
			if (ShowImGui())
				dirty = true;
			ImGui::Unindent(10.0f);
			ImGui::TreePop();
		}
		return dirty;
	}

	std::shared_ptr<RenderableObject> Light::GetIcon() const
	{
		return mIcon;
	}
#endif
}
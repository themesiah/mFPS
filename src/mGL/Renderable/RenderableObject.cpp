#include "RenderableObject.h"
#include "../Mesh.h"
#include "../Material/Material.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include "ImGui/imgui.h"
#include "XML/tinyxml2.h"
#include "XML/XML.h"

namespace mGL
{
	RenderableObject::RenderableObject() : mMatrix(new glm::mat4(1.0f)), mName("NONAME")
	{
	}

	RenderableObject::RenderableObject(tinyxml2::XMLElement *element) : mMatrix(new glm::mat4(1.0f))
	{
		const char *cname;
		if (element->QueryStringAttribute("name", &cname) == tinyxml2::XML_SUCCESS)
		{
			mName = std::string(cname);
		}

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
	}

	RenderableObject::RenderableObject(RenderableObject &ro)
	{
		mMatrix = ro.mMatrix;
		mName = ro.mName;
	}

	RenderableObject &RenderableObject::operator=(RenderableObject &ro)
	{
		mMatrix = ro.mMatrix;
		mName = ro.mName;

		return *this;
	}

	RenderableObject::~RenderableObject()
	{
	}

	void RenderableObject::SetName(const std::string &name)
	{
		mName = name;
	}

	std::shared_ptr<glm::mat4> RenderableObject::GetMatrix() const
	{
		return mMatrix;
	}

#ifdef EDITOR_MODE
	void RenderableObject::ShowImGui()
	{
		if (ImGui::TreeNode(mName.c_str()))
		{
			ImGui::Indent(1.0f);
			ImGui::Text("Nothing to see here yet");
			ImGui::Unindent(1.0f);
			ImGui::TreePop();
		}
	}
#endif
}
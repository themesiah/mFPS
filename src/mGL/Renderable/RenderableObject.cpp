#include "RenderableObject.h"
#include "../Mesh.h"
#include "../Material/Material.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtx/quaternion.hpp>
#include "ImGui/imgui.h"
#include "XML/tinyxml2.h"
#include "XML/XML.h"

#include "Logger.h"

namespace mGL
{
	RenderableObject::RenderableObject() : mName("NONAME"), mMatrix(new glm::mat4(1.0f))
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
			ImGui::Indent(10.0f);
			glm::vec3 translation, scale, skew;
			glm::vec4 perspective;
			glm::quat oldRotation;

			// Decompose the matrix
			glm::decompose(*mMatrix, scale, oldRotation, translation, skew, perspective);

			if (ImGui::SliderFloat3("Position", &(*mMatrix)[3][0], -100.0f, 100.0f))
			{
			}
			if (ImGui::SliderFloat4("Rotation", &oldRotation.x, -1, 1))
			{
				oldRotation = glm::normalize(oldRotation);
				glm::mat4 newRotationMatrix = glm::toMat4(oldRotation);

				*mMatrix = glm::translate(glm::mat4(1.0f), translation) * newRotationMatrix * glm::scale(glm::mat4(1.0f), scale);
			}
			ImGui::Unindent(10.0f);
			ImGui::TreePop();
		}
	}
#endif
}
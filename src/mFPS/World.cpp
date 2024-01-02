#include "World.h"

#include "mBase/XML/tinyxml2.h"
#include "mBase/XML/XML.h"
#include "mBase/Logger.h"
#include "mGL/MeshFactory.h"
#include "glm/glm.hpp"
#include "mBase/CheckedDelete.h"
#include "mGL/Lights/LightFactory.h"
#include "mGL/Lights/Light.h"

#ifdef _DEBUG
#include "mBase/ImGui/imgui.h"
#endif

namespace mFPS
{
	World::World() : mRenderableObjects({}) {}

	World::~World()
	{
		for (int i = 0; i < mRenderableObjects.size(); ++i)
		{
			mBase::CheckedDelete(mRenderableObjects[i]);
		}
	}

	void World::AddRenderableObject(mGL::RenderableObject* renderableObject)
	{
		mRenderableObjects.push_back(renderableObject);
	}
	
	const std::vector<mGL::RenderableObject*> World::GetRenderableObjects() const
	{
		return mRenderableObjects;
	}

	void World::FromXML(const std::string& path)
	{
		tinyxml2::XMLDocument doc;
		std::string fullPath = "Data/World/" + path;
		Logger::Log("World", "Trying to load world at path " + fullPath);
		doc.LoadFile(fullPath.c_str());
		
		if (doc.ErrorID() == tinyxml2::XML_SUCCESS)
		{
			tinyxml2::XMLElement* world = doc.FirstChildElement("world");
			tinyxml2::XMLElement* object = world->FirstChildElement("object");
		
			while (object != NULL)
			{
				const char* modelName;
				object->QueryStringAttribute("model", &modelName);
				mGL::RenderableObject* renderableObject = mGL::MeshFactory::LoadObj(modelName);
				tinyxml2::XMLElement* transformElement = object->FirstChildElement("transform");
				glm::vec3 pos = { 0.0f, 0.0f, 0.0f };
				if (transformElement != NULL) {
					if (tinyxml2::QueryVec3Attribute(transformElement, "position", &pos) == tinyxml2::XML_SUCCESS)
					{
						*renderableObject->GetMatrix() = glm::translate(*renderableObject->GetMatrix(), pos);
					}
					glm::vec3 scale = { 1.0f, 1.0f, 1.0f };
					if (tinyxml2::QueryVec3Attribute(transformElement, "scale", &scale) == tinyxml2::XML_SUCCESS)
					{
						*renderableObject->GetMatrix() = glm::scale(*renderableObject->GetMatrix(), scale);
					}
					glm::vec3 euler = { 0.0f, 0.0f, 0.0f };
					if (tinyxml2::QueryVec3Attribute(transformElement, "rotation", &euler) == tinyxml2::XML_SUCCESS)
					{
						*renderableObject->GetMatrix() = glm::rotate(*renderableObject->GetMatrix(), glm::radians(euler.x), { 1.0f, 0.0f, 0.0f });
						*renderableObject->GetMatrix() = glm::rotate(*renderableObject->GetMatrix(), glm::radians(euler.y), { 0.0f, 1.0f, 0.0f });
						*renderableObject->GetMatrix() = glm::rotate(*renderableObject->GetMatrix(), glm::radians(euler.z), { 0.0f, 0.0f, 1.0f });
					}
				}

				AddRenderableObject(renderableObject);
				object = object->NextSiblingElement();
			}

			tinyxml2::XMLElement* lightObject = world->FirstChildElement("light");

			while (lightObject != NULL)
			{
				mGL::Light* light = mGL::LightFactory::GetLight(lightObject);
				light->Set();
				mLights.push_back(light);
				lightObject = lightObject->NextSiblingElement();
			}
		}
		else
		{
			Logger::Log("World", "Failed loading XML");
		}
		doc.Clear();
	}

#ifdef _DEBUG
	void World::ShowImGui()
	{
		if (ImGui::CollapsingHeader("World"))
		{
			for (int i = 0; i < mLights.size(); ++i)
			{
				mLights[i]->StartImGui();
			}
			ImGui::Spacing();
		}
	}
#endif
}
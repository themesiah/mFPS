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
#ifdef _DEBUG
		std::vector<mGL::RenderableObject*> renderables = mRenderableObjects;
		for (unsigned int i = 0; i < mLights.size(); ++i)
		{
			renderables.push_back(mLights[i]->GetIcon());
		}
		return renderables;
#else
		return mRenderableObjects;
#endif
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
			if (world != NULL) {
				tinyxml2::XMLElement* objects = world->FirstChildElement("objects");
				if (objects != NULL) {
					tinyxml2::XMLElement* object = objects->FirstChildElement("object");

					while (object != NULL)
					{
						mGL::RenderableObject* renderableObject = mGL::MeshFactory::LoadObj(object);
						AddRenderableObject(renderableObject);
						object = object->NextSiblingElement();
					}
				}

				tinyxml2::XMLElement* lights = world->FirstChildElement("lights");
				if (lights != NULL) {
					tinyxml2::XMLElement* lightObject = lights->FirstChildElement("light");

					while (lightObject != NULL)
					{
						mGL::Light* light = mGL::LightFactory::GetLight(lightObject);
						light->Set();
						mLights.push_back(light);
						lightObject = lightObject->NextSiblingElement();
					}
				}
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
			ImGui::Indent(1.0f);
			if (ImGui::CollapsingHeader("Objects"))
			{
				for (int i = 0; i < mRenderableObjects.size(); ++i)
				{
					mRenderableObjects[i]->ShowImGui();
				}
				ImGui::Spacing();
			}
			if (ImGui::CollapsingHeader("Lights")) {
				for (int i = 0; i < mLights.size(); ++i)
				{
					mLights[i]->StartImGui();
				}
				ImGui::Spacing();
			}
			ImGui::Unindent(1.0f);
		}
	}
#endif
}
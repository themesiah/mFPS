#include "World.h"

#include "XML/tinyxml2.h"
#include "XML/XML.h"
#include "Logger.h"
#include "MeshFactory.h"
#include "glm/glm.hpp"
#include "CheckedDelete.h"
#include "Lights/LightFactory.h"
#include "Lights/Light.h"
#include "Lights/LightsManager.h"

#ifdef EDITOR_MODE
#include "ImGui/imgui.h"
#endif

namespace mFPS
{
	World::World() : mRenderableObjects({}), mLightsManager(std::make_unique<mGL::LightsManager>()) {}

	World::~World()
	{
	}

	void World::AddRenderableObject(std::shared_ptr<mGL::RenderableObject> renderableObject)
	{
		mRenderableObjects.push_back(renderableObject);
	}

	const std::vector<std::shared_ptr<mGL::RenderableObject>> World::GetRenderableObjects() const
	{
#ifdef EDITOR_MODE
		std::vector<std::shared_ptr<mGL::RenderableObject>> renderables = mRenderableObjects;
		for (unsigned int i = 0; i < mLightsManager->GetCount(); ++i)
		{
			renderables.push_back(mLightsManager->operator[](i)->GetIcon());
		}
		return renderables;
#else
		return mRenderableObjects;
#endif
	}

	void World::FromXML(const std::string &path)
	{
		tinyxml2::XMLDocument doc;
		std::string fullPath = "Data/World/" + path;
		Logger::Log("World", "Trying to load world at path " + fullPath);
		doc.LoadFile(fullPath.c_str());

		if (doc.ErrorID() == tinyxml2::XML_SUCCESS)
		{
			tinyxml2::XMLElement *world = doc.FirstChildElement("world");
			if (world != NULL)
			{
				tinyxml2::XMLElement *objects = world->FirstChildElement("objects");
				if (objects != NULL)
				{
					tinyxml2::XMLElement *object = objects->FirstChildElement("object");

					while (object != NULL)
					{
						std::shared_ptr<mGL::RenderableObject> renderableObject = mGL::MeshFactory::LoadObj(object);
						AddRenderableObject(renderableObject);
						object = object->NextSiblingElement();
					}
				}

				mLightsManager->InitBuffers();
				tinyxml2::XMLElement *lights = world->FirstChildElement("lights");
				if (lights != NULL)
				{
					tinyxml2::XMLElement *lightObject = lights->FirstChildElement("light");

					while (lightObject != NULL)
					{
						std::shared_ptr<mGL::Light> light = mGL::LightFactory::GetLight(lightObject);
						mLightsManager->Add(light->GetName(), light);
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

	void World::Update(const float &deltaTime)
	{
		mLightsManager->Update();
	}

#ifdef EDITOR_MODE
	void World::ShowImGui()
	{
		if (ImGui::CollapsingHeader("World"))
		{
			ImGui::Indent(10.0f);
			if (ImGui::CollapsingHeader("Objects"))
			{
				for (size_t i = 0; i < mRenderableObjects.size(); ++i)
				{
					mRenderableObjects[i]->ShowImGui();
				}
				ImGui::Spacing();
			}
			if (ImGui::CollapsingHeader("Lights"))
			{
				mLightsManager->ShowImGui();
				ImGui::Spacing();
			}
			ImGui::Unindent(10.0f);
		}
	}
#endif
}
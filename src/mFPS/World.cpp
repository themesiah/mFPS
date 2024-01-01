#include "World.h"

#include "mBase/XML/tinyxml2.h"
#include "mBase/XML/XML.h"
#include "mBase/Logger.h"
#include "mGL/MeshFactory.h"
#include "glm/glm.hpp"
#include "mBase/CheckedDelete.h"

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
				glm::vec3 pos;
				if (tinyxml2::QueryVec3Attribute(transformElement, "position", &pos) == tinyxml2::XML_SUCCESS)
				{
					*renderableObject->GetMatrix() = glm::translate(*renderableObject->GetMatrix(), pos);
				}
				glm::vec3 scale;
				if (tinyxml2::QueryVec3Attribute(transformElement, "scale", &scale) == tinyxml2::XML_SUCCESS)
				{
					*renderableObject->GetMatrix() = glm::scale(*renderableObject->GetMatrix(), scale);
				}

				AddRenderableObject(renderableObject);
				object = object->NextSiblingElement();
			}
		}
		else
		{
			Logger::Log("World", "Failed loading XML");
		}
		doc.Clear();
	}
}
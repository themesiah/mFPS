#include "World.h"

#include "mBase/XML/tinyxml2.h"
#include "mBase/XML/XML.h"
#include "mBase/Logger.h"
#include "mGL/MeshFactory.h"
#include "glm/glm.hpp"

namespace mFPS
{
	World::World() : mRenderableObjects({}) {}
	World::~World()
	{
		for (int i = 0; i < mRenderableObjects.size(); ++i)
		{
			delete mRenderableObjects[i];
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
				tinyxml2::XMLElement* position = object->FirstChildElement("position");
				glm::vec3 pos;
				tinyxml2::QueryVec3Attribute(position, "xyz", &pos);
				*renderableObject->GetMatrix() = glm::translate(*renderableObject->GetMatrix(), pos);

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
#include "World.h"

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
}
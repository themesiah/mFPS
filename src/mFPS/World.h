#ifndef MFPS_WORLD
#define MFPS_WORLD

#include <vector>

#include "mGL/RenderableObject.h"

namespace mFPS
{
	class World
	{
	public:
		World();
		~World();
		void AddRenderableObject(mGL::RenderableObject* renderableObject);
		const std::vector<mGL::RenderableObject*> GetRenderableObjects() const;
	private:
		std::vector<mGL::RenderableObject*> mRenderableObjects;
	};
}

#endif
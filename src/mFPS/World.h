#ifndef MFPS_WORLD
#define MFPS_WORLD

#include <vector>
#include <string>
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
		void FromXML(const std::string& path);
	private:
		std::vector<mGL::RenderableObject*> mRenderableObjects;
	};
}

#endif
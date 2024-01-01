#ifndef MFPS_WORLD
#define MFPS_WORLD

#include <vector>
#include <string>
#include "mGL/Renderable/RenderableObject.h"
#include "mGL/Lights/DirectionalLight.h"

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
#ifdef _DEBUG
		void ShowImGui();
#endif
	private:
		std::vector<mGL::RenderableObject*> mRenderableObjects;
		std::vector<mGL::DirectionalLight*> mLights;
	};
}

#endif
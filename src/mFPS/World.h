#ifndef MFPS_WORLD
#define MFPS_WORLD

#include <vector>
#include <string>
#include <memory>
#include "Renderable/RenderableObject.h"

namespace mGL
{
	class Light;
	class LightsManager;
}

namespace mFPS
{
	class World
	{
	public:
		World();
		~World();
		void AddRenderableObject(std::shared_ptr<mGL::RenderableObject> renderableObject);
		const std::vector<std::shared_ptr<mGL::RenderableObject>> GetRenderableObjects() const;
		void FromXML(const std::string &path);
		void Update(const float &deltaTime);
#ifdef EDITOR_MODE
		void ShowImGui();
#endif
	private:
		std::vector<std::shared_ptr<mGL::RenderableObject>> mRenderableObjects;
		std::unique_ptr<mGL::LightsManager> mLightsManager;
	};
}

#endif
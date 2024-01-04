#ifndef MGL_LIGHTSMANAGER
#define MGL_LIGHTSMANAGER

#include <vector>

namespace mGL
{
	class Light;
	class LightsManager
	{
	public:
		LightsManager();
		~LightsManager();
		void Set();
	private:
		std::vector<Light*> mDirectionalLights;
		std::vector<Light*> mAmbientLights;
		std::vector<Light*> mPointLights;
	};
}

#endif
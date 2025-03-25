#ifndef MGL_LIGHTSMANAGER
#define MGL_LIGHTSMANAGER

#include <vector>
#include <memory>

#include "TemplatedMapVector.h"

namespace mGL
{
	class Light;
	class LightsManager : public mBase::TemplatedMapVector<Light>
	{
	public:
		LightsManager();
		~LightsManager();
		void Set() const;
		virtual bool Add(const std::string &aName, std::shared_ptr<Light> aLight) override;
		virtual void Clear() override;
		virtual void Destroy() override;
		virtual void Remove(const std::string &aName) override;
		void Update();
#ifdef EDITOR_MODE
		void ShowImGui();
#endif
	private:
		bool mDirty;
	};
}

#endif
#ifndef MGL_LIGHTSMANAGER
#define MGL_LIGHTSMANAGER

#include <vector>
#include <memory>

#include "TemplatedMapVector.h"

namespace mGL
{
	const size_t FIRST_LIGHT_TYPE = 3;
	const size_t LIGHT_TYPES_AMOUNT = 3;
	class Light;
	class LightsManager : public mBase::TemplatedMapVector<Light>
	{
	public:
		LightsManager();
		~LightsManager();
		void InitBuffers();
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
		std::array<unsigned int, LIGHT_TYPES_AMOUNT> mSSBOs;
	};
}

#endif
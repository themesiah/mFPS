#ifndef MGL_AMBIENTLIGHT
#define MGL_AMBIENTLIGHT

#include "Light.h"

namespace mGL
{
	struct AmbientLightBuffer
	{
		glm::vec4 colorIntensity;
	};

	class AmbientLight : public Light
	{
	public:
		AmbientLight(tinyxml2::XMLElement *element);
		virtual ~AmbientLight();
		void Set(const size_t &offset) override;
		virtual BindBufferTarget GetBindBufferTarget() const override { return BindBufferTarget::Ambient; };
		virtual size_t GetBufferSize() const override { return sizeof(AmbientLightBuffer); };

	protected:
#ifdef EDITOR_MODE
		virtual bool ShowImGui() override;
#endif
	};
}

#endif
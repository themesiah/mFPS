#ifndef MGL_DIRLIGHT
#define MGL_DIRLIGHT

#include "Light.h"

namespace mGL
{
	struct DirectionalLightBuffer
	{
		glm::vec4 direction;
		glm::vec4 colorIntensity;
	};

	class DirectionalLight : public Light
	{
	public:
		DirectionalLight(tinyxml2::XMLElement *element);
		virtual ~DirectionalLight();
		void Set(const size_t &offset) override;
		virtual BindBufferTarget GetBindBufferTarget() const override { return BindBufferTarget::Directional; };
		virtual size_t GetBufferSize() const override { return sizeof(DirectionalLightBuffer); };

	protected:
#ifdef EDITOR_MODE
		virtual bool ShowImGui() override;
#endif
	private:
		glm::vec4 mDirection;
	};
}

#endif
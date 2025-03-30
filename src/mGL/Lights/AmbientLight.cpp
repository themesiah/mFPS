#include "AmbientLight.h"

#include <GL/glew.h>

#include "ImGui/imgui.h"

namespace mGL
{
	AmbientLight::AmbientLight(tinyxml2::XMLElement *element) : Light(element) {}

	AmbientLight::~AmbientLight() {}

	void AmbientLight::Set(const size_t &offset)
	{
		AmbientLightBuffer data;

		data.colorIntensity.x = mColor.x;
		data.colorIntensity.y = mColor.y;
		data.colorIntensity.z = mColor.z;
		data.colorIntensity.w = mIntensity;

		glBufferSubData(GL_SHADER_STORAGE_BUFFER, offset, sizeof(data), &data);
	}

#ifdef EDITOR_MODE
	bool AmbientLight::ShowImGui()
	{
		return false;
	}
#endif
}
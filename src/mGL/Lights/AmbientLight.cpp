#include "AmbientLight.h"

#include <GL/glew.h>

#include "ImGui/imgui.h"

namespace mGL
{
	AmbientLight::AmbientLight(tinyxml2::XMLElement *element) : Light(element) {}

	AmbientLight::~AmbientLight() {}

	void AmbientLight::Set()
	{
		struct
		{
			glm::vec4 colorIntensity;
		} data;

		data.colorIntensity.x = mColor.x;
		data.colorIntensity.y = mColor.y;
		data.colorIntensity.z = mColor.z;
		data.colorIntensity.w = mIntensity;

		glBindBuffer(GL_SHADER_STORAGE_BUFFER, mSSBO);
		glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(data), &data, GL_STATIC_DRAW);
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 4, mSSBO);
	}

#ifdef EDITOR_MODE
	bool AmbientLight::ShowImGui()
	{
		return false;
	}
#endif
}
#include "MaterialColorParameter.h"
#include "../Shader.h"

#include "mBase/Logger.h"

namespace mGL
{
	MaterialColorParameter::MaterialColorParameter() : mColor() {}
	MaterialColorParameter::MaterialColorParameter(glm::vec4 color) : mColor(color) {}
	MaterialColorParameter::MaterialColorParameter(float r, float g, float b, float a) : mColor(glm::vec4(r, g, b, a)) {}

	MaterialColorParameter::MaterialColorParameter(const MaterialColorParameter& mcp)
	{
		mColor = mcp.mColor;
	}

	MaterialColorParameter& MaterialColorParameter::operator=(const MaterialColorParameter& mcp)
	{
		mColor = mcp.mColor;
		return *this;
	}

	MaterialColorParameter::~MaterialColorParameter()
	{
		Logger::Log("Material Color Parameter", "Destructor called");
	}

	void MaterialColorParameter::Bind(Shader* shader) const
	{
		shader->SetUniform4f("tint", mColor);
		shader->SetUniform1i("use_tint", true);
	}
}
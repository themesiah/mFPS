#include "IMaterialParameter.h"
#include "Shader.h"

namespace mGL
{
	MaterialColorParameter::MaterialColorParameter() : mColor(){}
	MaterialColorParameter::MaterialColorParameter(glm::vec4 color) : mColor(color){}
	MaterialColorParameter::MaterialColorParameter(float r, float g, float b, float a) : mColor(glm::vec4(r, g, b, a)){}

	void MaterialColorParameter::Bind(Shader* shader) const
	{
		shader->SetUniform4f("tint", mColor);
	}
}
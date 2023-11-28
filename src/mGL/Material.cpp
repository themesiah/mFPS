#include "Material.h"
#include "IMaterialParameter.h"

namespace mGL
{
	Material::Material() : mShader(nullptr), mParameters(){}

	Material::Material(Shader* shader) : mShader(shader), mParameters(){}

	Material::~Material()
	{
		for (int i = 0; i < mParameters.size(); ++i)
		{
			delete mParameters[i];
		}
	}

	void Material::Use()
	{
		for (int i = 0; i < mParameters.size(); ++i)
		{
			mParameters[i]->Bind(mShader.get());
		}
		mShader.get()->UseShader();
	}

	void Material::AddParameter(IMaterialParameter* parameter)
	{
		mParameters.push_back(parameter);
	}

	Shader* Material::GetShader()
	{
		return mShader.get();
	}
}
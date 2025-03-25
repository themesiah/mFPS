#include "Material.h"
#include "IMaterialParameter.h"

#include "Logger.h"

namespace mGL
{
	Material::Material() : mShader(nullptr), mParameters() {}

	Material::Material(Shader *shader) : mShader(shader), mParameters() {}

	Material::Material(const Material &m)
	{
		mParameters = m.mParameters;
		mShader = m.mShader;
	}

	Material &Material::operator=(const Material &m)
	{
		mParameters = m.mParameters;
		mShader = m.mShader;

		return *this;
	}

	Material::~Material()
	{
		Logger::Log("Material", "Destructor called");
		for (size_t i = 0; i < mParameters.size(); ++i)
		{
			delete mParameters[i];
		}
	}

	void Material::Use() const
	{
		for (size_t i = 0; i < mParameters.size(); ++i)
		{
			mParameters[i]->Bind(mShader.get());
		}
		mShader.get()->UseShader();
	}

	void Material::AddParameter(IMaterialParameter *parameter)
	{
		mParameters.push_back(parameter);
	}

	Shader *Material::GetShader() const
	{
		return mShader.get();
	}
}
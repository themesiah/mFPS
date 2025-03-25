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
	}

	void Material::Use() const
	{
		for (size_t i = 0; i < mParameters.size(); ++i)
		{
			mParameters[i]->Bind(mShader.get());
		}
		mShader.get()->UseShader();
	}

	void Material::AddParameter(std::shared_ptr<IMaterialParameter> parameter)
	{
		mParameters.push_back(parameter);
	}

	Shader *Material::GetShader() const
	{
		return mShader.get();
	}
}
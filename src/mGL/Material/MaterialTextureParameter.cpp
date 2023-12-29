#include "MaterialTextureParameter.h"
#include "../Texture.h"
#include "../Shader.h"

#include <iostream>

namespace mGL
{
	MaterialTextureParameter::MaterialTextureParameter() : mTextureType(TextureType::Albedo), mTexture(nullptr){}
	MaterialTextureParameter::MaterialTextureParameter(TextureType texType) : mTextureType(texType), mTexture(nullptr){}
	MaterialTextureParameter::MaterialTextureParameter(TextureType texType, Texture* tex) : mTextureType(texType), mTexture(tex){}

	MaterialTextureParameter::MaterialTextureParameter(const MaterialTextureParameter& mtp)
	{
		mTextureType = mtp.mTextureType;
		mTexture = new Texture(*mtp.mTexture);
	}

	MaterialTextureParameter& MaterialTextureParameter::operator=(const MaterialTextureParameter& mtp)
	{
		mTextureType = mtp.mTextureType;
		delete mTexture;
		mTexture = new Texture(*mtp.mTexture);
		return *this;
	}

	MaterialTextureParameter::~MaterialTextureParameter()
	{
		std::cout << "~MaterialTextureParameter called" << std::endl;
		delete mTexture;
	}

	void MaterialTextureParameter::Bind(Shader* shader) const
	{
		switch (mTextureType)
		{
		case TextureType::Albedo:
			shader->SetUniform1i("albedo", 0);
			glActiveTexture(GL_TEXTURE0);
			break;
		case TextureType::Normal:
			shader->SetUniform1i("normal", 1);
			glActiveTexture(GL_TEXTURE1);
			break;
		}
		shader->SetUniform1i("use_albedo_texture", true);
		mTexture->Use();
	}
}
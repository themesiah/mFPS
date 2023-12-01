#include "MaterialTextureParameter.h"
#include "Texture.h"
#include "Shader.h"

namespace mGL
{
	MaterialTextureParameter::MaterialTextureParameter() : mTextureType(TextureType::Albedo), mTexture(nullptr){}
	MaterialTextureParameter::MaterialTextureParameter(TextureType texType) : mTextureType(texType), mTexture(nullptr){}
	MaterialTextureParameter::MaterialTextureParameter(TextureType texType, Texture* tex) : mTextureType(texType), mTexture(tex){}
	MaterialTextureParameter::~MaterialTextureParameter()
	{
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

		mTexture->Use();
	}
}
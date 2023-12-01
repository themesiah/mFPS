#include "Texture.h"
#include "stb_image.h"

namespace mGL
{
	Texture::Texture() : mData(nullptr), mWidth(0), mHeight(0), mChannels(0)
	{
		stbi_set_flip_vertically_on_load(true);
	}

	Texture::Texture(const std::string& path) : Texture()
	{
		Load(path);
	}

	Texture::~Texture()
	{
	}

	void Texture::Load(const std::string& path)
	{
		const std::string& fullPath = "Data/Texture/" + path;
		mData = stbi_load(fullPath.c_str(), &mWidth, &mHeight, &mChannels, 0);
		if (mData) {
			glGenTextures(1, &mTextureId);
			glBindTexture(GL_TEXTURE_2D, mTextureId);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, mWidth, mHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, mData);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		stbi_image_free(mData);
	}

	void Texture::Use() const
	{
		glBindTexture(GL_TEXTURE_2D, mTextureId);
	}
}
#include "Texture.h"
#include "stb_image.h"

#include "Logger.h"

namespace mGL
{
	Texture::Texture() : mData(nullptr), mWidth(0), mHeight(0), mChannels(0)
	{
		stbi_set_flip_vertically_on_load(true);
	}

	Texture::Texture(const std::string &path) : Texture()
	{
		Load(path);
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &mTextureId);
	}

	void Texture::Load(const std::string &path)
	{
		const std::string &fullPath = "Data/Texture/" + path;
		Logger::Log("Texture", "Loading texture on path " + fullPath);
		mData = stbi_load(fullPath.c_str(), &mWidth, &mHeight, &mChannels, 0);
		if (mData)
		{
			glGenTextures(1, &mTextureId);
			glBindTexture(GL_TEXTURE_2D, mTextureId);
			GLint format = GL_R;
			if (mChannels == 3)
			{
				format = GL_RGB;
			}
			else if (mChannels == 4)
			{
				format = GL_RGBA;
			}
			glTexImage2D(GL_TEXTURE_2D, 0, format, mWidth, mHeight, 0, format, GL_UNSIGNED_BYTE, mData);
			glGenerateMipmap(GL_TEXTURE_2D);
			Logger::Log("Texture", "Texture loaded");
		}
		stbi_image_free(mData);
	}

	void Texture::Use() const
	{
		glBindTexture(GL_TEXTURE_2D, mTextureId);
	}
}
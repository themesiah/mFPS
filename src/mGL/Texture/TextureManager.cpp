#include "TextureManager.h"

#include "mBase/Logger.h"

namespace mGL
{
	TextureManager::TextureManager() {}

	TextureManager::~TextureManager()
	{
		Logger::Log("Texture Manager", "Destroying " + std::to_string(m_ResourcesVector.size()) + " textures...");
		Destroy();
		Logger::Log("Texture Manager", "Done");
	}

	TextureManager& TextureManager::GetInstance()
	{
		static TextureManager instance;
		return instance;
	}
}
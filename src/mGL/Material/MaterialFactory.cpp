#include "MaterialFactory.h"

#include <fstream>
#include <memory>

#include "Material.h"
#include "MaterialColorParameter.h"
#include "MaterialTextureParameter.h"
#include "../Texture/Texture.h"
#include "../Texture/TextureManager.h"
#include "Logger.h"
#include "StringUtils.h"

namespace mGL
{
	std::unordered_map<std::string, std::shared_ptr<Material>> MaterialFactory::LoadMaterials(const std::string &path)
	{
		std::unordered_map<std::string, std::shared_ptr<Material>> map = std::unordered_map<std::string, std::shared_ptr<Material>>();
		std::string fullPath = "Data/Material/" + path;
		Logger::Log("Mesh Factory", "Trying to open material file on path " + fullPath);
		std::ifstream file = std::ifstream(fullPath);
		if (!file.is_open())
		{
			Logger::Warning("Mesh Factory", "File not found");
			return map;
		}
		Logger::Log("Mesh Factory", "File opened");
		std::string line;
		std::shared_ptr<Material> currentMaterial = nullptr;
		while (std::getline(file, line))
		{
			if (line.substr(0, 1) == "#")
				continue;
			std::string firstToken = mBase::Strings::FirstToken(line);
			if (firstToken == "newmtl") // Create new material
			{
				Shader *shader = new Shader();
				shader->Init("VertexUberShader.gls", "PixelUberShader.gls");
				currentMaterial = std::shared_ptr<Material>(new Material(shader));
				std::string matName = mBase::Strings::Tail(line);
				map[matName] = currentMaterial;
			}
			else if (firstToken == "Kd") // Diffuse color
			{
				if (currentMaterial == nullptr)
					continue;
				std::vector<std::string> splitted;
				mBase::Strings::Split(mBase::Strings::Tail(line), splitted, " ");
				float r = std::stof(splitted[0]);
				float g = std::stof(splitted[1]);
				float b = std::stof(splitted[2]);
				currentMaterial->AddParameter(std::make_shared<MaterialColorParameter>(r, g, b, 1.0f));
			}
			else if (firstToken == "map_Kd") // Diffuse texture
			{
				if (currentMaterial == nullptr)
					continue;
				std::shared_ptr<Texture> tex;
				std::string texPath = mBase::Strings::Tail(line);
				if (TextureManager::GetInstance().Exist(texPath))
				{
					tex = TextureManager::GetInstance()(texPath);
				}
				else
				{
					tex = std::make_shared<Texture>(texPath);
					TextureManager::GetInstance().Add(texPath, tex);
				}
				currentMaterial->AddParameter(std::make_shared<MaterialTextureParameter>(TextureType::Albedo, tex));
			}
		}
		file.close();
		return map;
	}
}
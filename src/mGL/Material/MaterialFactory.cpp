#include "MaterialFactory.h"

#include <fstream>

#include "Material.h"
#include "MaterialColorParameter.h"
#include "MaterialTextureParameter.h"
#include "../Texture.h"
#include "mBase/Logger.h"
#include "mBase/StringUtils.h"

namespace mGL
{
	std::unordered_map<std::string, std::shared_ptr<Material>> MaterialFactory::LoadMaterials(const std::string& path)
	{
		std::unordered_map<std::string, std::shared_ptr<Material>> map = std::unordered_map<std::string, std::shared_ptr<Material>>();
		std::string fullPath = "Data/Material/" + path;
		Logger::Log("Mesh Factory", "Trying to open material file on path " + fullPath);
		std::ifstream file = std::ifstream(fullPath);
		if (!file.is_open())
		{
			Logger::Log("Mesh Factory", "File not found");
			return map;
		}
		Logger::Log("Mesh Factory", "File opened");
		std::string line;
		std::shared_ptr<Material> currentMaterial = nullptr;
		while (std::getline(file, line))
		{
			if (line.substr(0, 1) == "#") continue;
			std::string firstToken = mBase::Strings::FirstToken(line);
			if (firstToken == "newmtl") // Create new material
			{
				Shader* shader = new Shader();
				shader->Init("VertexUberShader.gls", "PixelUberShader.gls");
				currentMaterial = std::shared_ptr<Material>(new Material(shader));
				std::string matName = mBase::Strings::Tail(line);
				map[matName] = currentMaterial;
			}
			else if (firstToken == "Kd") // Diffuse color
			{
				if (currentMaterial == nullptr) continue;
				std::vector<std::string> splitted;
				mBase::Strings::Split(mBase::Strings::Tail(line), splitted, " ");
				float r = std::stof(splitted[0]);
				float g = std::stof(splitted[1]);
				float b = std::stof(splitted[2]);
				currentMaterial->AddParameter(new MaterialColorParameter(r, g, b, 1.0f));
			}
			else if (firstToken == "map_Kd") // Diffuse texture
			{
				if (currentMaterial == nullptr) continue;
				currentMaterial->AddParameter(new MaterialTextureParameter(TextureType::Albedo, new Texture(mBase::Strings::Tail(line))));
			}
		}
		file.close();
		return map;
	}
}
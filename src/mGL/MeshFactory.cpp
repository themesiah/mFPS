#include <vector>
#include <iostream>
#include <fstream>
#include <unordered_map>

#include "glm/glm.hpp"
#include "Renderable/RenderableObject.h"
#include "Renderable/RenderableModel.h"
#include "Mesh.h"
#include "MeshFactory.h"
#include "mBase/StringUtils.h"
#include "Vertex.h"
#include "Material/MaterialFactory.h"
#include "mBase/Logger.h"

namespace mGL
{
	RenderableObject* MeshFactory::LoadObj(const std::string& path)
	{
		if (path.substr(path.size() - 4, 4) != ".obj")
			return nullptr;


		std::string fullPath = "Data/Meshes/" + path;
		Logger::Log("Mesh Factory", "Trying to open obj file on path " + fullPath);
		std::ifstream file = std::ifstream(fullPath);
		if (!file.is_open())
		{
			Logger::Warning("Mesh Factory", "File not found");
			return nullptr;
		}
		Logger::Log("Mesh Factory", "File opened");

		std::string line;
		std::vector<glm::vec3> positions;
		std::vector<glm::vec2> uvs;
		std::vector<glm::vec3> normals;
		std::vector<Vertex> vertexs;
		std::vector<unsigned short> indices;
		std::unordered_map<Vertex, unsigned short> indicesMap = std::unordered_map<Vertex, unsigned short>();
		std::unordered_map<std::string, std::shared_ptr<Material>> materialMap;
		std::shared_ptr<Material> currentMaterial = nullptr;
		std::vector<Mesh*> meshes = std::vector<Mesh*>();
		unsigned short indexCount = 0;
		while (std::getline(file, line))
		{
			if (line.substr(0,1) == "#") continue;
			std::string firstToken = mBase::Strings::FirstToken(line);
			if (firstToken == "mtllib")
			{
				materialMap = MaterialFactory::LoadMaterials(mBase::Strings::Tail(line));
			}
			else if (firstToken == "v")
			{
				std::vector<std::string> splitted;
				mBase::Strings::Split(mBase::Strings::Tail(line), splitted, " ");
				glm::vec3 position = glm::vec3(std::stof(splitted[0]), std::stof(splitted[1]), std::stof(splitted[2]));
				positions.push_back(position);
			}
			else if (firstToken == "vn")
			{
				std::vector<std::string> splitted;
				mBase::Strings::Split(mBase::Strings::Tail(line), splitted, " ");
				glm::vec3 normal = glm::vec3(std::stof(splitted[0]), std::stof(splitted[1]), std::stof(splitted[2]));
				normals.push_back(normal);
			}
			else if (firstToken == "vt")
			{
				std::vector<std::string> splitted;
				mBase::Strings::Split(mBase::Strings::Tail(line), splitted, " ");
				glm::vec2 uv = glm::vec2(std::stof(splitted[0]), std::stof(splitted[1]));
				uvs.push_back(uv);
			}
			else if (firstToken == "usemtl")
			{
				if (currentMaterial != nullptr) {
					Mesh* mesh = new Mesh(vertexs, indices);
					mesh->SetMaterial(currentMaterial);
					meshes.push_back(mesh);
				}

				indicesMap.clear();
				indices.clear();
				vertexs.clear();
				indexCount = 0;
				currentMaterial = nullptr;

				std::string matName = mBase::Strings::Tail(line);
				if (materialMap.find(matName) != materialMap.end())
				{
					currentMaterial = materialMap[matName];
				}
			}
			else if (firstToken == "f")
			{
				std::vector<std::string> faces;
				mBase::Strings::Split(mBase::Strings::Tail(line), faces, " ");
				unsigned int firstIndex;
				for (int i = 0; i < faces.size(); ++i)
				{
					std::vector<std::string> splitted;
					mBase::Strings::Split(faces[i], splitted, "/");
					unsigned short positionIndex = std::stoi(splitted[0]);
					unsigned short uvIndex = std::stoi(splitted[1]);

					Vertex v = Vertex();
					v.Position = positions[positionIndex - 1];
					v.Uvs = uvs[uvIndex - 1];
					if (splitted.size() > 2) {
						unsigned short normalIndex = std::stoi(splitted[2]);
						v.Normal = normals[normalIndex - 1];
					}
					if (indicesMap.find(v) != indicesMap.end())
					{
						// Exists!
						indices.push_back(indicesMap[v]);
						if (faces.size() == 4 && i == 0)
							firstIndex = indicesMap[v];
						if (faces.size() == 4 && i == 2)
							indices.push_back(indicesMap[v]);
						if (faces.size() == 4 && i == 3)
							indices.push_back(firstIndex);
					}
					else {
						// Not exists. Create new one
						vertexs.push_back(v);
						indicesMap[v] = indexCount;
						indices.push_back(indexCount);
						if (faces.size() == 4 && i == 0)
							firstIndex = indicesMap[v];
						if (faces.size() == 4 && i == 2)
							indices.push_back(indicesMap[v]);
						if (faces.size() == 4 && i == 3)
							indices.push_back(firstIndex);
						indexCount++;
					}
				}
			}
		}
		if (currentMaterial != nullptr) { // There is no indicator of EOF, so on the end we use all data for the last material configured
			Mesh* mesh = new Mesh(vertexs, indices);
			mesh->SetMaterial(currentMaterial);
			meshes.push_back(mesh);
		}
		file.close();
		RenderableObject* ro = new RenderableModel(meshes);
		return ro;
	}
}
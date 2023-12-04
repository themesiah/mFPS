#include <vector>
#include <iostream>
#include <fstream>
#include <unordered_map>

#include "glm/glm.hpp"
#include "Mesh.h"
#include "MeshFactory.h"
#include "mBase/StringUtils.h"
#include "Vertex.h"

namespace mGL
{
	Mesh MeshFactory::LoadMesh(const std::string& path)
	{
		if (path.substr(path.size() - 4, 4) != ".obj")
			return Mesh();


		std::string fullPath = "Data/Meshes/" + path;
		Log("Trying to open file on path " + fullPath);
		std::ifstream file = std::ifstream(fullPath);
		if (!file.is_open())
		{
			Log("File not found");
			return Mesh();
		}
		Log("File opened");

		std::string line;
		std::vector<glm::vec3> positions;
		std::vector<glm::vec2> uvs;
		std::vector<glm::vec3> normals;
		std::vector<Vertex> vertexs;
		std::vector<unsigned short> indices;
		std::unordered_map<Vertex, unsigned short> indicesMap = std::unordered_map<Vertex, unsigned short>();
		unsigned short indexCount = 0;
		while (std::getline(file, line))
		{
			//Log(line);
			std::string firstToken = mBase::Strings::FirstToken(line);
			if (firstToken == "v")
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
			else if (firstToken == "f")
			{
				std::vector<std::string> faces;
				mBase::Strings::Split(mBase::Strings::Tail(line), faces, " ");
				for (int i = 0; i < faces.size(); ++i)
				{
					std::vector<std::string> splitted;
					mBase::Strings::Split(faces[i], splitted, "/");
					unsigned short positionIndex = std::stoi(splitted[0]);
					unsigned short uvIndex = std::stoi(splitted[1]);
					unsigned short normalIndex = std::stoi(splitted[2]);
					Vertex v = Vertex();
					v.Position = positions[positionIndex - 1];
					v.Uvs = uvs[uvIndex - 1];
					if (indicesMap.find(v) != indicesMap.end())
					{
						// Exists!
						indices.push_back(indicesMap[v]);
					}
					else {
						// Not exists. Create new one
						vertexs.push_back(v);
						indicesMap[v] = indexCount;
						indices.push_back(indexCount);
						indexCount++;
					}
				}
			}
		}

		Mesh mesh = Mesh(vertexs, indices);
		return mesh;
	}

	void MeshFactory::Log(const std::string& logMessage)
	{
		std::cout << logMessage << std::endl;
	}
}
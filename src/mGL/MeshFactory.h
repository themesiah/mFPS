#ifndef MGL_MESH_FACTORY
#define MGL_MESH_FACTORY

#include <string>
#include <unordered_map>
#include <vector>
#include <memory>

namespace tinyxml2
{
	class XMLElement;
}

namespace mGL
{
	class RenderableObject;
	class Material;
	class Mesh;
	class MeshFactory
	{
	public:
		static std::shared_ptr<RenderableObject> LoadObj(tinyxml2::XMLElement *element);
		static std::shared_ptr<RenderableObject> LoadObj(const std::string &path);

	private:
		static std::vector<Mesh *> GetMeshes(const std::string &path);
	};
}

#endif

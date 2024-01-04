#ifndef MGL_MESH_FACTORY
#define MGL_MESH_FACTORY

#include <string>
#include <unordered_map>

namespace tinyxml2
{
	class XMLElement;
}

namespace mGL
{
	class RenderableObject;
	class Material;
	class Mesh;
	static class MeshFactory
	{
	public:
		static RenderableObject* LoadObj(tinyxml2::XMLElement* element);
		static RenderableObject* LoadObj(const std::string& path);
	private:
		static std::vector<Mesh*> GetMeshes(const std::string& path);
	};
}

#endif

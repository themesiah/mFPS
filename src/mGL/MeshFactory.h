#ifndef MGL_MESH_FACTORY
#define MGL_MESH_FACTORY

#include <string>
#include <unordered_map>

namespace mGL
{
	class RenderableObject;
	class Material;
	static class MeshFactory
	{
	public:
		static RenderableObject* LoadObj(const std::string& path);
	};
}

#endif

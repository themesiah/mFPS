#ifndef MGL_MESH_FACTORY
#define MGL_MESH_FACTORY

#include <string>

namespace mGL
{
	class Mesh;
	class Material;
	static class MeshFactory
	{
	public:
		static Mesh LoadMesh(const std::string& path);
		static Material* LoadMaterial(const std::string& path);
		static void Log(const std::string& path);
	};
}

#endif

#ifndef MGL_MATERIALFACTORY
#define MGL_MATERIALFACTORY

#include <string>
#include <unordered_map>
#include <memory>

namespace mGL
{
	class Material;
	static class MaterialFactory
	{
	public:
		static std::unordered_map<std::string, std::shared_ptr<Material>> LoadMaterials(const std::string& path);
	};
}

#endif
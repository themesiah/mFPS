#ifndef MGL_VERTEX
#define MGL_VERTEX

#include <functional>
#include "glm/glm.hpp"

namespace mGL
{
	struct Vertex
	{
		glm::vec3 Position;
		glm::vec2 Uvs;
		glm::vec3 Rgb;

		bool operator==(const Vertex& other) const
		{
			return Position == other.Position && Uvs == other.Uvs && Rgb == other.Rgb;
		}
	};
}

namespace std
{
	template <>
	struct hash<mGL::Vertex>
	{
		std::size_t operator()(const mGL::Vertex& v) const
		{
			static std::hash<float> Hash;
			std::size_t res = 17;
			res = res * 31 + Hash(v.Position.x);
			res = res * 31 + Hash(v.Position.y);
			res = res * 31 + Hash(v.Position.z);
			res = res * 31 + Hash(v.Uvs.x);
			res = res * 31 + Hash(v.Uvs.y);
			res = res * 31 + Hash(v.Rgb.x);
			res = res * 31 + Hash(v.Rgb.y);
			res = res * 31 + Hash(v.Rgb.z);
			return res;
		}
	};
}

#endif

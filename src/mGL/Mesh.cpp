#include "Mesh.h"

namespace mGL {

	Mesh::Mesh(std::vector<float> vertices)
	{
		SetVertices(vertices);
	}

	void Mesh::SetVertices(std::vector<float> vertices)
	{
		_vertices = vertices;
	}

	void Mesh::Render()
	{
		glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(float), &_vertices[0], GL_STATIC_DRAW);
		// draw points 0-3 from the currently bound VAO with current in-use shader
		glDrawArrays(GL_TRIANGLES, 0, _vertices.size());
	}
}
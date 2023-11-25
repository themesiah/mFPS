#include "Mesh.h"

namespace mGL
{

	Mesh::Mesh(std::vector<float> vertices)
	{
		_usingIndices = false;
		SetVertices(vertices);
	}

	Mesh::Mesh(std::vector<float> vertices, std::vector<int> indices) : Mesh(vertices)
	{
		SetIndices(indices);
	}

	void Mesh::SetVertices(std::vector<float> vertices)
	{
		_vertices = vertices;
	}

	void Mesh::SetIndices(std::vector<int> indices)
	{
		_indices = indices;
		_usingIndices = true;
	}

	void Mesh::Render()
	{
		glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(float), &_vertices[0], GL_STATIC_DRAW);
		// draw points 0-3 from the currently bound VAO with current in-use shader
		if (_usingIndices) {
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(int), &_indices[0], GL_STATIC_DRAW);
			glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0);
		}
		else {
			glDrawArrays(GL_TRIANGLES, 0, _vertices.size());
		}
	}
}
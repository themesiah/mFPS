#include "Mesh.h"

namespace mGL
{

	Mesh::Mesh(std::vector<float> vertices)
	{
		mUsingIndices = false;
		SetVertices(vertices);
	}

	Mesh::Mesh(std::vector<float> vertices, std::vector<int> indices) : Mesh(vertices)
	{
		SetIndices(indices);
	}

	void Mesh::SetVertices(std::vector<float> vertices)
	{
		mVertices = vertices;
	}

	void Mesh::SetIndices(std::vector<int> indices)
	{
		mIndices = indices;
		mUsingIndices = true;
	}

	void Mesh::Render()
	{
		glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(float), &mVertices[0], GL_STATIC_DRAW);
		// draw points 0-3 from the currently bound VAO with current in-use shader
		if (mUsingIndices) {
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndices.size() * sizeof(int), &mIndices[0], GL_STATIC_DRAW);
			glDrawElements(GL_TRIANGLES, mIndices.size(), GL_UNSIGNED_INT, 0);
		}
		else {
			glDrawArrays(GL_TRIANGLES, 0, mVertices.size());
		}
	}
}
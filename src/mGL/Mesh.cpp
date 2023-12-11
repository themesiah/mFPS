#include "Mesh.h"
#include "Vertex.h"
#include "Material.h"

namespace mGL
{	
	Mesh::Mesh() : mIndicesSize(0), mVAO(0), mEBO(0), mVBO(0), mMaterial(nullptr) {}

	Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned short> indices) : mMaterial(nullptr)
	{
		mIndicesSize = indices.size();
		SetupMesh(vertices, indices);
	}

	Mesh::Mesh(const Mesh& m)
	{
		mVAO = m.mVAO;
		mVBO = m.mVBO;
		mEBO = m.mEBO;
		mIndicesSize = m.mIndicesSize;
		mMaterial = m.mMaterial;
	}

	Mesh& Mesh::operator=(const Mesh& m)
	{
		mVAO = m.mVAO;
		mVBO = m.mVBO;
		mEBO = m.mEBO;
		mIndicesSize = m.mIndicesSize;
		mMaterial = m.mMaterial;

		return *this;
	}

	Mesh::~Mesh()
	{
		//glDeleteVertexArrays(1, &mVAO);
		//glDeleteBuffers(1, &mVBO);
		//glDeleteBuffers(1, &mEBO);
	}

	void Mesh::SetupMesh(std::vector<Vertex> vertices, std::vector<unsigned short> indices)
	{
		glGenVertexArrays(1, &mVAO);
		glGenBuffers(1, &mVBO);
		glGenBuffers(1, &mEBO);

		glBindVertexArray(mVAO);
		glBindBuffer(GL_ARRAY_BUFFER, mVBO); // position vertex buffer object
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO); // position element buffer object
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned short), &indices[0], GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0); // Vertex position
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float))); // UVs

		glBindVertexArray(0);
	}

	void Mesh::SetMaterial(std::shared_ptr<Material> material)
	{
		mMaterial = material;
	}

	void Mesh::Render(glm::mat4 *matrix, const glm::mat4& projection, const glm::mat4& view) const
	{
		if (mVAO != 0) {
			mMaterial.get()->Use();
			mMaterial.get()->GetShader()->SetUniformMatrix4fv("transform", *matrix);
			mMaterial.get()->GetShader()->SetUniformMatrix4fv("projection", projection);
			mMaterial.get()->GetShader()->SetUniformMatrix4fv("view", view);
			glBindVertexArray(mVAO);
			glDrawElements(GL_TRIANGLES, mIndicesSize, GL_UNSIGNED_SHORT, 0);
			glBindVertexArray(0);
		}
	}
}
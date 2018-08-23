#include "Mesh.h"


Mesh::Mesh(VertexArray* vertexArray, IndexBuffer* indexBuffer, MaterialInstance* materialInstance)
	:m_VertexArray(vertexArray), m_IndexBuffer(indexBuffer), m_MaterialInstance(materialInstance)
{
}

Mesh::~Mesh()
{
	delete m_VertexArray;
	delete m_IndexBuffer;
	delete m_MaterialInstance;
}

void Mesh::Render(Renderer3D& renderer)
{
	m_MaterialInstance->Bind();

	m_VertexArray->Bind();
	m_IndexBuffer->Bind();
	m_VertexArray->Draw(m_IndexBuffer->getCount());
	m_IndexBuffer->Unbind();
	m_VertexArray->Unbind();

	m_MaterialInstance->Unbind();

}

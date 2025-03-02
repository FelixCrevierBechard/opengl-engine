#include "GameObject.h"

GameObject::GameObject(const char* name, const float* vertices, const float* uv, unsigned int uvCount, const unsigned int* indices)
	: Ebo(indices, uvCount)
{
	Mesh.vertices = vertices;
	Mesh.uv = uv;
	Mesh.indices = indices;
	Name = name;

	Vao.AddBuffer(Vbo, vertices, uv);
	Vbo.Unbind();
	Vao.Unbind();
}

#include "GameObject.h"

GameObject::GameObject(const char* name, const float* vertices, const float* uv, const unsigned int* indices)
{
	Mesh.vertices = vertices;
	Mesh.uv = uv;
	Mesh.indices = indices;
	Name = name;

	Vao.AddBuffer(Vbo, Mesh.vertices, Mesh.uv);
	Vbo.Unbind();
}

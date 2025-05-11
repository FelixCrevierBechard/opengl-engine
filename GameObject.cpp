#include "GameObject.h"
	
GameObject::GameObject(const char* name, const std::vector<float>& vertices, const std::vector<float>& uv, const std::vector<unsigned int>& indices, const Texture& texture) : name(name), mesh(Mesh(vertices, uv, indices, texture)) {}

GameObject::~GameObject() {  }

Mesh::Mesh(const std::vector<float>& vertices, const std::vector<float>& uv, const std::vector<unsigned int>& indices, const Texture& texture) : texture(texture), vertices(vertices), uv(uv), indices(indices) {}

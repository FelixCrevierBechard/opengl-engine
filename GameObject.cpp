#include "GameObject.h"

GameObject::GameObject(const char* name, const VAO& vao, const EBO& ebo, const Texture& texture = Texture("Default.png", GL_RGBA)) : _Name(name), _Vao(vao), _Ebo(ebo), _Text(texture) {}

GameObject::~GameObject() {  }

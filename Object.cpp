#include "Object.h"
	
Object::Object(const char* name, const std::vector<float>& vertices, const std::vector<float>& uv, const std::vector<unsigned int>& indices, const Texture& texture) : name(name) { 
	mesh = { vertices, uv, indices }; 
	material = { texture };
}

Object::~Object() {  }
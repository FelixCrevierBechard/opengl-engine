#pragma once

#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

#include <glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<vector>

enum Space { Self, Global };

struct Transform
{
	glm::mat4 model = glm::mat4(1.0f);
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	void Move(glm::vec3 position) {
		model = glm::translate(model, position);
		UpdateValues(rotation);
	}
	void Translate(glm::vec3 translation) {//TODO: SPACE.SELF/relativeTo
		model = glm::translate(model, position + translation);
		UpdateValues(rotation);
	}
	void Scale(glm::vec3 scale) {
		model = glm::scale(model, scale);
		UpdateValues(rotation);
	}
	void Rotate(glm::vec3 rotationRad) {
		model = glm::rotate(model, glm::radians(rotationRad.x), { 1, 0, 0 });
		model = glm::rotate(model, glm::radians(rotationRad.y), { 0, 1, 0 });
		model = glm::rotate(model, glm::radians(rotationRad.z), { 0, 0, 1 });

		UpdateValues(rotationRad);
	}
	void UpdateValues(glm::vec3 newRotation) {
		position = model[3];

		scale.x = glm::length(glm::vec3(model[0]));
		scale.y = glm::length(glm::vec3(model[1]));
		scale.z = glm::length(glm::vec3(model[2]));

		rotation = newRotation;
	}
};

struct Mesh
{
	const float* vertices;	
	const float* uv;
	const unsigned int* indices;
};

class GameObject
{
public:
	const char* Name;
	Transform Transform;
	Mesh Mesh;
	VAO Vao;
	VBO Vbo;
	EBO Ebo;

	GameObject(const char* name, const float* vertices, const float* uv, const unsigned int* indices);
};


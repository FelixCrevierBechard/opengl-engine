#pragma once

#include "Texture.h"

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<vector>

struct Transform
{
public:
	glm::vec3 Positon = { 0, 0, 0 };
	glm::vec3 Rotation = { 0, 0, 0 };
	glm::vec3 Scale = { 1, 1, 1 };
};
class Mesh {
public:
	Texture texture = Texture("Default.png", GL_RGBA);

	std::vector<float> vertices;
	std::vector<float> uv;
	std::vector<unsigned int> indices;

	Mesh(const std::vector<float>& vertices, const std::vector<float>& uv, const std::vector<unsigned int>& indices, const Texture& texture = Texture("Default.png", GL_RGBA));
	~Mesh() {}
};
class GameObject
{
public:
	const char* name;
	Mesh mesh;
	Transform transform;

	GameObject(const char* name, const std::vector<float>& vertices, const std::vector<float>& uv, const std::vector<unsigned int>& indices, const Texture& texture = Texture("Default.png", GL_RGBA));
	~GameObject();

	static std::vector<float> MergeVertices(std::vector<GameObject>& objects)
	{
		std::vector<float> vertices;
		for (const auto& obj : objects)
		{
			for (int i = 0; i < obj.mesh.vertices.size(); ++i)
			{
				if(i % 3 == 0)
					vertices.push_back(obj.mesh.vertices[i] + obj.transform.Positon.x);
				else if (i % 3 == 1)
					vertices.push_back(obj.mesh.vertices[i] + obj.transform.Positon.y);
				else
					vertices.push_back(obj.mesh.vertices[i] + obj.transform.Positon.z);
			}
		}
		return vertices;
	}
	static std::vector<float> MergeUV(std::vector<GameObject>& objects)
	{
		std::vector<float> uv;
		for (const auto& obj : objects)
		{
			uv.insert(uv.end(), obj.mesh.uv.begin(), obj.mesh.uv.end());
		}
		return uv;
	}
	static std::vector<unsigned int> MergeIndices(const std::vector<GameObject>& objects)
	{
		std::vector<unsigned int> indices;
		unsigned int offset = 0;
		for (const auto& obj : objects)
		{
			for (int i = 0; i < obj.mesh.indices.size(); ++i)
			{
				indices.push_back(obj.mesh.indices[i] + offset);
			}
			offset += obj.mesh.vertices.size() / 3;
		}
		return indices;
	}
};
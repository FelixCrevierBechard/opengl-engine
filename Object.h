#pragma once

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<vector>

#include"Texture.h"
#include"Renderer.h"

struct Transform
{
public:
	glm::vec3 Positon = { 0, 0, 0 };
	glm::vec3 Rotation = { 0, 0, 0 };
	glm::vec3 Scale = { 1, 1, 1 };
};
struct Mesh {
public:
	std::vector<float> vertices;
	std::vector<float> uv;
	std::vector<unsigned int> indices;
};
struct Material
{
	Texture texture = Texture("Default.png", GL_RGBA);
};
class Object
{
public:
	const char* name;
	Mesh mesh;
	Transform transform;
	Material material;

	Object(const char* name, const std::vector<float>& vertices, const std::vector<float>& uv, const std::vector<unsigned int>& indices, const Texture& texture = Texture("Default.png", GL_RGBA));
	~Object();

	RendererObject parse() { return RendererObject(mesh.indices, mesh.vertices, mesh.uv, material.texture); }

	//STATIC METHODS FOR MERGING OBJECTS
	static Object merge_objects(const std::vector<Object>& objects, const char* name = "MergedObject")
	{
		std::vector<float> vertices = merge_vertices(objects);
		std::vector<float> uv = MergeUV(objects);
		std::vector<unsigned int> indices = MergeIndices(objects);
		return Object(name, vertices, uv, indices, objects[0].material.texture);
	}
	static Object merge_objects(const std::vector<Object>& objects, const Texture& texture, const char* name = "MergedObject")
	{
		std::vector<float> vertices = merge_vertices(objects);
		std::vector<float> uv = MergeUV(objects);
		std::vector<unsigned int> indices = MergeIndices(objects);
		return Object(name, vertices, uv, indices, texture);
	}
	static std::vector<float> merge_vertices(const std::vector<Object>& objects)
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
	static std::vector<float> MergeUV(const std::vector<Object>& objects)
	{
		std::vector<float> uv;
		for (const auto& obj : objects)
		{
			uv.insert(uv.end(), obj.mesh.uv.begin(), obj.mesh.uv.end());
		}
		return uv;
	}
	static std::vector<unsigned int> MergeIndices(const std::vector<Object>& objects)
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
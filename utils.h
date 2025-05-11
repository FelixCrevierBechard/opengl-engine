#pragma once

template <typename T>
class Data
{
public:
	const T* data;
	const unsigned long long size;

	data<T>(const T* data, const unsigned long long size) : data(data), size(size) {}
	~data<T>() {}
};

static Mesh Merge(std::vector<Mesh>) {
	VAO vao;
}
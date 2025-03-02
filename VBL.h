#pragma once

#include<vector>
#include<glad/glad.h>
#include<stdexcept>
#include<glm/glm.hpp>

struct VBE {
	unsigned int type;
	unsigned int count;
	unsigned char normalized;

	static unsigned int GetTypeSize(unsigned int t) {
		switch (t)
		{
		case GL_FLOAT:
			return 4;
		case GL_UNSIGNED_INT:
			return 4;
		case GL_UNSIGNED_BYTE:
			return 1;
		default:
			break;
		}
	}
};

class VBL {
private:
	std::vector<VBE> m_elements;
	unsigned int m_stride;
public:
	VBL()
		:m_stride(0) {}

	template<typename T>
	void Push(unsigned int count) {
		std::runtime_error(false);
	}

	template<>
	void Push<float>(unsigned int count) {
		m_elements.push_back({GL_FLOAT, count, GL_FALSE });
		m_stride += VBE::GetTypeSize(GL_FLOAT) * count;
	}

	template<>
	void Push<unsigned int>(unsigned int count) {
		m_elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		m_stride += VBE::GetTypeSize(GL_UNSIGNED_INT) * count;
	}

	template<>
	void Push<unsigned char>(unsigned int count) {
		m_elements.push_back({ GL_UNSIGNED_BYTE, count, GL_FALSE });
		m_stride += VBE::GetTypeSize(GL_UNSIGNED_BYTE) * count;
	}

	inline unsigned int GetStride() const { return m_stride; }
	inline const std::vector<VBE> GetElements() const { return m_elements; }
};


#pragma once

#include <glad/glad.h>
#include<iostream>

#include"stb_image.h"

class Texture
{
public:
	unsigned int id;

	Texture(const char* fileDir, GLenum imageType = GL_RGB);
	void setup_texture(const char* fileDir, GLenum imageType = GL_RGB);
	void bind();
	void unbind();
};


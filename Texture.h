#pragma once

#include <glad/glad.h>
#include<iostream>

#include"stb_image.h"

class Texture
{
public:
	unsigned int ID;

	Texture(const char* fileDir, GLenum imageType = GL_RGB);
	void SetupTexture(const char* fileDir, GLenum imageType = GL_RGB);
	void Bind();
};


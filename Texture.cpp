#include "Texture.h"

#include "Renderer.h"

Texture::Texture(const char* fileDirectory, GLenum imageType) {
    setup_texture(fileDirectory, imageType);
}

void Texture::setup_texture(const char* fileDirectory, GLenum imageType) {
    GLCall(glGenTextures(1, &id));
    GLCall(glBindTexture(GL_TEXTURE_2D, id)); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));	// set texture wrapping to GL_REPEAT (default wrapping method)
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
    // set texture filtering parameters
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    // load image, create texture and generate mipmaps
    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
    int width, height, nrChannels;
    unsigned char* data = stbi_load(fileDirectory, &width, &height, &nrChannels, 0);
    if (data)
    {
        switch (imageType)
        {
        case GL_RGBA:
            GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data));
            break;
        case GL_RGB:
            GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data));
            break;
        default:
            GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data));
            break;
        }
        GLCall(glGenerateMipmap(GL_TEXTURE_2D));
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
}

void Texture::bind() {
    glBindTexture(GL_TEXTURE_2D, id);
}
void Texture::unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}
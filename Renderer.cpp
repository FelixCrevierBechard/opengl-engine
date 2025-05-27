
#include "Renderer.h"

void GLClearError()
{
	while (glGetError());
}
bool GLLogCall(const char* function, const char* file, int line) {
	while (GLenum error = glGetError()) {
		std::cout << "[OpenGl error] (0x" << std::hex << error << std::dec << "): "
			<< function << " " << file << ":" << line << std::endl;
		return false;
	}
	return true;
}

void Renderer::draw(RendererObject rendererObject, Shader& shader)
{
	shader.use();
	//ebo
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererObject.ebo);
	//vbo
	glBindBuffer(GL_ARRAY_BUFFER, rendererObject.vbos["vert"]);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 12, 0);
	glEnableVertexAttribArray(0);
	//uv
	glBindBuffer(GL_ARRAY_BUFFER, rendererObject.vbos["uv"]);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8, 0);
	glEnableVertexAttribArray(1);
	//texture
	shader.set_int("Texture", 0);
	glActiveTexture(GL_TEXTURE0);
	rendererObject.texture.bind();
	//model
	shader.set_mat4("model", rendererObject.model);
	//draw
	glDrawElements(GL_TRIANGLES, rendererObject.indexCount, GL_UNSIGNED_INT, nullptr);
	//unbind everything
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Renderer::draw(std::vector<RendererObject>& ro, Shader& shader)
{
	for (auto& obj : ro)
		draw(obj, shader);
}

void Renderer::set_currentcamera(Shader& shader, Camera& newCam) const
{
	shader.set_mat4("projection", newCam.get_projection());
	shader.set_mat4("view", newCam.get_view());
}

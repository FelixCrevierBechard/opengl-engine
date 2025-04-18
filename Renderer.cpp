
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

void Renderer::Draw(const VAO& vao, const EBO& ebo, const Shader& shader) const
{
	shader.use();
	vao.Bind();
	ebo.Bind();
	glDrawElements(GL_TRIANGLES, ebo.GetCount(), GL_UNSIGNED_INT, nullptr);
	vao.Unbind();
}

void Renderer::Draw(GameObject& gameObject, Shader& shader) const
{
	shader.use();

	gameObject._Vao.Bind();
	gameObject._Ebo.Bind();

	shader.setInt("Texture1", 0);
	glActiveTexture(GL_TEXTURE0);
	gameObject._Text.Bind();

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, gameObject.Positon);
	model = glm::rotate(model, glm::radians(gameObject.Rotation.x), glm::vec3(1, 0, 0));	
	model = glm::rotate(model, glm::radians(gameObject.Rotation.y), glm::vec3(0, 1, 0));
	model = glm::rotate(model, glm::radians(gameObject.Rotation.z), glm::vec3(0, 0, 1));
	model = glm::scale(model, gameObject.Scale);	
	shader.setMat4("model", model);

	glDrawElements(GL_TRIANGLES, gameObject._Ebo.GetCount(), GL_UNSIGNED_INT, nullptr);

	gameObject._Vao.Unbind();
	gameObject._Text.Unbind();
}

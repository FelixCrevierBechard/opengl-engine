
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

void Renderer::Draw(RendererObject ro, Transform transform, Shader& shader)
{
	shader.use();

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ro.ebo);

	glBindBuffer(GL_ARRAY_BUFFER, ro.vbos["vert"]);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 12, 0);
	glEnableVertexAttribArray(0);
	//uv
	glBindBuffer(GL_ARRAY_BUFFER, ro.vbos["uv"]);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8, 0);
	glEnableVertexAttribArray(1);

	shader.setInt("Texture1", 0);
	glActiveTexture(GL_TEXTURE0);
	ro.texture.Bind();

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, transform.Positon);
	model = glm::rotate(model, glm::radians(transform.Rotation.x), glm::vec3(1, 0, 0));
	model = glm::rotate(model, glm::radians(transform.Rotation.y), glm::vec3(0, 1, 0));
	model = glm::rotate(model, glm::radians(transform.Rotation.z), glm::vec3(0, 0, 1));
	model = glm::scale(model, transform.Scale);
	shader.setMat4("model", model);

	glDrawElements(GL_TRIANGLES, ro.indexCount, GL_UNSIGNED_INT, nullptr);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void Renderer::Draw(std::vector<GameObject> gameObjects, Shader& shader)
{
	for (GameObject obj : gameObjects)
		Draw(RendererObject(obj.mesh.indices, obj.mesh.vertices, obj.mesh.uv, obj.mesh.texture), obj.transform, shader);
}

void Renderer::SetCurrentCamera(Shader& shader, Camera& newCam) const
{
	shader.setMat4("projection", newCam.getProjection());
	shader.setMat4("view", newCam.getView());
}


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

void Renderer::Draw(GameObject& gameObject, Shader& shader)
{
	std::vector<float> temp1;
	std::vector<float> temp2;
	std::vector<unsigned int> temp3;

	temp1.insert(temp1.end(), gameObject.mesh.vertices.begin(), gameObject.mesh.vertices.end());
	temp2.insert(temp2.end(), gameObject.mesh.uv.begin(), gameObject.mesh.uv.end());
	temp3.insert(temp3.end(), gameObject.mesh.indices.begin(), gameObject.mesh.indices.end());

	shader.use();

	//ebo
	unsigned int ebo;
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, gameObject.mesh.indices.size() * 4, gameObject.mesh.indices.data(), GL_STATIC_DRAW);

	//vbos
	unsigned int vert, uv;
	//vertices
	glGenBuffers(1, &vert);
	glBindBuffer(GL_ARRAY_BUFFER, vert);
	glBufferData(GL_ARRAY_BUFFER, gameObject.mesh.vertices.size() * 4, gameObject.mesh.vertices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 12, 0);
	glEnableVertexAttribArray(0);
	//uv
	glGenBuffers(1, &uv);
	glBindBuffer(GL_ARRAY_BUFFER, uv);
	glBufferData(GL_ARRAY_BUFFER, gameObject.mesh.uv.size() * 4, gameObject.mesh.uv.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8, 0);
	glEnableVertexAttribArray(1);

	shader.setInt("Texture1", 0);
	glActiveTexture(GL_TEXTURE0);
	gameObject.mesh.texture.Bind();

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, gameObject.Positon);
	model = glm::rotate(model, glm::radians(gameObject.Rotation.x), glm::vec3(1, 0, 0));
	model = glm::rotate(model, glm::radians(gameObject.Rotation.y), glm::vec3(0, 1, 0));
	model = glm::rotate(model, glm::radians(gameObject.Rotation.z), glm::vec3(0, 0, 1));
	model = glm::scale(model, gameObject.Scale);
	shader.setMat4("model", model);

	glDrawElements(GL_TRIANGLES, gameObject.mesh.indices.size(), GL_UNSIGNED_INT, nullptr);

	glBindTexture(GL_TEXTURE_2D, 0);

	glDeleteBuffers(1, &vert);
	glDeleteBuffers(1, &uv);
	glDeleteBuffers(1, &ebo);
}

void Renderer::Draw(std::vector<GameObject> gameObjects, Shader& shader)
{
	for (GameObject obj : gameObjects)
		Draw(obj, shader);
}

void Renderer::SetCurrentCamera(Shader& shader, Camera& newCam) const
{
	shader.setMat4("projection", newCam.getProjection());
	shader.setMat4("view", newCam.getView());
}

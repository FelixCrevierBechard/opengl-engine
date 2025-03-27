#include<conio.h>
#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>è

#include"Renderer.h"
#include"stb_image.h"
#include"Camera.h"
#include"Texture.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void InitGlfw();
void ProcessInput(GLFWwindow* window, Camera cam);

const int SCREEN_WIDTH = 1600;
const int SCREEN_HEIGHT = 900;

glm::vec3 cameraPos(0.f, 0.f, 5.f);
Camera camera(SCREEN_WIDTH, SCREEN_HEIGHT);

float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

int main() {
	InitGlfw();

	//InitWindow
	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Engine", glfwGetPrimaryMonitor(), NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(window);

	gladLoadGL();

	glfwSetCursorPosCallback(window, mouse_callback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSwapInterval(1); //60 fps so our gpu doesnt explode

	//HadleViewport
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);

	Shader shader("./shader.vert_s", "./shader.frag_s");

	{
		glm::vec3 positions[] = {
			glm::vec3(0, 0, 0),
			glm::vec3(0, 0, 1),
			glm::vec3(0, 0, 2),
			glm::vec3(0, 0, 3),
			glm::vec3(0, 0, 4),
			glm::vec3(1, 0, 0),
			glm::vec3(1, 0, 1),
			glm::vec3(1, 0, 2),
			glm::vec3(1, 0, 3),
			glm::vec3(1, 0, 4),
			glm::vec3(2, 0, 0),
			glm::vec3(2, 0, 1),
			glm::vec3(2, 0, 2),
			glm::vec3(2, 0, 3),
			glm::vec3(2, 0, 4),
			glm::vec3(3, 0, 0),
			glm::vec3(3, 0, 1),
			glm::vec3(3, 0, 2),
			glm::vec3(3, 0, 3),
			glm::vec3(3, 0, 4),
			glm::vec3(4, 0, 0),
			glm::vec3(4, 0, 1),
			glm::vec3(4, 0, 2),
			glm::vec3(4, 0, 3),
			glm::vec3(4, 0, 4),
		};

		GLfloat block[] = {
			//north
			  .5f, -.5f,  -.5f,	0.f, 0.f,
			 -.5f, -.5f,  -.5f,	1.f, 0.f,
			 -.5f,  .5f,  -.5f,	1.f, 1.f,
			  .5f,  .5f,  -.5f,	0.f, 1.f,
			//south
			 -.5f, -.5f,   .5f,	0.f, 0.f,
			  .5f, -.5f,   .5f,	1.f, 0.f,
			  .5f,  .5f,   .5f,	1.f, 1.f,
			 -.5f,  .5f,   .5f,	0.f, 1.f,
			 //east
			 -.5f, -.5f,  -.5f,	0.f, 0.f,
			 -.5f, -.5f,   .5f,	1.f, 0.f,
			 -.5f,  .5f,   .5f,	1.f, 1.f,
			 -.5f,  .5f,  -.5f,	0.f, 1.f,
			 //west
			  .5f, -.5f,   .5f,	0.f, 0.f,
			  .5f, -.5f,  -.5f,	1.f, 0.f,
			  .5f,  .5f,  -.5f,	1.f, 1.f,
			  .5f,  .5f,   .5f,	0.f, 1.f,
			 //top
			 -.5f,  .5f,   .5f,	0.f, 0.f,
			  .5f,  .5f,   .5f,	1.f, 0.f,
			  .5f,  .5f,  -.5f,	1.f, 1.f,
			 -.5f,  .5f,  -.5f,	0.f, 1.f,
			 //bottom
			  .5f, -.5f,   .5f,	0.f, 0.f,
			 -.5f, -.5f,   .5f,	1.f, 0.f,
			 -.5f, -.5f,  -.5f,	1.f, 1.f,
			  .5f, -.5f,  -.5f,	0.f, 1.f,
		};
		GLuint indices[] = {
			//north
			0, 1, 2,
			2, 3, 0,
			//south
			4, 5, 6,
			6, 7, 4,
			//east
			8, 9, 10,
			10, 11, 8,
			//west
			12, 13, 14,
			14, 15, 12,
			//top
			16, 17, 18,
			18, 19, 16,
			//bottom
			20, 21, 22,
			22, 23, 20
		};

		VAO vao;
		EBO ebo(indices, 36);
		VBO vbo(block, sizeof(block));
		VBL layout;
		layout.Push<float>(3);
		layout.Push<float>(2);
		vao.AddBuffer(vbo, layout);
		vbo.Unbind();
		vao.Unbind();

		GameObject cube(vao, ebo);
		

		Texture texture1("wall.jpg");
		Texture texture2("awesomeface.png", GL_RGBA);

		shader.use();
		shader.setInt("Texture1", 0);
		shader.setInt("Texture2", 1);

		Renderer renderer;

		glActiveTexture(GL_TEXTURE0);	
		texture1.Bind();
		glActiveTexture(GL_TEXTURE1);	
		texture2.Bind();

		float timer = 0;

		while (!glfwWindowShouldClose(window)) // start Gameloop
		{
			float currentFrame = static_cast<float>(glfwGetTime());
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;

			ProcessInput(window, camera);//Input

			timer += deltaTime;
			if (timer > .5f) {
				system("cls");
				std::cout << round(1 / deltaTime) << '\n';
				timer = 0;
			}

			//rendering
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);// clear with color
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// clear color/depth buffer

			shader.setMat4("projection", camera.getProjection());

			camera.Move(cameraPos);
			shader.setMat4("view", camera.getView());

			for (auto pos : positions) {
				glm::mat4 model = glm::mat4(1.0f);	
				model = glm::translate(model, pos);
				shader.setMat4("model", model);

				renderer.Draw(cube, shader);
			}

			glfwSwapBuffers(window);
			glfwPollEvents();
		}
	}

	glfwTerminate();
	return 0;
}

void InitGlfw() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void ProcessInput(GLFWwindow* window, Camera cam) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	float cameraSpeed = static_cast<float>(2.5 * deltaTime);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += cameraSpeed * cam.Front;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cam.Front;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos -= glm::normalize(glm::cross(cam.Front, cam.GlobalUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos += glm::normalize(glm::cross(cam.Front, cam.GlobalUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		cameraPos += cameraSpeed * cam.GlobalUp;
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cam.GlobalUp;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	camera.mouse_callback(window, xpos, ypos);
}
#include<conio.h>
#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>�
#include<iterator>
#include<map>
#include<vector>

#include"Renderer.h"
#include"Object.h"
#include"stb_image.h"
#include"Camera.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void key_callback(GLFWwindow* window, int key, int scanCode, int action, int mods);
void process_sustainedinput(GLFWwindow* window);
void InitGlfw();

GLFWmonitor* monitor = glfwGetPrimaryMonitor();
const int SCREEN_WIDTH = 1600;
const int SCREEN_HEIGHT = 900;

glm::vec3 cameraPos(0.f, 0.f, 5.f);
Camera* camera = new Camera(SCREEN_WIDTH, SCREEN_HEIGHT);

float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

bool mouseMode = true; // true = mouse is hidden, false = mouse is visible

int main() {
	InitGlfw();

	//InitWindow
	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Engine", NULL, NULL);
	//GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Engine", glfwGetPrimaryMonitor(), NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(window);

	gladLoadGL();

	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetKeyCallback(window, key_callback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSwapInterval(.5f); //60 fps so our gpu doesnt explode

	//HadleViewport
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);

	{
		Shader shader("./shader.vert_s", "./shader.frag_s");

		Texture texture("Default.png", GL_RGBA);

	
		float block[] = {
			//north
			  .5f, -.5f,  -.5f,	
			 -.5f, -.5f,  -.5f,	
			 -.5f,  .5f,  -.5f,	
			  .5f,  .5f,  -.5f,	
			//south
			 -.5f, -.5f,   .5f,	
			  .5f, -.5f,   .5f,	
			  .5f,  .5f,   .5f,	
			 -.5f,  .5f,   .5f,
			 //east
			 -.5f, -.5f,  -.5f,	
			 -.5f, -.5f,   .5f,	
			 -.5f,  .5f,   .5f,	
			 -.5f,  .5f,  -.5f,	
			 //west
			  .5f, -.5f,   .5f,	
			  .5f, -.5f,  -.5f,	
			  .5f,  .5f,  -.5f,	
			  .5f,  .5f,   .5f,
			 //top
			 -.5f,  .5f,   .5f,	
			  .5f,  .5f,   .5f,
			  .5f,  .5f,  -.5f,
			 -.5f,  .5f,  -.5f,
			 //bottom
			  .5f, -.5f,   .5f,	
			 -.5f, -.5f,   .5f,	
			 -.5f, -.5f,  -.5f,	
			  .5f, -.5f,  -.5f,
		};
		float uv[]{
			0.f, 0.f,
			1.f, 0.f,
			1.f, 1.f,
			0.f, 1.f,

			0.f, 0.f,
			1.f, 0.f,
			1.f, 1.f,
			0.f, 1.f,

			0.f, 0.f,
			1.f, 0.f,
			1.f, 1.f,
			0.f, 1.f,

			0.f, 0.f,
			1.f, 0.f,
			1.f, 1.f,
			0.f, 1.f,

			0.f, 0.f,
			1.f, 0.f,
			1.f, 1.f,
			0.f, 1.f,

			0.f, 0.f,
			1.f, 0.f,
			1.f, 1.f,
			0.f, 1.f,
		};
		unsigned int indices[] = {
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

		std::vector<float> vert;
		std::vector<float> UV;
		std::vector<unsigned int> tri;

		vert.insert(vert.end(), std::begin(block), std::end(block));
		UV.insert(UV.end(), std::begin(uv), std::end(uv));
		tri.insert(tri.end(), std::begin(indices), std::end(indices));

		Object cube("Cube", vert, UV, tri);

		std::vector<Object> objects;
		for (int x = 0; x < 32; x++)
			for (int y = 0; y < 32; y++)
				for (int z = 0; z < 32; z++)
				{
					Object obj = cube;
					obj.transform.Positon = {x, y, z};
					objects.push_back(obj);
				}

		Object merged = Object::merge_objects(objects, "Chunk");
		RendererObject mergedRenderObject = merged.parse();

		Renderer renderer;

		float timer = 0;

		while (!glfwWindowShouldClose(window)) // start Gameloop
		{
			float currentFrame = static_cast<float>(glfwGetTime());
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;

			//FPS counter
			timer += deltaTime;
			if (timer > 1) {
				system("cls");
				std::cout << "FPS: " << 1.0f / deltaTime;
				timer = 0;
			}

			//rendering
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);// clear with color
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// clear color/depth buffer

			process_sustainedinput(window); // processes input that is held down

			camera->move(cameraPos);
			renderer.set_currentcamera(shader, *camera);

			renderer.draw(mergedRenderObject, shader);

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

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	if (mouseMode) {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		camera->mouse_callback(window, xpos, ypos);
	}
	else 
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}
void process_sustainedinput(GLFWwindow* window) { // processes input that is held down
	float cameraSpeed = static_cast<float>(2.5 * deltaTime);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += cameraSpeed * camera->front;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= cameraSpeed * camera->front;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos -= glm::normalize(glm::cross(camera->front, camera->globalUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos += glm::normalize(glm::cross(camera->front, camera->globalUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		cameraPos += cameraSpeed * camera->globalUp;
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		cameraPos -= cameraSpeed * camera->globalUp;
}
void key_callback(GLFWwindow* window, int key, int scanCode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		mouseMode = !mouseMode;
}
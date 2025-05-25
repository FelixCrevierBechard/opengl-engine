#pragma once

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<GLFW/glfw3.h>

class Camera
{
private:
	glm::mat4 projection;
	glm::mat4 view = glm::mat4(1.f);

	int screenWidth = 500;
	int screenHeight = 500;

	float yaw = -90.0f;
	float pitch = 0.0f;
	float lastX = 1600.0f / 2.0;
	float lastY = 900.0 / 2.0;
	float fov = 90.0f;
	float closePlane = 0.1f;
	float farPlane = 100.0f;
	bool firstMouse = true;

	glm::vec3 position = glm::vec3(0.0f, 0.0f, 5.0f); // Default camera position
public:
	const glm::vec3 globalUp = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);

	Camera(int screenWidth, int screenHeight);

	void move(glm::vec3 position);
	glm::mat4 get_projection();
	glm::mat4 get_view() const;
	glm::vec3 get_position() const { return position; }

	void set_screen_size(int width, int height) {
		screenWidth = width;
		screenHeight = height;
		projection = glm::perspective(glm::radians(fov), (float)screenWidth / (float)screenHeight, closePlane, farPlane);
	}

	void mouse_callback(GLFWwindow* window, double xpos, double ypos);
};


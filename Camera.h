#pragma once
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<GLFW/glfw3.h>

class Camera
{
public:
	const glm::vec3 GlobalUp = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 Front = glm::vec3(0.0f, 0.0f, -1.0f);

	Camera(int screenWidth, int screenHeight);

	void Move(glm::vec3 position);
	glm::mat4 getProjection();
	glm::mat4 getView() const;
	void mouse_callback(GLFWwindow* window, double xpos, double ypos);
private:
	glm::mat4 Projection;
	glm::mat4 View = glm::mat4(1.f);

	int ScreenWidth;
	int ScreenHeight;

	float Yaw = -90.0f;
	float Pitch = 0.0f;
	float LastX = 1600.0f / 2.0;
	float LastY = 900.0 / 2.0;
	float Fov = 90.0f;
	bool FirstMouse = true;
};


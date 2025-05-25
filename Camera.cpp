#include "Camera.h"

Camera::Camera(int screenWidth, int screenHeight){
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;
	projection = glm::perspective(glm::radians(fov), (float)this->screenWidth / (float)this->screenHeight, closePlane, farPlane);
}

void Camera::move(glm::vec3 position) {
	this->position = position;
	view = glm::lookAt(this->position, this->position + front, globalUp);
}

glm::mat4 Camera::get_projection(){
    projection = glm::perspective(glm::radians(fov), (float)screenWidth / (float)screenHeight, closePlane, farPlane);
	return projection;
}
glm::mat4 Camera::get_view() const {
	return view;
}

void Camera::mouse_callback(GLFWwindow* window, double xPosIn, double yPosIn)
{
    float xpos = static_cast<float>(xPosIn);
    float ypos = static_cast<float>(yPosIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 90.0f)
        pitch = 90.0f;
    if (pitch < -90.0f)
        pitch = -90.0f;

    glm::vec3 front = this->front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    this->front = glm::normalize(front);
}

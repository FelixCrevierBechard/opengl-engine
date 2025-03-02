#include "Camera.h"

Camera::Camera(int screenWidth, int screenHeight){
    ScreenWidth = screenWidth;
    ScreenHeight = screenHeight;
	Projection = glm::perspective(glm::radians(Fov), (float)screenWidth / (float)screenHeight, 0.1f, 100.0f);
}

void Camera::Move(glm::vec3 position) {
	View = glm::lookAt(position, position + Front, GlobalUp);
}

glm::mat4 Camera::getProjection(){
    Projection = glm::perspective(glm::radians(Fov), (float)ScreenWidth / (float)ScreenHeight, 0.1f, 100.0f);
	return Projection;
}
glm::mat4 Camera::getView() const {
	return View;
}

void Camera::mouse_callback(GLFWwindow* window, double xPosIn, double yPosIn)
{
    float xpos = static_cast<float>(xPosIn);
    float ypos = static_cast<float>(yPosIn);

    if (FirstMouse)
    {
        LastX = xpos;
        LastY = ypos;
        FirstMouse = false;
    }

    float xoffset = xpos - LastX;
    float yoffset = LastY - ypos;
    LastX = xpos;
    LastY = ypos;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    Yaw += xoffset;
    Pitch += yoffset;

    if (Pitch > 89.0f)
        Pitch = 89.0f;
    if (Pitch < -89.0f)
        Pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Front = glm::normalize(front);
}


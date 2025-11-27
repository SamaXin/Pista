//#include <GL/glew.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "./../headerFiles/Input.h"
using namespace std;

float zSpeed = 0.02f;
//---------------Camera Class----------------------------//
Camera::Camera(glm::vec3 positionCam,glm::vec3 lookCam,
	double yaw, double radCam, double pitch, double sensi)
	: positionCam(positionCam),target(lookCam),
	yaw(yaw), radCam(radCam), pitch(pitch), sensi(sensi) {

	//camOrbit();    
}
Camera::~Camera() {}
void Camera::calCameraCor(glm::vec2 deltaCor)
{
	double dx = deltaCor.x;
	double dy = deltaCor.y;

	//float sensitivity = 0.1f;
	dx *= sensi;
	dy *= sensi;

	yaw += dx;
	pitch += dy;
	// clamp pitch
	if (pitch > 89.0f) pitch = 89.0f;
	if (pitch < -89.0f) pitch = -89.0f;

	// Recalculate direction
	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	this->direction=glm::normalize(direction);

	camOrbit();
	

	//std::cout << positionCam.x <<' ' << positionCam.y <<' ' << positionCam.z << std::endl;

}
void Camera::zMove(double xOffset,double yOffset) {
	//float xOffSet = xOffset;
	//float yOffSet = yOffset;
	
	if (radCam + ((float)(xOffset + yOffset) * 0.5) > 0.0) {
		radCam += ((float)(xOffset + yOffset) * 0.5);
	}
	else std::cout << "Max Zoom limit Reached" << std::endl;
	camOrbit();
}
void Camera::camOrbit() {
	//Camera* cam = static_cast<Camera*>(glfwGetWindowUserPointer(window));
	positionCam.x = target.x - direction.x * radCam;
	positionCam.y = target.y - direction.y * radCam;
	positionCam.z = target.z - direction.z * radCam;
}



glm::vec3 Camera::getCamPos() { return { positionCam }; }

//---------------Input Class----------------------------//

Input::Input(GLFWwindow* window, Camera* cam): clicked(false), camera(cam) {
	glfwSetWindowUserPointer(window, this);
	glfwSetKeyCallback(window, Input::keyInput);
	glfwSetMouseButtonCallback(window, Input::mouseInput);
	glfwSetCursorPosCallback(window, Input::cursor);
	glfwSetScrollCallback(window, Input::scrollBar);
}
Input::~Input() {}

void Input::keyInput(GLFWwindow* window, int key, int scancode, int action, int mods) {
	Input* input = static_cast<Input*>(glfwGetWindowUserPointer(window));
	if (action == GLFW_PRESS) {
		if (key == GLFW_KEY_ESCAPE) {
			std::cout << "Escape Pressed" << std::endl;
			glfwSetWindowShouldClose(window, true);
		}
		if (key == GLFW_KEY_P) {
			std::cout << "Action Pressed" << std::endl;
		}
	}
	
}

void Input::mouseInput(GLFWwindow* window, int key, int action, int mods) {
	Input* input = static_cast<Input*>(glfwGetWindowUserPointer(window));
	if (!input) return;
	if (key ==  GLFW_MOUSE_BUTTON_LEFT) {
		if (action == GLFW_PRESS)input->clicked = true;
		if (action == GLFW_RELEASE) {
			input->clicked = false;
		}
	}
}
void Input::cursor(GLFWwindow* window, double xpos, double ypos) {
	Input* input = static_cast<Input*>(glfwGetWindowUserPointer(window));
	input->lastMouseCor = input->curMouseCor;
	input->curMouseCor.x = xpos;
	input->curMouseCor.y = ypos;
	if (input->clicked) {
		double dx = input->curMouseCor.x - input->lastMouseCor.x;
		double dy = input->lastMouseCor.y - input->curMouseCor.y;
		input->camera->calCameraCor(glm::vec2(dx,dy));
	}

	
}
void Input::scrollBar(GLFWwindow* window, double xOffset, double yOffset) {
	Input* input = static_cast<Input*>(glfwGetWindowUserPointer(window));
	//std::cout << input->curMouseCor.x << ' ' << input->curMouseCor.y << std::endl;
	//std::cout << input->curMouseCor.x << ' ' << input->curMouseCor.y << std::endl;
	input->camera->zMove(xOffset, yOffset);
	std::cout << "Vertical scroll bar " << yOffset << std::endl;

}

//getter functions
glm::vec2 Input::getCoordinate() { return curMouseCor; }
bool Input::click() { return clicked; }



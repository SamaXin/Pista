#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "./../headerFiles/Input.h"
using namespace std;

Input::Input(GLFWwindow* window):persp(true),clicked(false) {
	glfwSetWindowUserPointer(window, this);
	glfwSetKeyCallback(window,Input::keyInput);
	glfwSetMouseButtonCallback(window, Input::mouseInput);
	glfwSetCursorPosCallback(window, Input::cursor);
	glfwSetScrollCallback(window,Input::scrollBar);
}
Input::~Input() {
	
}
void Input::keyInput(GLFWwindow* window, int key, int scancode, int action, int mods) {
	//Input* keyInput = static_cast<Input*>(glfwGetWindowUserPointer(window));

	if (action == GLFW_PRESS) {
		if (key == GLFW_KEY_ESCAPE) {
			std::cout << "Escape Pressed" << std::endl;
			glfwSetWindowShouldClose(window, true);
		}
		if (key == GLFW_KEY_P) {
			std::cout << "Action Pressed" << std::endl;
		}
	}
	/*if (action == GLFW_PRESS) {
		if (keyInput->onKeyPressed){
			keyInput->onKeyPressed(key); 
		}
	}*/
}
void Input::mouseInput(GLFWwindow* window, int key, int action, int mods) {
	Input* input = static_cast<Input*>(glfwGetWindowUserPointer(window));
	if (!input) return;
	if (key ==  GLFW_MOUSE_BUTTON_LEFT) {
		if(action==GLFW_PRESS)input->clicked = true;
		else if (action == GLFW_RELEASE && input->clicked) {
			input->clicked = false;
			std::cout << "Mouse Position " << input->mouseX << " , " << input->mouseY << std::endl;
		}
	}
}
void Input::cursor(GLFWwindow* window, double xpos, double ypos) {
	Input* cur = static_cast<Input*>(glfwGetWindowUserPointer(window));
	cur->mouseX = xpos;
	cur->mouseY = ypos;
}
void Input::scrollBar(GLFWwindow* window, double xOffset, double yOffset) {
	Input* cur = static_cast<Input*>(glfwGetWindowUserPointer(window));
	std::cout << "Vertical scroll bar " << yOffset << std::endl;
}
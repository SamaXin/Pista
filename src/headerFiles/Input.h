#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <functional>

using namespace std;
class Input {
private:
	unsigned int Render_Id;
	double mouseX = 0.0f;
	double mouseY = 0.0f;
	bool clicked;
	bool persp;
public:
	Input(GLFWwindow* window);
	~Input();

	static void keyInput(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void mouseInput(GLFWwindow* window, int key,int action,int mods);
	static void cursor(GLFWwindow* window, double xpos, double ypos);
	static void scrollBar(GLFWwindow* window, double xOffset, double yOffset);
	//bool perspectiveView() { return persp; }
};
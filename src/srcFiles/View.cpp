//#include <GL/glew.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <gtc/type_ptr.hpp>
#include <gtc/constants.hpp>
#include "./../headerFiles/View.h"
#include <iostream>
using namespace std;


View::View(glm::vec3 cameraPos, glm::vec3 cameraTar, glm::vec3 cameraDir)
	:cameraPos(cameraPos),cameraTar(cameraTar),cameraDir(cameraDir) {}


glm::mat4 View::getViewMatrix() const
{
	return glm::lookAt(cameraPos, cameraTar, cameraDir);
}

glm::vec3 View::getPosCamera() const
{
	return cameraPos;
}

void View::setPosCamera(const glm::vec3& newPos) 
{
	cameraPos = newPos;
}

#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <gtc/constants.hpp>
#include <iostream>

class View{
private:
    //unsigned int programId;
    glm::vec3 cameraPos;
    glm::vec3 cameraTar;
    glm::vec3 cameraDir;
public:
    View(
        glm::vec3 cameraPos, glm::vec3 cameraTar, glm::vec3 cameraDir
    );
    glm::mat4 getViewMatrix() const;
    //glm::vec3 getPosCamera() const;
    void setCamPos(const glm::vec3& newPos);
};
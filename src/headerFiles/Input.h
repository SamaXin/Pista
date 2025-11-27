#pragma once  
#include <glad/glad.h>  
#include <GLFW/glfw3.h>  
#include <iostream>  
#include <functional>  
#include <glm.hpp> 
#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>  
#include <gtc/constants.hpp>  
using namespace std;  

//----------------Camera-----------------------//  
class Camera {  
private:  
    glm::vec3 positionCam,direction;
    glm::vec3 target;
   double yaw, radCam, pitch, sensi;  
   glm::vec2 lastCor;  
public:  
   Camera(glm::vec3 postionCam,glm::vec3 lookCam,
       double yCam, double rCam, double pCam, double sCam);  
   ~Camera();  
   void calCameraCor(glm::vec2 deltaCor);
   void zMove(double xOffset, double yOffset);
   void camOrbit();  

   // Getter function  
   glm::vec3 getCamPos();  
};

//----------------Input-----------------------//  
class Input {  
private:  
   Camera* camera;  
   unsigned int Render_Id;  
   glm::vec2 curMouseCor; 
   glm::vec2 lastMouseCor;
   bool clicked;  

public:  
   Input(GLFWwindow* window, Camera* cam);  
   ~Input();  

   static void keyInput(GLFWwindow* window, int key, int scancode, int action, int mods);  
   static void mouseInput(GLFWwindow* window, int key, int action, int mods);  
   static void cursor(GLFWwindow* window, double xpos, double ypos);  
   static void scrollBar(GLFWwindow* window, double xOffset, double yOffset);  

   // Getter functions  
   glm::vec2 getCoordinate();  
   bool click();  
};  

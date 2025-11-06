// main.cpp
//#include <GL/glew.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <cmath>
//External Files inclusion
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <gtc/constants.hpp>
//Source Files inclusion
#include "./../headerFiles/IndexBuffer.h"
#include "./../headerFiles/VertexBuffer.h"
#include "./../headerFiles/VertexArray.h"
#include "./../headerFiles/Shader.h"
#include "./../headerFiles/Input.h"
#include "./../headerFiles/View.h"
//imgui
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

using namespace std;


float vertex[] = {
   0.0f,  0.5f,  0.0f,  // top
    -0.5f, -0.5f,  0.5f,  // front-left
     0.5f, -0.5f,  0.5f,  // front-right
     0.0f, -0.5f, -0.5f   // back
};
unsigned int indexs[]{
   0, 1, 2,
    0, 2, 3,
    0, 3, 1,
    1, 3, 2
};

bool direction = true;//left
float moveIncrement = 0.005f;
float x = 0.0f;
float y = 0.0f;
float z = 0.0f;
float minAll = -0.7f;
float maxAll = 0.7f;

float angle = 0; // degrees
float angleInc = 1;

float scaleInc = 0.0005f;
float scaleMin = 0.1f;
float scaleMax = 1.0f;
float scale = 0.6f;

float cameraSpeed = 0.02f;



int main() {
    if (!glfwInit()) {
        cout << "Failed to initialize GLFW" << endl;
        return -1;
    }
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
    GLFWwindow* window = glfwCreateWindow(1200, 800, "Test", NULL, NULL);
    if (window == NULL) {
        cout << "Error!" << endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD!" << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

    //Debug Call back function
    //InitDebugCallBack();

    //vertex array objects.
    VertexArray va;

    //vertex buffer objects.
    VertexBuffer vb(vertex, sizeof(vertex));

    //index bffer objects.
    IndexBuffer ib(indexs, sizeof(indexs));

    //Attribute telling openGL how to read the data.
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(0);

    //step 7.
    // C:/Users/bhati/Music/OpenGL/__PROJECTS_/Template/CMakeProject1/src/shaders/vertex.shader
    const string vertexPath = "shaders/vertex.shader";
    const string fragmentPath = "shaders/fragment.shader";

    //Shader Class Object 
    Shader shader(vertexPath, fragmentPath);
    unsigned int programId = shader.getId();
    shader.bind();
    if (!shader.fileStatus()) {
        cout << "Not Able to open file content Check Path or Code once \n";
        return -1;
    }
    //cout << shader.vertexShader() << "\n" << shader.fragmentShader();

    //Calling the CreateShader() func to get shader's Code & program where these are Located
    if (programId == -1) {
        cout << "Shader Value coming as INVALID" << endl;
        return 0;
    }
    //std::cout << programId << std::endl;
    // Setting up Camera

    //glm::mat4 view = glm::lookAt(cameraPos,cameraTarget,direction);//View Matrix
    View camera(
        glm::vec3(0.0f, 0.0f, -3.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(-1.0f, 1.0f, 0.0f)
    );

    //GLM way of using the basic trans,rotate,scaling operations
    float aspRatio = 1200.0 / 800.0;
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 perProj = glm::perspective(45.0f, aspRatio, 0.5f, 100.0f);
    //glm::mat4 ortProj = glm::ortho(-0.8f, 0.8f, -0.8f, 0.8f, 0.5f, 100.0f);
    model = glm::translate(model, glm::vec3(x, y, z));//Translation
    //Calling uniform location 
    int locationColor = glGetUniformLocation(programId, "uColor");
    int locationTrans = glGetUniformLocation(programId, "model");
    int locationPProj = glGetUniformLocation(programId, "perProj");
    //int locationOProj = glGetUniformLocation(programId, "ortProj");
    glUniform4f(locationColor, 0.0f, 0.0f, 0.0f, 1.0f);//Color Set
    glUniformMatrix4fv(locationTrans, 1, GL_FALSE, glm::value_ptr(model));//GLM way Translate
    glUniformMatrix4fv(locationPProj, 1, GL_FALSE, glm::value_ptr(perProj));//perspective Projection
    //glUniformMatrix4fv(locationOProj, 1, GL_FALSE, glm::value_ptr(ortProj));//Orthographic Projection


    //Camera View Setup
    glm::mat4 view = camera.getViewMatrix();
    int locationView = glGetUniformLocation(programId, "view");
    glUniformMatrix4fv(locationView, 1, GL_FALSE, glm::value_ptr(view));

    // Initialize ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    //std::cout << locationPProj <<" "<<locationTrans << std::endl;
    //Input.h object
    Input input(window);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //Only Draw outlayer 
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        va.bind();

        // Movements through Keys W S A D (Object)
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
            if (y + moveIncrement < maxAll)y += moveIncrement;
            else std::cout << "Top Limit Reached" << std::endl;
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
            if (y - moveIncrement > minAll)y -= moveIncrement;
            else std::cout << "Bottom Limit Reached" << std::endl;
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
            if (x + moveIncrement < maxAll)x += moveIncrement;
            else std::cout << "Right Limit Reached" << std::endl;
        }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
            if (x - moveIncrement > minAll)x -= moveIncrement;
            else std::cout << "Left Limit Reached" << std::endl;
        }
        //Camera Movement Keys
        if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
            glm::vec3 pos = camera.getPosCamera();
            if (pos.z - cameraSpeed > -8.0f) {
                pos.z -= cameraSpeed;
                camera.setPosCamera(pos);
            }
            else {
                std::cout << "Closest Position Reached\n";
            }
        }

        if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) {
            glm::vec3 pos = camera.getPosCamera();
            if (pos.z + cameraSpeed < 8.0f) {
                pos.z += cameraSpeed;
                camera.setPosCamera(pos);
            }
            else {
                std::cout << "Far Position Reached\n";
            }
        }
        
        

        glm::mat4 model = glm::mat4(1.0f); // identity
        model = glm::translate(model, glm::vec3(x, y, z));//Translation
        
        glUniform4f(locationColor, 1.0f, 0.0f, 0.0f, 1.0f);//Color Set
        glUniformMatrix4fv(locationTrans, 1, GL_FALSE, glm::value_ptr(model));//xMove with GLM
        //glm::mat4 ortProj = glm::ortho(-0.8f, 0.8f, -0.8f, 0.8f, 0.5f, 100.0f);
        glUniformMatrix4fv(locationPProj, 1, GL_FALSE, glm::value_ptr(perProj));//Perspective Projection


        glm::mat4 view = camera.getViewMatrix();//View Matrix
        glUniformMatrix4fv(locationView, 1, GL_FALSE, glm::value_ptr(view));


        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);


        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, nullptr);
        
        // --- Start ImGui frame ---
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // --- GUI code ---
        ImGui::Begin("Hello, ImGui!");
        ImGui::Text("ImGui is working!");
        ImGui::End();

        // --- Render GUI ---
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);   // Show what you just rendered
        glfwPollEvents();
    }
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwSetWindowShouldClose(window, true);
    return 0;
}

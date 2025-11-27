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
#include "./../mesh/sphere.h"
//imgui
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

using namespace std;

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

unsigned int total = 30;
float slices = 20;
float radius = 0.5f;



void guiPanel() {
    const float panelWidth = 200.0f;

    // Set next window size
    ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x - panelWidth, 0));
    ImGui::SetNextWindowSize(ImVec2(panelWidth, ImGui::GetIO().DisplaySize.y));

    // Create window without titlebar or movement
    ImGuiWindowFlags flags =
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoBringToFrontOnFocus |
        ImGuiWindowFlags_NoNavFocus;

    ImGui::Begin("RightPanel", nullptr, flags);

    ImGui::Text("Settings Panel");
    ImGui::Separator();

    // Example UI elements
    static float brightness = 1.0f;
    ImGui::SliderFloat("Brightness", &brightness, 0.0f, 2.0f);

    static float exposure = 1.0f;
    ImGui::DragFloat("Exposure", &exposure, 0.01f, 0.0f, 10.0f);

    static bool enabled = false;
    ImGui::Checkbox("Enable Shadows", &enabled);


    ImGui::End();
}



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

    //sphere calling class
    sphere sphere(total, slices, radius);
    glm::vec3 lookCam=sphere.getCenter();
    glm::vec3 positionCam = {0.0f,0.0f,-3.0f};
    static std::vector<float>vert= sphere.getInterleaved();

    //std::cout << lookCam.x << ',' << lookCam.y << ' ' << lookCam.z << endl;

    //vertex array objects.
    VertexArray va;

    //vertex buffer objects.z
    VertexBuffer vb(vert.data(), vert.size() * sizeof(float));

    //index bffer objects.
    //IndexBuffer ib(indexs, sizeof(indexs));

    //Attribute telling openGL how to read the data.
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    //step 7.
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

    //Lighting and coloring
    int sphereColor = glGetUniformLocation(programId, "sphereColor");
    int ambientColor = glGetUniformLocation(programId, "ambientColor");
    int difLightPos = glGetUniformLocation(programId, "difLightPos");
    int difLightCol = glGetUniformLocation(programId, "difLightCol");
    int specLightCol = glGetUniformLocation(programId,"specLightCol");
    int camPos = glGetUniformLocation(programId, "camPos");

    glUniform3f(sphereColor, 0.0f, 1.0f, 0.0f);
    glUniform3f(ambientColor, 2.0f, 1.0f, 1.0f);
    glUniform3f(difLightPos, 10.0f, 10.0f, -10.0f);
    glUniform3f(difLightCol, 1.0f, 1.0f, 1.0f);
    glUniform3f(specLightCol, 1.0f, 1.0f, 1.0f);
    glUniform3f(camPos, positionCam.x, positionCam.y, positionCam.z);

    View camera(
        positionCam,
        lookCam,
        glm::vec3(0.0f, 1.0f, 0.0f)
    );

    //GLM way of using the basic trans,rotate,scaling operations
    float aspRatio = 1200.0 / 800.0;
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 perProj = glm::perspective(45.0f, aspRatio, 0.5f, 100.0f);

    model = glm::translate(model, glm::vec3(x, y, z));//Translation
    //Calling uniform location 
    int locationTrans = glGetUniformLocation(programId, "model");
    int locationPProj = glGetUniformLocation(programId, "perProj");

    glUniformMatrix4fv(locationTrans, 1, GL_FALSE, glm::value_ptr(model));//GLM way Translate
    glUniformMatrix4fv(locationPProj, 1, GL_FALSE, glm::value_ptr(perProj));//perspective Projection

    //Camera View Setup
    glm::mat4 view = camera.getViewMatrix();
    int locationView = glGetUniformLocation(programId, "view");
    glUniformMatrix4fv(locationView, 1, GL_FALSE, glm::value_ptr(view));


    //Input Handling 
    Camera cam(positionCam,lookCam,0.0f,3.0f,0.0f,0.07f);
    //yaw,radius,pitch,sensitivity
    Input input(window,&cam);

    glm::vec3 pos = cam.getCamPos();
    //cout << pos.x << ' ' <<pos.y<<' ' << pos.z << endl;


    // Initialize ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");


    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);
        //Only Draw outlayer 
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

       
        
        //if(input.click())cout << cord[0] << ' ' << cord[1] << endl;

        glUseProgram(programId);

        sphereColor = glGetUniformLocation(programId, "sphereColor");
        ambientColor = glGetUniformLocation(programId, "ambientColor");
        difLightPos = glGetUniformLocation(programId, "difLightPos");
        difLightCol = glGetUniformLocation(programId, "difLightCol");
        specLightCol = glGetUniformLocation(programId, "specLightCol");
        camPos = glGetUniformLocation(programId,"camPos");




        //Camera Movement Keys
        glm::vec2 cord = input.getCoordinate();
        glm::vec3 pos = cam.getCamPos();
        camera.setCamPos(pos);
   
        glUniform3f(sphereColor, 0.0f, 1.0f, 0.0f);
        glUniform3f(ambientColor, 1.0f, 0.5f, 0.0f);
        glUniform3f(difLightPos, 10.0f, 10.0f, -10.0f);
        glUniform3f(difLightCol, 1.0f, 1.0f, 1.0f);
        glUniform3f(specLightCol, 1.0f, 1.0f, 1.0f);
        glUniform3f(camPos, pos.x,pos.y,pos.z);

        

        glm::mat4 model = glm::mat4(1.0f); // identity
        glm::mat4 view = camera.getViewMatrix();//View Matrix
        //model = glm::translate(model, glm::vec3(x, y, z));//Translation
        
        glUniformMatrix4fv(locationTrans, 1, GL_FALSE, glm::value_ptr(model));//xMove with GLM
        glUniformMatrix4fv(locationPProj, 1, GL_FALSE, glm::value_ptr(perProj));//Perspective Projection
        glUniformMatrix4fv(locationView, 1, GL_FALSE, glm::value_ptr(view));

        //glPointSize(3.0f);
       
        va.bind();

        //glDrawElements(GL_TRIANGLES, vert.size(), GL_UNSIGNED_INT, nullptr);//with index buffer
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glUniform3f(sphereColor, 0.7f, 0.7f, 0.5f);
        glDrawArrays(GL_TRIANGLES,0,vert.size()/6);//with vertex buffer

        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glLineWidth(2.0f);
        glUniform3f(sphereColor, 1.0f, 1.0f, 1.0f);
        glDrawArrays(GL_TRIANGLES, 0, vert.size()/6);
        

         //glPointSize(0.5f);
        //glDrawArrays(GL_POINTS, 0, vert.size());




        
        // --- Start ImGui frame ---
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // --- GUI code ---
        guiPanel();

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

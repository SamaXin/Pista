//#include <GL/glew.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "./../headerFiles/Renderer.h"
using namespace std;


//------------------Renderer Class---------------------------
//class Renderer {
//public:
//    Renderer();
//    ~Renderer();
//};

//Clearing the error Before checking the error to specific call back func
void GLClearError() {
    while (glGetError() != GL_NO_ERROR);
}

//Getting an error in specific function or line 
void GLGetError() {
    while (unsigned int error = glGetError()) {
        cout << "Error in openGL : " << error << endl;
    }
}

//Error Hndling using glDebugCallback()
void APIENTRY GLDebugMessageCallBack(GLenum source,
    GLenum type,
    GLuint id,
    GLenum severity,
    GLsizei length,
    const GLchar* message,
    const void* userParam) {
    cout << "GL CALLBACK: " << (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "")
        << " type = " << type
        << ", severity = " << severity
        << ", message = " << message
        << endl;
    return;
}

//InitDebugCallBack()
void InitDebugCallBack() {
    int flags;
    glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
    if (flags & GL_CONTEXT_FLAG_DEBUG_BIT) {
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(GLDebugMessageCallBack, nullptr);
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
    }
}




#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

//Error Hndling using glDebugCallback()
void APIENTRY GLDebugMessageCallBack(GLenum source,GLenum type,
    GLuint id,GLenum severity,GLsizei length,const GLchar* message,const void* userParam);

//InitDebugCallBack()
void InitDebugCallBack();

//Clearing the error Before checking the error to specific call back func
void GLClearError();

//Getting an error in specific function or line 
void GLGetError();

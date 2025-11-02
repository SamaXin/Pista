
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "./../headerFiles/shader.h"
#include <iostream>
#include <string>
#include <math.h>
#include <fstream>
#include <sstream>

using namespace std;

string VertexCode = "", FragmentCode = "";
Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath) :m_RenderId(0),
fileOpen(false),vertexCode(""),fragmentCode("") {
    fileOpen=ReadShader(vertexPath, fragmentPath);
    vertexCode = VertexCode;
    fragmentCode = FragmentCode;
    m_RenderId=CreateShader(VertexCode,FragmentCode);
    //std::cout << m_RenderId << std::endl;
}
Shader::~Shader() {
    glDeleteProgram(m_RenderId);
}

//Reading the Shader program
bool Shader::ReadShader(const std::string& vertexPath, const std::string& fragmentPath) {
    stringstream buffer;
    ifstream vContent(vertexPath);

    if (!vContent.is_open()) {
        return false;
    }
    string line;
    while (getline(vContent, line)) {
        VertexCode += line + "\n";
    }
    ifstream fContent(fragmentPath);
    if (!fContent.is_open()) {
        cout << "Failed to Load Fragment Shader \n";
        return false;
    }
    while (getline(fContent, line)) {
        FragmentCode += line + "\n";
    }
    return true;
}


//Compiling the Shader Program
unsigned int Shader::CompileShader(unsigned int type, const std::string& shader) {
    unsigned int id = glCreateShader(type);
    const char* src = shader.c_str();//Memory Address of first character
    //unsigned int length=
    glShaderSource(id, 1, &src, nullptr);
    //Error Handling

    //
    glCompileShader(id);
    return id;
}


//Creating the Shader 
unsigned int Shader::CreateShader(const std::string & vertexShader, const std::string  & fragmentShader) {
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    //Attach shaders to program
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    //Link to Program
    glLinkProgram(program);
    //Validate the program
    glValidateProgram(program);
    //Delete Shader after Use
    glDeleteShader(vs);
    glDeleteShader(fs);
    return program;
}

//Binding the program
void Shader::bind()  {
    glUseProgram(m_RenderId);
}

//undbind the program
void Shader::unbind() {
    glUseProgram(0);
}
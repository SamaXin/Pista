//#include <GL/glew.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "./../headerFiles/IndexBuffer.h"

IndexBuffer::IndexBuffer(const void* data, unsigned int size) {
    glGenBuffers(1, &m_RenderId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RenderId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}
IndexBuffer::~IndexBuffer() {
    glDeleteBuffers(1, &m_RenderId);
}
void IndexBuffer::bind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RenderId);
}
void IndexBuffer::unbind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "./../headerFiles/VertexBuffer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size) {
    glGenBuffers(1, &m_RenderId);
    glBindBuffer(GL_ARRAY_BUFFER, m_RenderId);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}
VertexBuffer::~VertexBuffer() {
    glDeleteBuffers(1, &m_RenderId);
}
void VertexBuffer::bind() {
    glBindBuffer(GL_ARRAY_BUFFER, m_RenderId);
}
void VertexBuffer::unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
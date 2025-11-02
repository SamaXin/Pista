#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "./../headerFiles/VertexArray.h"

using namespace std;

VertexArray::VertexArray() {
	glGenVertexArrays(1,&m_RenderId);
	glBindVertexArray(m_RenderId);
}
VertexArray::~VertexArray() {
	glDeleteVertexArrays(1, &m_RenderId);
}

void VertexArray::bind() {
	glBindVertexArray(m_RenderId);
}
void VertexArray::unbind() {
	glBindVertexArray(0);
}
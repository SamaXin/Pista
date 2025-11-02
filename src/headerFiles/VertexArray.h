#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class VertexArray {
private:
	unsigned int m_RenderId;
public:
	VertexArray();
	~VertexArray();

	void bind();
	void unbind();
};

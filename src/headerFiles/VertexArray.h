#pragma once
#include <glad/glad.h>
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

#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class VertexBuffer {
private:
	unsigned int m_RenderId;
public:
	VertexBuffer(const void* data,unsigned int size);//Constructor
	~VertexBuffer();

	void bind();
	void unbind();
};
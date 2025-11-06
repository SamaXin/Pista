#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class IndexBuffer {
private:
	unsigned int m_RenderId;
public:
	IndexBuffer(const void* data, unsigned int size);//Constructor
	~IndexBuffer();

	void bind();
	void unbind();
}; 

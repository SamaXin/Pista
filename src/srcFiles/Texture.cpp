//#include <GL/glew.h>
//#include <GLFW/glfw3.h>
//#include <iostream>
//#include "Texture.h"
//#include <string>
//#include "Vendor/stb_image/stb_image.h"
//using namespace std;
//
//Texture::Texture(const string &path):m_RenderId(0),filePath(path), 
//m_localBuffer(nullptr), height(0), width(0), bpp(0)
//{
//	stbi_set_flip_vertically_on_load(true);
//	m_localBuffer = stbi_load(path.c_str(), &width, &height, &bpp, 4);
//
//	glGenTextures(1,&m_RenderId);
//	glBindTexture(GL_TEXTURE_2D,m_RenderId);
//
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
//
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width, height, 0, GL_RGBA16F, GL_UNSIGNED_INT, m_localBuffer);
//	glBindTexture(GL_TEXTURE_2D, 0);
//	if (m_localBuffer) {
//		stbi_image_free(m_localBuffer);
//	}
//}
//Texture::~Texture() {
//	glDeleteTextures(1,&m_RenderId);
//}
//void Texture::bind(unsigned int slot) {
//	//There are 32 textures(o->31) total and we are only using 0th and slot is use if we want different texture to 
//	//load
//	glActiveTexture(GL_TEXTURE0+slot);
//	glBindTexture(GL_TEXTURE_2D, m_RenderId);
//}
//void Texture::unbind() {
//	glBindTexture(GL_TEXTURE_2D, 0);
//
//}

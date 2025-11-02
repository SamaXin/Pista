#pragma once
#include <string>
using namespace std;
class Shader {
private:
	string vertexCode, fragmentCode;
	bool fileOpen;
	unsigned int m_RenderId;
public:
	Shader(const string &vertexPath, const string &fragmentPath);
	~Shader();

	void bind();
	void unbind();
	bool ReadShader(const string& vertexPath, const string& fragmentPath);
	unsigned int CompileShader(unsigned int type, const string& shader);
	unsigned int CreateShader(const string& vertexShader, const string& fragmentShader);

	unsigned int getId() { return m_RenderId; }
	bool fileStatus() { return fileOpen; }
	const string vertexShader() { return vertexCode; }
	const string fragmentShader() { return fragmentCode; }


};
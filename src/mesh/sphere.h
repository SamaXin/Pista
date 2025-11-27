#pragma once
#include <glad/glad.h>
#include "./../../external/glfw/include/GLFW/glfw3.h"

#include "./../../external/glm/glm.hpp"
#include "./../../external/glm/gtc/matrix_transform.hpp"
#include "./../../external/glm/gtc/type_ptr.hpp"
#include "./../../external/glm/gtc/constants.hpp"

#include <iostream>
using namespace std;

class sphere {
private:
	unsigned int total;
	float slices;
	float radius;
	std::vector<float>data;
	std::vector<std::vector<float>>interleaved;
	glm::vec3 center;
public:
	sphere(unsigned int& total, float& slices, float& radius);

	void calVertices();
	void calCenter();

	//getter functions
	std::vector<float>getInterleaved();
	glm::vec3 getCenter();
};
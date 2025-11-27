#include <iostream>
#include <glad/glad.h>
#include "./../../external/glfw/include/GLFW/glfw3.h"
#include <vector>
#include <cmath>
#include "./../../external/glm/glm.hpp"
#include "./../../external/glm/gtc/matrix_transform.hpp"
#include "./../../external/glm/gtc/type_ptr.hpp"
#include "./../../external/glm/gtc/constants.hpp"
#include "sphere.h"
using namespace std;

//static std::vector<float>data;
//static std::vector<std::vector<float>>interleaved;
//static glm::vec3 center;

sphere::sphere(unsigned int &total, float &slices, float &radius):
total(total),slices(slices),radius(radius){
    calVertices();
    calCenter();
}


void sphere::calVertices() {
    interleaved.clear();
   for (int i = 0; i <= total; i++) {
       float longitude0 = glm::two_pi<float>() * ((float)i / slices);
       float longitude1 = glm::two_pi<float>() * ((float)(i + 1) / slices);
       for (int j = 0; j <= total; j++) {
           float latitude0 = glm::pi<float>() * ((float)j / total - 0.5f);
           float latitude1 = glm::pi<float>() * ((float)(j + 1) / total - 0.5f);

           glm::vec3 p0 = glm::vec3(radius * cos(latitude0) * sin(longitude0),
                                    radius * sin(latitude0) * sin(longitude0),
                                    radius * cos(longitude0));

           glm::vec3 p1 = glm::vec3(radius * cos(latitude1) * sin(longitude0),
                                    radius * sin(latitude1) * sin(longitude0),
                                    radius * cos(longitude0));

           glm::vec3 p2 = glm::vec3(radius * cos(latitude0) * sin(longitude1),
                                    radius * sin(latitude0) * sin(longitude1),
                                    radius * cos(longitude1));

           glm::vec3 p3 = glm::vec3(radius * cos(latitude1) * sin(longitude1),
                                    radius * sin(latitude1) * sin(longitude1),
                                    radius * cos(longitude1));

           // Making of Interleaved vector
           

           // Tri 1
           glm::vec3 nor = glm::normalize(p0);
           std::vector<float> tempInterleaved = {p0.x, p0.y, p0.z, nor.x, nor.y, nor.z};
           interleaved.push_back(tempInterleaved);
           
           nor = glm::normalize(p1);
           tempInterleaved = { p1.x, p1.y, p1.z, nor.x, nor.y, nor.z };
           interleaved.push_back(tempInterleaved);
          
           nor = glm::normalize(p2);
           tempInterleaved = { p2.x, p2.y, p2.z, nor.x, nor.y, nor.z };
           interleaved.push_back(tempInterleaved);


           // Tri 2
           nor = glm::normalize(p1);
           tempInterleaved = { p1.x, p1.y, p1.z, nor.x, nor.y, nor.z };
           interleaved.push_back(tempInterleaved);

           nor = glm::normalize(p2);
           tempInterleaved = { p2.x, p2.y, p2.z, nor.x, nor.y, nor.z };
           interleaved.push_back(tempInterleaved);

           nor = glm::normalize(p3);
           tempInterleaved = { p3.x, p3.y, p3.z, nor.x, nor.y, nor.z };
           interleaved.push_back(tempInterleaved);
       }
   }
}
void sphere::calCenter(){
    center = glm::vec3(0.0f, 0.0f, 0.0f);
    for (auto &v : interleaved){
        center.x += v[0];
        center.y += v[1];
        center.z += v[2];
    }
    center.x /= interleaved.size();
    center.y /= interleaved.size();
    center.z /= interleaved.size();
}


glm::vec3 sphere::getCenter() { return center; }
std::vector<float> sphere::getInterleaved() { 
    data.clear();
    data.reserve(interleaved.size() * 6);

    for (auto &v : interleaved) {
        data.insert(data.end(), v.begin(), v.end());
    }
    return data;
}


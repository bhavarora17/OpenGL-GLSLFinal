#include <GL/glew.h> 
#include <GL/glut.h> 
#include <GL/gl.h> 
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <stack> 
#include <math.h> 

#include<glm/glm.hpp> 
#include<glm/gtx/transform.hpp> 
#include "glm/gtx/string_cast.hpp"
#include<iostream>
#include <glm/gtc/type_ptr.hpp>	


#ifndef _SPHERE_H
#define _SPHERE_H

class Sphere{
public:
	const float PI = 3.14159265358979323846f;

struct Vertex{
	float xyzw[4];
	float color[4];
	float normal[4];
}vertex;

std::vector<Vertex> vertices;
std::vector<GLuint> index;

GLuint vboHandleSphere[1];   // a VBO that contains interleaved positions and colors 
GLuint indexVBOSphere;


GLuint *indices;
int indicesTotal;



int nIndices;

void InitSphere(const float radius, const unsigned int stacks, const unsigned int slices, float r, float g, float b);
void draw();
void InitVBOSphere(int nslices, int nstacks);
//void MouseFunc(int button, int state, int x, int y);
//void mouseMotion(int x, int y);
std::vector<Vertex> getVertices();
std::vector<GLuint> getIndices();

}s;


#endif _SPHERE_H
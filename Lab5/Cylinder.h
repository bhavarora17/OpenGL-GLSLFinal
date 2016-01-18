#include <GL/glew.h> 
#include <GL/glut.h> 
#include <GL/gl.h> 
#include<glm/glm.hpp>
#include<glm/gtx/transform.hpp>
#include <stdio.h>
#include <stdlib.h>
#include<math.h>
#include<iostream>


#ifndef _CYLINDER_H
#define _CYLINDER_H

class Cylinder{
	public:
	typedef struct
	{
		float location[4];
		float normal[4];
		float color[4];
	} Vertex;

	int nindices;
	Vertex *cyverts;   // cylinder vertices
	GLuint *cindices;

	GLuint vboHandle[1];   // a VBO that contains interleaved positions and colors 
	GLuint indexVBO;

	/////////////////////////////////
	float M_PI1 = 22 / 7.0;
	////////////////////////////////////////////////////////////////////////////////////

	void InitCylinder(int nslices, int nstacks, float r, float g, float b, float* m, float color[3], GLuint c0, GLuint c1, GLuint c2, GLuint m1);
	void InitCylVBO(int nslices, int nstacks);
	//void mymouse(int button, int state, int x, int y);
	//void mymotion(int x, int y);
	void mykey(unsigned char key, int x, int y);
	Vertex* getCylinderVertices();
	GLuint* getCylinderIndex();
	void drawCylinder();
	void bindCylinder();

}c;


#endif _CYLINDER_H
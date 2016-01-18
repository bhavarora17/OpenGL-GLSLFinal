#include <GL/glew.h> 
#include <GL/glut.h> 
#include <GL/gl.h> 
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <stack> 
#include <math.h> 
#include "Cylinder.h"
#include "Sphere.h"
#include "MazeGenerator.h"

#include<glm/glm.hpp> 
#include<glm/gtx/transform.hpp> 
#include "glm/gtx/string_cast.hpp"
#include<iostream>
#include <glm/gtc/type_ptr.hpp>	


#ifndef _LAB3ROBOT_H
#define _LAB3ROBOT_H


class Robot{
public:

	float color[4];

	float angle1 = 0, angle2 = 0;
	float angle3 = 0, angle4 = 0;
	int count1 = 0, count2 = 0, count3 = 0, count4 = 0;
	struct BaseStructure
	{
		//float vertices[];
		float x, y, z, w;        //Vertex
		//float nx, ny, nz;     //Normal
		//float s0, t0;         //Texcoord0
	};

	int xform_mode = 0;
#define XFORM_NONE    0 
#define XFORM_ROTATE  1
#define XFORM_SCALE 2 

	int press_x, press_y;
	int release_x, release_y;
	float x_angle = 0.0;
	float y_angle = 0.0;
	float scale_size = 1;
	float M_PI = 22 / 7.0;

	float rr = 0.1, g = 0.1, b = 0.1;

	int width;
	int height;

	GLubyte tindices[6];

	GLuint vboHandleCube[1];   // a VBO that contains interleaved positions and colors 
	GLuint indexVBOCube;
	int nslices=15, nstacks=15;

	
	glm::mat4 modelMR = glm::mat4(1.0f);
	std::stack<glm::mat4> mat_stack;
	
	void loop();
	void draw(glm::mat4 &local2clip, glm::mat4 &local2eye, glm::mat4 &world2eye,
		float color[3], GLuint c0, GLuint c1, GLuint c2, GLuint m1,
		GLuint m2, GLuint m3, GLuint m4);
	void InitVBOCube();
	void drawCube(glm::mat4 &local2clip, glm::mat4 &local2eye, glm::mat4 &world2eye,
		float color[3], GLuint c0, GLuint c1, GLuint c2, GLuint m1,
		GLuint m2, GLuint m3, GLuint m4); //, glm::mat4& view);
	//void displayRobot();
	//void keys(unsigned char key, int x, int y);
	void initializeGlut(int argc, char** argv);
	void rememberParent(glm::mat4 &ModelMR);
	glm::mat4 getParentMatrix();
	void forgetParent();
	void keys1(unsigned char key, int x, int y);
	//void mymotion(int x, int y);
	//void mymouse(int button, int state, int x, int y);
}r;


#endif _LAB3ROBOT_H
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <math.h>
#include<glm/glm.hpp>
#include<glm/gtx/transform.hpp>

#include <GL/glew.h> 
#include <GL/glut.h> 
#include <GL/gl.h> 


#include "ply.h"


#ifndef _PLYREAD_H
#define _PLYREAD_H


class Model{
public:

	typedef struct Vertex {
		float x, y, z;
		float nx, ny, nz;
	} Vertex;

	typedef struct Face {
		unsigned int count;
		unsigned int *vertices;
		float nx, ny, nz;
	} Face;

	


	struct model{
		float xyzw[4];
		float normal[4];
		float color[4];
	}model1;


	float cx, cy, cz;
	float x_min, x_max, y_min, y_max, z_min, z_max;

	Vertex** vertices = 0;
	Face** faces = 0;
	unsigned int vertexcount;
	unsigned int facecount;
	int vertexnormals = 0;
	int facenormals = 0;

	GLuint vboHandleModel[1];   // a VBO that contains interleaved positions and colors 
	GLuint indexVBOModel;

	///////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////
	//

	model *ply_verts;

	int ply_nindices;
	GLuint *ply_indices;




	void InitPly(float min[3], float max[3]);

	void drawModel(glm::mat4 &local2clip, glm::mat4 &local2eye, glm::mat4 &world2eye,
		float color[3], GLuint c0, GLuint c1, GLuint c2, GLuint m1,
		GLuint m2, GLuint m3, GLuint m4);


	void store_ply(PlyFile* input, Vertex ***vertices, Face ***faces,
		unsigned int* vertexcount, unsigned int* facecount,
		int* vertexnormals, int* facenormals);

	void find_center(float& cx, float& cy, float& cz,
		float& minx, float& maxx, float&miny,
		float &maxy, float &minz, float & maxz);

	void plyInit();

}obj;



#endif _LAB3ROBOT_H
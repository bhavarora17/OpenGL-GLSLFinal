#include "Cylinder.h"


void Cylinder::InitCylinder(int nslices, int nstacks, float r, float g, float b, float* m, float color[3], GLuint c0, GLuint c1, GLuint c2, GLuint m1)
{
	int nvertices = nslices * nstacks;
	cyverts = new Vertex[nvertices];

	float Dangle = 2 * M_PI1 / (float)(nslices - 1);

	for (int j = 0; j<nstacks; j++)
	for (int i = 0; i<nslices; i++) {
		int idx = j*nslices + i; // mesh[j][i] 
		float angle = Dangle * i;
		cyverts[idx].location[0] = cyverts[idx].normal[0] = cos(angle);
		cyverts[idx].location[1] = cyverts[idx].normal[1] = sin(angle);
		cyverts[idx].location[2] = j*1.0 / (float)(nstacks - 1);
		cyverts[idx].normal[2] = 0.0;
		cyverts[idx].location[3] = 1.0;  cyverts[idx].normal[3] = 0.0;
		cyverts[idx].color[0] = r; cyverts[idx].color[1] = g; cyverts[idx].color[2] = b;
		cyverts[idx].color[3] = 1.0;
	}
	// now create the index array 

	nindices = (nstacks - 1) * 2 * (nslices + 1);
	cindices = new GLuint[nindices];
	int n = 0;
	for (int j = 0; j<nstacks - 1; j++)
	for (int i = 0; i <= nslices; i++) {
		int mi = i % nslices;
		int idx = j*nslices + mi; // mesh[j][mi] 
		int idx2 = (j + 1) * nslices + mi;
		cindices[n++] = idx;
		cindices[n++] = idx2;
	}
}
 
void Cylinder::InitCylVBO(int nslices, int nstacks)
{
	int nvertices = nslices * nstacks;
	nindices = (nstacks - 1) * 2 * (nslices + 1);

	glGenBuffers(1, vboHandle);   // create an interleaved VBO object
	glBindBuffer(GL_ARRAY_BUFFER, vboHandle[0]);   // bind the first handle 

	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*nvertices, cyverts, GL_STATIC_DRAW); // allocate space and copy the position data over
	glBindBuffer(GL_ARRAY_BUFFER, 0);   // clean up 

	glGenBuffers(1, &indexVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*nindices, cindices, GL_STATIC_DRAW);  // load the index data 

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);  // clean up 

	// by now, we moved the position and color data over to the graphics card. There will be no redundant data copy at drawing time 
}

Cylinder::Vertex* Cylinder::getCylinderVertices(){
	return cyverts;
}

GLuint* Cylinder::getCylinderIndex(){
	return cindices;
}


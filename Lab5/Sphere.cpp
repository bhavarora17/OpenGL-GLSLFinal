#include "Sphere.h"

void Sphere::InitSphere(const float radius, const unsigned int stacks, const unsigned int slices, float r, float g, float b){
	for(unsigned int stackNumber = 0; stackNumber <= stacks; ++stackNumber)
	{
		for (unsigned int sliceNumber = 0; sliceNumber < slices; ++sliceNumber)
		{
			float theta = stackNumber * PI / (stacks);

			float phi = sliceNumber * 2 * PI / slices;
			float sinTheta = std::sin(theta);
			float sinPhi = std::sin(phi);
			float cosTheta = std::cos(theta);
			float cosPhi = std::cos(phi);
			vertex.normal[0]=vertex.xyzw[0] = radius * cosPhi * sinTheta;
			vertex.normal[1]=vertex.xyzw[1] = radius * sinPhi * sinTheta;
			vertex.normal[2]=vertex.xyzw[2] = radius * cosTheta;
			vertex.xyzw[3] = 1.0;
			vertex.normal[3] = 0.0;
			
			//vertex.xyzw[3] = 0.0f;
			vertex.color[0] = r; vertex.color[1] = g; vertex.color[2] = b;
			vertex.color[3] = 1.0;
			vertices.push_back(vertex);
		}
	}
	int n = 0;

	for (unsigned int stackNumber = 0; stackNumber < stacks; ++stackNumber)
	{	
		for (unsigned int sliceNumber = 0; sliceNumber <= slices; ++sliceNumber)
		{
			index.push_back((stackNumber * slices) + (sliceNumber % slices));
			index.push_back(((stackNumber + 1) * slices) + (sliceNumber % slices));
		}
	}	
	std::cout << index.size();
}




void Sphere::InitVBOSphere(int nslices, int nstacks){

	int nvertices = nslices * (nstacks+1);

	glGenBuffers(1, vboHandleSphere);   // create an interleaved VBO object
	glBindBuffer(GL_ARRAY_BUFFER, vboHandleSphere[0]);   // bind the first handle 

	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*nvertices, &vertices[0], GL_STATIC_DRAW); // allocate space and copy the position data over 
	glBindBuffer(GL_ARRAY_BUFFER, 0);   // clean up 

	glGenBuffers(1, &indexVBOSphere);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVBOSphere);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*index.size(), &index[0], GL_STATIC_DRAW);  // load the index data 

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);  // clean up 

}



std::vector<Sphere::Vertex> Sphere::getVertices(){
	return (s.vertices);
}


std::vector<GLuint> Sphere::getIndices(){
	return s.index;
}

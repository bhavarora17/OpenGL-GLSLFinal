#include "Lab3Robot.h"

Robot::BaseStructure baseSquare[] = { -0.05f, -0.05f, -0.05f, 1.0f, 
-1, 0, 0, 0,

-0.05f, -0.05f, 0.05f, 1.0f,
-1, 0, 0, 0,

-0.05f, 0.05f, 0.05f, 1.0f,
-1, 0, 0, 0,




0.05f, 0.05f, -0.05f, 1.0f,
0, 0, -1, 0,

-0.05f, -0.05f, -0.05f, 1.0f,
0, 0, -1, 0,

-0.05f, 0.05f, -0.05f, 1.0f,
0, 0, -1, 0,



0.05f, -0.05f, 0.05f, 1.0f,
0, -1, 0, 0,

-0.05f, -0.05f, -0.05f, 1.0f,
0, -1, 0, 0,
0.05f, -0.05f, -0.05f, 1.0f,
0,-1,0,0,



0.05f, 0.05f, -0.05f, 1.0f,
0, 0, -1, 0,

0.05f, -0.05f, -0.05f, 1.0f,
0, 0, -1, 0,

-0.05f, -0.05f, -0.05f, 1.0f,
0, 0, -1, 0,



-0.05f, -0.05f, -0.05f, 1.0f,
-1, 0, 0, 0,

-0.05f, 0.05f, 0.05f, 1.0f,
-1, 0, 0, 0,

-0.05f, 0.05f, -0.05f, 1.0f,
-1, 0, 0, 0,




0.05f, -0.05f, 0.05f, 1.0f,
0, -1, 0, 0,

-0.05f, -0.05f, 0.05f, 1.0f,
0, -1, 0, 0,

-0.05f, -0.05f, -0.05f, 1.0f,
0, -1, 0, 0,




-0.05f, 0.05f, 0.05f, 1.0f,
0, 0, 1, 0,

-0.05f, -0.05f, 0.05f, 1.0f,
0, 0, 1, 0,

0.05f, -0.05f, 0.05f, 1.0f,
0, 0, 1, 0,



0.05f, 0.05f, 0.05f, 1.0f,
1, 0, 0, 0,

0.05f, -0.05f, -0.05f, 1.0f,
1, 0, 0, 0,

0.05f, 0.05f, -0.05f, 1.0f,
1, 0, 0, 0,




0.05f, -0.05f, -0.05f, 1.0f,
1, 0, 0, 0,

0.05f, 0.05f, 0.05f, 1.0f,
1, 0, 0, 0,

0.05f, -0.05f, 0.05f, 1.0f,
1, 0, 0, 0,




0.05f, 0.05f, 0.05f, 1.0f,
1, 0, 0, 0,

0.05f, 0.05f, -0.05f, 1.0f,
1, 0, 0, 0,

-0.05f, 0.05f, -0.05f, 1.0f,
1, 0, 0, 0,



0.05f, 0.05f, 0.05f, 1.0f,
1, 0, 0, 0,

-0.05f, 0.05f, -0.05f, 1.0f,
1, 0, 0, 0,

-0.05f, 0.05f, 0.05f, 1.0f,
1, 0, 0, 0,



0.05f, 0.05f, 0.05f, 1.0f,
0, 0, 1, 0,

-0.05f, 0.05f, 0.05f, 1.0f,
0, 0, 1,0,


0.05f, -0.05f, 0.05f, 1.0f,
0, 0, 1,0
}; 

	void Robot::InitVBOCube()
	{

		GLenum err = glewInit();

		if (err != GLEW_OK) {
			fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
			//return -1;
		}

		glGenBuffers(1, r.Robot::vboHandleCube);   // create an interleaved VBO object
		glBindBuffer(GL_ARRAY_BUFFER, r.Robot::vboHandleCube[0]);   // bind the first handle 
		glBufferData(GL_ARRAY_BUFFER, sizeof(float)* 288, &baseSquare[0].x, GL_STATIC_DRAW); // allocate space and copy the position data over
		glBindBuffer(GL_ARRAY_BUFFER, 0);   // clean up 

	}

	void Robot::drawCube(glm::mat4 &local2clip, glm::mat4 &local2eye, glm::mat4 &world2eye,
		float color[3], GLuint c0, GLuint c1, GLuint c2, GLuint m1,
		GLuint m2, GLuint m3, GLuint m4){
		

		//glLoadMatrixf(&m[0][0]);
		glColor3f(rr, g, b);

		//	glVertexPointer(4, GL_FLOAT, 0, 0);
		glVertexAttribPointer(c0, 4, GL_FLOAT, GL_FALSE, 32, (char*)NULL + 0);
		glVertexAttribPointer(c1, 4, GL_FLOAT, GL_FALSE, 32, (char*)NULL + 0);
		glVertexAttribPointer(c2, 4, GL_FLOAT, GL_FALSE, 32, (char*)NULL + 16);

		glm::mat4 normal_matrix = glm::inverse(local2eye);
		normal_matrix = glm::transpose(normal_matrix);

		glUniformMatrix4fv(m1, 1, GL_FALSE, &local2clip[0][0]);
		glUniformMatrix4fv(m2, 1, GL_FALSE, &local2eye[0][0]);   // pass the local2eye matrix
		glUniformMatrix4fv(m3, 1, GL_FALSE, &normal_matrix[0][0]);   // pass the local2eye matrix
		glUniformMatrix4fv(m4, 1, GL_FALSE, &world2eye[0][0]);   // pass the local2eye matrix

		glDrawArrays(GL_TRIANGLES, 0, 12 * 4);
	}


	void Robot::rememberParent(glm::mat4 &ModelMR){
		mat_stack.push(modelMR);
	}

	glm::mat4 Robot::getParentMatrix(){
		return mat_stack.top();
	}

	void Robot::forgetParent(){
		mat_stack.pop();
	}

	void Robot::draw(glm::mat4 &local2clip, glm::mat4 &local2eye, glm::mat4 &world2eye,
		float color[3], GLuint c0, GLuint c1, GLuint c2, GLuint m1,
		GLuint m2, GLuint m3, GLuint m4){


//		float *model1 = &model[0][0];
		float angleRR = (3.141592653589793238463 / 180) * 90;


		/////////////////////////////////////////BODY/////////////////////////////	

		rememberParent(modelMR);
		

		glBindBuffer(GL_ARRAY_BUFFER, c.vboHandle[0]);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, c.indexVBO);
		
		modelMR = glm::translate(modelMR, glm::vec3(0.0f, -0.25f, 0.0f));
		float ang= 270 * (22 / 7.0) / 180.0;
		
		glVertexAttribPointer(c0, 4, GL_FLOAT, GL_FALSE, 48, (char*)NULL + 0);
		glVertexAttribPointer(c1, 4, GL_FLOAT, GL_FALSE, 48, (char*)NULL + 32);
		glVertexAttribPointer(c2, 4, GL_FLOAT, GL_FALSE, 48, (char*)NULL + 16);

		modelMR = glm::rotate(modelMR, ang,glm::vec3(1.0, 0.0, 0.0));

		
		modelMR = glm::scale(modelMR, glm::vec3(0.1f, 0.1f, 0.5f));

		glm::mat4 local2eyeV = local2eye*modelMR;
		modelMR = local2clip*modelMR;

		glm::mat4 normal_matrix = glm::inverse(local2eyeV);
		normal_matrix = glm::transpose(normal_matrix);

		
		glUniformMatrix4fv(m1, 1, GL_FALSE, &modelMR[0][0]);
		glUniformMatrix4fv(m2, 1, GL_FALSE, &local2eyeV[0][0]);   // pass the local2eye matrix
		glUniformMatrix4fv(m3, 1, GL_FALSE, &normal_matrix[0][0]);   // pass the local2eye matrix
		glUniformMatrix4fv(m4, 1, GL_FALSE, &world2eye[0][0]);   // pass the local2eye matrix

		
		glDrawElements(GL_TRIANGLE_STRIP, c.nindices, GL_UNSIGNED_INT, (char*)NULL + 0);

		
		modelMR = getParentMatrix();
		forgetParent();

		////////////////////////////////////Face//////////////////////////

		rememberParent(modelMR);
		modelMR = glm::translate(modelMR, glm::vec3(0.0, .31f, 0.0f));
		//std::cout << glm::to_string(modelMR[0]) << std::endl << glm::to_string(modelMR[1]) << std::endl << glm::to_string(modelMR[2]) << std::endl << glm::to_string(modelMR[3]) << std::endl;
		
		
		
		//drawCube(r.Robot::modelMR);
		glBindBuffer(GL_ARRAY_BUFFER, s.vboHandleSphere[0]);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s.indexVBOSphere);


		modelMR = glm::scale(modelMR, glm::vec3(0.3f, 0.3f, 0.3f));
		//modelMR = glm::translate(glm::vec3(0.5f, 0.5f, 0.3f));
		//modelMR = glm::scale(modelMR, glm::vec3(2.0f, 2.0f, 2.0f));
		
		local2eyeV = local2eye*modelMR;
		modelMR = local2clip*modelMR;
//		glLoadMatrixf(&modelMR[0][0]);
		
		normal_matrix = glm::inverse(local2eye);
		normal_matrix = glm::transpose(normal_matrix);

		glVertexAttribPointer(c0, 4, GL_FLOAT, GL_FALSE, 48, (char*)NULL + 0);
		glVertexAttribPointer(c1, 4, GL_FLOAT, GL_FALSE, sizeof(Sphere::Vertex), (char*)NULL + 16);
		glVertexAttribPointer(c2, 4, GL_FLOAT, GL_FALSE, sizeof(Sphere::Vertex), (char*)NULL + 32);

		glUniformMatrix4fv(m1, 1, GL_FALSE, &modelMR[0][0]);
		glUniformMatrix4fv(m2, 1, GL_FALSE, &local2eyeV[0][0]);   // pass the local2eye matrix
		glUniformMatrix4fv(m3, 1, GL_FALSE, &normal_matrix[0][0]);   // pass the local2eye matrix
		glUniformMatrix4fv(m4, 1, GL_FALSE, &world2eye[0][0]);   // pass the local2eye matrix

		
		glDrawElements(GL_TRIANGLE_STRIP, s.index.size(), GL_UNSIGNED_INT, (char*)NULL + 0);


		modelMR = getParentMatrix();
		forgetParent();


		
		glBindBuffer(GL_ARRAY_BUFFER, vboHandleCube[0]);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVBOCube);

	


		//////////////////////////////////left leg////////////////////////////////
		rememberParent(modelMR);
		modelMR = glm::translate(modelMR, glm::vec3(-.05, -0.36, 0.0f));
		modelMR = glm::rotate(modelMR, -angle1, glm::vec3(1.0f, 1.0f, 0.0f));


		rememberParent(modelMR);
		modelMR = glm::scale(modelMR, glm::vec3(0.9, 2, 1));
		//std::cout << glm::to_string(modelMR[0]) << std::endl << glm::to_string(modelMR[1]) << std::endl << glm::to_string(modelMR[2]) << std::endl << glm::to_string(modelMR[3]) << std::endl;
		
		local2eyeV = local2eye*modelMR;
		modelMR = local2clip*modelMR;
		////glLoadMatrixf(&modelMR[0][0]);
		//glLoadMatrixf(&modelMR[0][0]);


		drawCube(modelMR, local2eyeV, world2eye, color, c0, c1, c2, m1, m2, m3, m4);


		modelMR = getParentMatrix();
		

		modelMR = glm::translate(modelMR, glm::vec3(0, -0.21, 0.0f));
		modelMR = glm::rotate(modelMR, -angle2, glm::vec3(1.0f, 0.0f, 0.0f));
		

		rememberParent(modelMR);
		
		modelMR = glm::scale(modelMR, glm::vec3(0.9, 2, 1));
		
		local2eyeV = local2eye*modelMR;
		modelMR = local2clip*modelMR;
		////glLoadMatrixf(&modelMR[0][0]);
		//glLoadMatrixf(&modelMR[0][0]);

		
		
		drawCube(modelMR, local2eyeV, world2eye, color, c0, c1, c2, m1, m2, m3, m4);
		

		///left foot/////////////////////////////////

		modelMR = getParentMatrix();
		modelMR = glm::translate(modelMR, glm::vec3(-0.06,- 0.17, 0.0f));
		modelMR = glm::rotate(modelMR, -angle2, glm::vec3(1.0f, 0.0f, 0.0f));
		
		local2eyeV = local2eye*modelMR;
		modelMR = local2clip*modelMR;

		modelMR = glm::scale(modelMR, glm::vec3(2, 1, 1));


		drawCube(modelMR, local2eyeV, world2eye, color, c0, c1, c2, m1, m2, m3, m4);

		forgetParent();
		forgetParent();
		////////////////////////////////right leg///////////////////////////////
		modelMR = getParentMatrix();
	//	rememberParent(modelMR);
		modelMR = glm::translate(modelMR, glm::vec3(.05, -.36f, 0.0f));


		modelMR = glm::rotate(modelMR, angle3, glm::vec3(-1.0f, 1.0f, 0.0f));

		rememberParent(modelMR);
		modelMR = glm::scale(modelMR, glm::vec3(0.9, 2, 1));
		//std::cout << glm::to_string(modelMR[0]) << std::endl << glm::to_string(modelMR[1]) << std::endl << glm::to_string(modelMR[2]) << std::endl << glm::to_string(modelMR[3]) << std::endl;
		
		local2eyeV = local2eye*modelMR;
		modelMR = local2clip*modelMR;
		//glLoadMatrixf(&modelMR[0][0]);
//		glLoadMatrixf(&modelMR[0][0]);

		
	

		drawCube(modelMR, local2eyeV, world2eye, color, c0, c1, c2, m1, m2, m3, m4);


		modelMR = getParentMatrix();
		//mat_stack.pop();
		//rememberParent(modelMR);

		modelMR = glm::translate(modelMR, glm::vec3(0, -0.21, 0.0f));
		modelMR = glm::rotate(modelMR, angle4, glm::vec3(-1.0f, 0.0f, 0.0f));
		rememberParent(modelMR);
		

		local2eyeV = local2eye*modelMR;
		modelMR = local2clip*modelMR;
		modelMR = glm::scale(modelMR, glm::vec3(0.9, 2, 1));
		

		drawCube(modelMR, local2eyeV, world2eye, color, c0, c1, c2, m1, m2, m3, m4);
		

		///////////////////////////////////////////////////////////
		////right foot

		modelMR = getParentMatrix();
		modelMR = glm::translate(modelMR, glm::vec3(0.06, -0.17, 0.0f));
		modelMR = glm::rotate(modelMR, -angle2, glm::vec3(1.0f, 0.0f, 0.0f));
		modelMR = glm::scale(modelMR, glm::vec3(2, 1, 1));

		local2eyeV = local2eye*modelMR;
		modelMR = local2clip*modelMR;
		//glLoadMatrixf(&modelMR[0][0]);
	//	glLoadMatrixf(&modelMR[0][0]);


	

		drawCube(modelMR, local2eyeV, world2eye, color, c0, c1, c2, m1, m2, m3, m4);


		forgetParent();
		forgetParent();
		//forgetParent();




		///////////////////////////////////HANDS///////////////////////////

		//////////////////LEFT/////////////////////////

		modelMR = getParentMatrix();
		//rememberParent(modelMR);
		modelMR = glm::translate(modelMR, glm::vec3(-.21, 0.16, 0.0f));
		modelMR = glm::rotate(modelMR, angle3, glm::vec3(-1.0f, 1.0f, 0.0f));

		rememberParent(modelMR);
		modelMR = glm::scale(modelMR, glm::vec3(0.9, 2, 1));

		local2eyeV = local2eye*modelMR;
		modelMR = local2clip*modelMR;
		glLoadMatrixf(&modelMR[0][0]);


		drawCube(modelMR, local2eyeV, world2eye, color, c0, c1, c2, m1, m2, m3, m4);


		modelMR = getParentMatrix();

		modelMR = glm::translate(modelMR, glm::vec3(0, -0.21, 0.0f));
		modelMR = glm::rotate(modelMR, angle4, glm::vec3(-1.0f, 0.0f, 0.0f));
		modelMR = glm::scale(modelMR, glm::vec3(0.9, 2, 1));

		local2eyeV = local2eye*modelMR;
		modelMR = local2clip*modelMR;

		drawCube(modelMR, local2eyeV, world2eye, color, c0, c1, c2, m1, m2, m3, m4);



		forgetParent();
		modelMR = getParentMatrix();
		forgetParent();


		////////////////RIGHT///////////////

		
		rememberParent(modelMR);
		modelMR = glm::translate(modelMR, glm::vec3(+.21, 0.16, 0.0f));
		modelMR = glm::rotate(modelMR, -angle1, glm::vec3(1.0f, 1.0f, 0.0f));

		rememberParent(modelMR);
		modelMR = glm::scale(modelMR, glm::vec3(0.9, 2, 1));

		local2eye = local2eye*modelMR;
		modelMR = local2clip*modelMR;
		//glLoadMatrixf(&modelMR[0][0]);

		

		drawCube(modelMR, local2eye, world2eye, color, c0, c1, c2, m1, m2, m3, m4);


		modelMR = getParentMatrix();

		modelMR = glm::translate(modelMR, glm::vec3(0, -0.21, 0.0f));
		modelMR = glm::rotate(modelMR, -angle2, glm::vec3(1.0f, 0.0f, 0.0f));
		
		local2eye = local2eye*modelMR;
		modelMR = local2clip*modelMR;

		modelMR = glm::scale(modelMR, glm::vec3(0.9, 2, 1));
		
		////glLoadMatrixf(&modelMR[0][0]);
		//glLoadMatrixf(&modelMR[0][0]);


		drawCube(modelMR, local2eye, world2eye, color, c0, c1, c2, m1, m2, m3, m4);

		forgetParent();
		modelMR = getParentMatrix();
		forgetParent();
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);


		glutSwapBuffers();
		glFlush();

	}



	
	
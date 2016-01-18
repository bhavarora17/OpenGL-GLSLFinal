#define _CRT_SECURE_NO_WARNINGS


#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <stack> 
#include <math.h>
#include "plyread.h"
#include "MazeGenerator.h"
#include "Lab3Robot.h"

using namespace std;

#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#define M_PI 3.1415926

#include <glm/glm.hpp> 
#include <glm/gtx/transform.hpp>


vector<int> *abc;

GLuint programObject;
GLuint SetupGLSL(char*);


GLuint cubemap_texture;
GLuint cubemap_texture1;

GLuint skybox_texture;


float posx = 0.0f;
float posy = 0.0f;
float posz = 0.0f;


char fname[] = "stars1.ppm";
char fname1[] = "grassJpeg.ppm";
char fname2[] = "harry_potter.ppm";

char donkey_fur[] = "donkey_fur.ppm";

char sky1[] = "ft.ppm";//"bluefreeze_front.ppm";
char sky2[] = "bk.ppm";//"bluefreeze_back.ppm";
char sky3[] = "lf.ppm";//"bluefreeze_left.ppm";
char sky4[] = "rt.ppm";// "bluefreeze_right.ppm";
char sky5[] = "up.ppm";//"bluefreeze_top.ppm";
char sky6[] = "dn.ppm";//"bottomNew.ppm";


typedef struct
{
	float location[4];
	float normal[4];
	float color[4];
	float texCoord[2];
} Vertex;

GLubyte checkImage[256][256][4];
GLubyte readImage[400][400][4];
GLubyte texImage[256][256][4];
GLubyte gradientImage[256][256][4];

Vertex sqverts[4];
GLuint sqindices[6];
int sq_nindices = 6;

GLuint vboHandleSquare[2];   // a VBO that contains interleaved positions and colors 
GLuint indexVBOSquare[2];

struct BaseStructure
{

	float xyzw[4];
	float normal[4];
	float texCoord[2];

};

BaseStructure baseSquare[] = { -0.05f, -0.05f, -0.05f, 1.0f,
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
0, -1, 0, 0,



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
0, 0, 1, 0,


0.05f, -0.05f, 0.05f, 1.0f,
0, 0, 1, 0
};



/////////////////////////////////
// Define Light Properties -  Ia, Id, Is, and light position 
//////////////////////////////////

GLfloat light_ambient[4] = { 0.8, 0.8, 0.8, 1 };  //Ia 
GLfloat light_diffuse[4] = { 0.8, 0.8, 0.8, 1 };  //Id
GLfloat light_specular[4] = { 1, 1, 1, 1 };  //Is
GLfloat light_pos[4] = {-1.0, -3, 0.0, 1 };

////////////////////////////////
// Define Default Material Properties -  Ka, Kd, Ks, Shininess 
//////////////////////////////////

GLfloat mat_ambient[4] = { 0.2, 0.2, 0.2, 1 };  //Ka 
GLfloat mat_diffuse[4] = { 0.8, 0.8, 0.8, 1 };  //Kd
GLfloat mat_specular[4] = { 1, 1, 1, 1 };  //Ks
GLfloat mat_shine[1] = {3};


GLuint vboHandle[2];   // a VBO that contains interleaved positions and colors 
GLuint indexVBO[2];

float angle1 = 0, angle2 = 0;
float angle3 = 0, angle4 = 0;

glm::mat4 modelM = glm::mat4(1.0f);

stack<glm::mat4> mat_stack;

GLuint c0;
GLuint c1;
GLuint c2;
GLuint c3;

GLuint m1 ;
GLuint m2 ;
GLuint m3 ;
GLuint m4 ;
GLuint m5 ;

GLuint Ia ;
GLuint Id ;
GLuint Is ;
GLuint Lpos;

GLuint Ka ;
GLuint Kd;
GLuint Ks;
GLuint Shine ;

GLuint b1;

bool use_gradient = false;

/////////////////////////////////
// glut mouse control 
// 

int xform_mode = 0;
#define XFORM_NONE    0 
#define XFORM_ROTATE  1
#define XFORM_SCALE 2 

int press_x, press_y;
int release_x, release_y;
float z_angle = 0.0;
float x_angle = 0.0;
float scale_size = 1;

float color[3];

glm::mat4 mvp;
glm::mat4 mv;


//////////////////////////////////////////////////////////////


#define SetMaterialColor(d, r, g, b, a)  glUniform4f(d, r, g, b, a); 

/////////////////////////////////////////////////////////////



void InitCube_VBO()
{
	glGenBuffers(1, vboHandle);   // create an interleaved VBO object
	glBindBuffer(GL_ARRAY_BUFFER, vboHandle[0]);   // bind the first handle 
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)* 288, &baseSquare[0], GL_STATIC_DRAW); // allocate space and copy the position data over
	glBindBuffer(GL_ARRAY_BUFFER, 0);   // clean up 

}


void draw_cube(float* local2clip, float* local2eye, float* world2eye, float color[3], GLuint c0, GLuint c1,
	GLuint c2, GLuint m1, GLuint m2, GLuint m3, GLuint m4, GLuint m5) {

	glBindBuffer(GL_ARRAY_BUFFER, vboHandle[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVBO[0]);
	
	glVertexAttribPointer(c0, 4, GL_FLOAT, GL_FALSE, 32, (char*)NULL + 0);
	glVertexAttribPointer(c1, 4, GL_FLOAT, GL_FALSE, 32, (char*)NULL + 0);
	glVertexAttribPointer(c2, 4, GL_FLOAT, GL_FALSE, 32, (char*)NULL + 16); // normal 

	glm::mat4 eye2world = glm::inverse((glm::mat4)*world2eye);

	glm::mat4 normal_matrix = glm::inverse((glm::mat4)*local2eye);
	normal_matrix = glm::transpose(normal_matrix);

	glUniformMatrix4fv(m1, 1, GL_FALSE, (float*)local2clip);   // pass the local2clip matrix
	glUniformMatrix4fv(m2, 1, GL_FALSE, (float*)local2eye);   // pass the local2eye matrix
	glUniformMatrix4fv(m3, 1, GL_FALSE, (float*)&normal_matrix[0][0]);   // pass the local2eye matrix
	glUniformMatrix4fv(m4, 1, GL_FALSE, (float*)world2eye);   // pass the local2eye matrix
	//glUniformMatrix4fv(m5, 1, GL_FALSE, (float*)&eye2world[0][0]);   // pass the local2eye matrix
	glUniformMatrix4fv(m5, 1, GL_FALSE, (float*)world2eye);   // pass the local2eye matrix


	glDrawArrays(GL_TRIANGLES, 0, 12 * 4);
}

void read_Image(char* fname)
{
	//  FILE* in = fopen("normal.ppm", "r"); 
	//  FILE* in = fopen("rough.ppm", "r"); 
	//  FILE* in = fopen("brick.ppm", "r"); 
	//  FILE* in = fopen("earth.ppm", "r"); 

	FILE* in = fopen(fname, "r");

	int height, width, ccv;
	char header[100];
	fscanf(in, "%s %d %d %d", header, &width, &height, &ccv);

	printf("%s %d %d %d\n", header, width, height, ccv);
	int r, g, b;

	for (int i = height - 1; i >= 0; i--)
	for (int j = 0; j<width; j++)
	{
		fscanf(in, "%d %d %d", &r, &g, &b);
		readImage[i][j][0] = (GLubyte)r;
		readImage[i][j][1] = (GLubyte)g;
		readImage[i][j][2] = (GLubyte)b;
		readImage[i][j][3] = 255;
	}

	for (int i = 0; i<256; i++)
	for (int j = 0; j<256; j++) {
		if (i<height && j <width) {
			texImage[i][j][0] = readImage[i][j][0]; texImage[i][j][1] = readImage[i][j][1];
			texImage[i][j][2] = readImage[i][j][2];	texImage[i][j][3] = 255;
		}
		else {
			texImage[i][j][0] = 0; 	texImage[i][j][1] = 0; 	texImage[i][j][2] = 0;
			texImage[i][j][3] = 255;
		}
	}
	//////////////////////////////////
	// Use central difference to calculate the gradients 
	for (int i = 0; i<256; i++)
	for (int j = 0; j<256; j++) {
		gradientImage[i][j][0] = (unsigned char)((texImage[(i + 1) % 256][j][0] -
			texImage[(i - 1) % 256][j][0]) / 2.0 + 128);
		gradientImage[i][j][1] = (unsigned char)((texImage[i][(j + 1) % 256][0] -
			texImage[i][(j - 1) % 256][0]) / 2.0 + 128);
		gradientImage[i][j][2] = 20;
		gradientImage[i][j][3] = 255;
	}
	fclose(in);
}



void init_skybox()
{

	glEnable(GL_TEXTURE_CUBE_MAP);
	glGenTextures(1, &skybox_texture);
	printf("skybox_texture %d \n", &skybox_texture);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_CUBE_MAP, skybox_texture);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	//for (int i = 0; i<6; i++)
	//{
	int i = 0;
		read_Image(fname);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i++, 0, GL_RGBA, 256, 256, 0, GL_RGBA, GL_UNSIGNED_BYTE, texImage);

		read_Image(sky2);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i++, 0, GL_RGBA, 256, 256, 0, GL_RGBA, GL_UNSIGNED_BYTE, texImage);

		read_Image(sky3);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i++, 0, GL_RGBA, 256, 256, 0, GL_RGBA, GL_UNSIGNED_BYTE, texImage);

		read_Image(sky4);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i++, 0, GL_RGBA, 256, 256, 0, GL_RGBA, GL_UNSIGNED_BYTE, texImage);

		read_Image(sky5);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i++, 0, GL_RGBA, 256, 256, 0, GL_RGBA, GL_UNSIGNED_BYTE, texImage);

		read_Image(sky6);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i++, 0, GL_RGBA, 256, 256, 0, GL_RGBA, GL_UNSIGNED_BYTE, texImage);


	//}
}



void init_cubemap()
{
	

	glEnable(GL_TEXTURE_CUBE_MAP);
	glGenTextures(1, &cubemap_texture);
	printf("cubemap_texture %d \n", &cubemap_texture);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap_texture);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	read_Image(fname);
	for (int i = 0; i<6; i++)
	{
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, 256, 256, 0, GL_RGBA, GL_UNSIGNED_BYTE, texImage);
	}
}



void init_cubemap2()
{
	glEnable(GL_TEXTURE_CUBE_MAP);
	glGenTextures(1, &cubemap_texture1);
	printf("cubemap_texture %d \n", &cubemap_texture1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap_texture1);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	read_Image(fname1);
	for (int i = 0; i<6; i++)
	{
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, 256, 256, 0, GL_RGBA, GL_UNSIGNED_BYTE, texImage);
	}
}

void display()
{

	float angle123 = (3.141592653589793238463 / 180) * 90;

	glEnable(GL_DEPTH_TEST);
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	

	//glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	
	glUseProgram(programObject);

	c0 = glGetAttribLocation(programObject, "position");
	c1 = glGetAttribLocation(programObject, "color1");
	c2 = glGetAttribLocation(programObject, "normal");
	c3 = glGetAttribLocation(programObject, "texCoord");


	m1 = glGetUniformLocation(programObject, "local2clip");
	m2 = glGetUniformLocation(programObject, "local2eye");
	m3 = glGetUniformLocation(programObject, "normal_matrix");
	m4 = glGetUniformLocation(programObject, "world2eye");
	m5 = glGetUniformLocation(programObject, "eye2world");

	Ia = glGetUniformLocation(programObject, "light_ambient");
	Id = glGetUniformLocation(programObject, "light_diffuse");
	Is = glGetUniformLocation(programObject, "light_specular");
	Lpos = glGetUniformLocation(programObject, "light_pos");

	Ka = glGetUniformLocation(programObject, "mat_ambient");
	Kd = glGetUniformLocation(programObject, "mat_diffuse");
	Ks = glGetUniformLocation(programObject, "mat_specular");
	Shine = glGetUniformLocation(programObject, "mat_shine");

	b1 = glGetUniformLocation(programObject, "use_texture");

	int use_texture = 1;
	glUniform1i(b1, use_texture);

	glUniform4f(Ia, light_ambient[0], light_ambient[1], light_ambient[2], light_ambient[3]);
	glUniform4f(Id, light_diffuse[0], light_diffuse[1], light_diffuse[2], light_diffuse[3]);
	glUniform4f(Is, light_specular[0], light_specular[1], light_specular[2], light_specular[3]);
	glUniform4f(Lpos, light_pos[0], light_pos[1], light_pos[2], light_pos[3]);

	glUniform4f(Ka, mat_ambient[0], mat_ambient[1], mat_ambient[2], mat_ambient[3]);
	glUniform4f(Kd, mat_diffuse[0], mat_diffuse[1], mat_diffuse[2], mat_diffuse[3]);
	glUniform4f(Ks, mat_specular[0], mat_specular[1], mat_specular[2], mat_specular[3]);
	glUniform1f(Shine, mat_shine[0]);
	

	glBindBuffer(GL_ARRAY_BUFFER, vboHandleSquare[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVBOSquare[0]);

	glEnableVertexAttribArray(c0);
	glEnableVertexAttribArray(c1);
	glEnableVertexAttribArray(c2);
	glEnableVertexAttribArray(c3);

	glVertexAttribPointer(c0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (char*)NULL + 0);
	glVertexAttribPointer(c1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (char*)NULL + 16);
	glVertexAttribPointer(c2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (char*)NULL + 32);
	glVertexAttribPointer(c3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (char*)NULL + 48);



	// define/get the viewing matrix 
	glm::mat4 view = glm::lookAt(glm::vec3(-2.0+posx, -2+posy, 1.2+posz),
		glm::vec3(-0.0 + posx, -0.0 + posy, -0.0 + posz),
		glm::vec3(0.0, 0.0, 1.0));

	// define/get the projection matrix 
	glm::mat4 projection = glm::perspective(((float)M_PI/180.0f)*60.0f, 1.0f, .01f, 100.0f);

	// define the modeling matrix 
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::rotate(model, z_angle, glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::rotate(model, x_angle, glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(scale_size, scale_size, scale_size));

	
	color[0] = 1.0;   color[1] = 1.0;   color[2] = 0.0;
	mvp = projection*view*model;
	mv = view * model;

	//modelM = modelM * glm::mat4(2.0);
	mat_stack.push(modelM);

	////////////////////First////////////////////////BACK

	glm::mat4 normal_matrix = glm::inverse(mv);
	normal_matrix = glm::transpose(normal_matrix);

	//modelM = glm::rotate(180.0f*(22 / 7.0f) / 180.0f, glm::vec3(0.0f, 0.0f, 1.0f)); 
	modelM = glm::translate(modelM, glm::vec3(0.0f, -4.99999f, 0.0f));
	
	modelM = glm::scale(modelM, glm::vec3(10.0f,10.0f,10.0f));
	glm::mat4 mvp2 = mvp*modelM;
	glm::mat4 mv2 = mv*modelM;
	
	glUniformMatrix4fv(m1, 1, GL_FALSE, &mvp2[0][0]);
	glUniformMatrix4fv(m2, 1, GL_FALSE, &mv2[0][0]);
	glUniformMatrix4fv(m3, 1, GL_FALSE, &normal_matrix[0][0]);

	use_texture = 1;
	glUniform1i(b1, use_texture);
	int tex_loc = glGetUniformLocation(programObject, "Tex1");
	if (!use_gradient) glUniform1i(tex_loc,12);
	else glUniform1i(tex_loc, 12);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (char*)NULL + 0);

	//////////////////////////Second/////////////////////TOP

	modelM = mat_stack.top();
	mat_stack.pop();
	mat_stack.push(modelM);


	use_texture = 1;
	glUniform1i(b1, use_texture);
	tex_loc = glGetUniformLocation(programObject, "Tex1");
	if (!use_gradient) glUniform1i(tex_loc, 15);
	else glUniform1i(tex_loc, 15);



	modelM = mat_stack.top();
	mat_stack.pop();
	mat_stack.push(modelM);
	
	

	modelM = glm::rotate(90.0f*(22 / 7.0f) / 180.0f, glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4  model2= glm::rotate(90.0f*(22 / 7.0f) / 180.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	modelM = modelM *model2;
	//	modelM = glm::rotate(90.0f*(22 / 7.0f) / 180.0f, glm::vec3(0.0f, 1.0f, 0.0f));
//	modelM = glm::rotate(90.0f*(22 / 7.0f) / 180.0f, glm::vec3(0.0f, 0.0f, 1.0f));
//	modelM = glm::rotate(180.0f*(22 / 7.0f) / 180.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	modelM = glm::translate(modelM, glm::vec3(0.0f, 4.99999f, 0.0f));
	modelM = glm::scale(modelM, glm::vec3(10.0f, 00.0f, 10.0f));
	
	mvp2 = mvp*modelM;
	mv2 = mv*modelM;

	glUniformMatrix4fv(m1, 1, GL_FALSE, &mvp2[0][0]);
	glUniformMatrix4fv(m2, 1, GL_FALSE, &mv2[0][0]);
	glUniformMatrix4fv(m3, 1, GL_FALSE, &normal_matrix[0][0]);

	
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (char*)NULL + 0);

	modelM = mat_stack.top();
	mat_stack.pop();
	mat_stack.push(modelM);

	/////////Third Surface of the encironment///////////////////////////LEFT

	

	use_texture = 1;
	glUniform1i(b1, use_texture);
	tex_loc = glGetUniformLocation(programObject, "Tex1");
	if (!use_gradient) glUniform1i(tex_loc, 13);
	else glUniform1i(tex_loc, 13);
	
	
	modelM = mat_stack.top();
	mat_stack.pop();
	mat_stack.push(modelM);

	modelM = glm::rotate(90.0f*(22 / 7.0f) / 180.0f, glm::vec3(0.0f, 0.0f, 1.0f));
	modelM = glm::translate(modelM, glm::vec3(0.0f, 4.999999f, 0.0f));
	modelM = glm::scale(modelM, glm::vec3(10.0f, 10.0f, 10.0f));

	mvp2 = mvp*modelM;
	mv2 = mv*modelM;

	glUniformMatrix4fv(m1, 1, GL_FALSE, &mvp2[0][0]);
	glUniformMatrix4fv(m2, 1, GL_FALSE, &mv2[0][0]);
	glUniformMatrix4fv(m3, 1, GL_FALSE, &normal_matrix[0][0]);


	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (char*)NULL + 0);

	modelM = mat_stack.top();
	mat_stack.pop();
	mat_stack.push(modelM);


	/////////Fourth Surface of the encironment///////////////////////////FRONT!!


	use_texture = 1;
	glUniform1i(b1, use_texture);
	tex_loc = glGetUniformLocation(programObject, "Tex1");
	if (!use_gradient) glUniform1i(tex_loc, 11);
	else glUniform1i(tex_loc, 11);

	
	modelM = mat_stack.top();
	mat_stack.pop();
	mat_stack.push(modelM);

	//modelM = glm::rotate(90.0f*(22 / 7.0f) / 180.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	modelM = glm::translate(modelM, glm::vec3(0.0f, 4.999999f, 0.0f));
	modelM = glm::scale(modelM, glm::vec3(10.0f, 10.0f, 10.0f));

	mvp2 = mvp*modelM;
	mv2 = mv*modelM;

	glUniformMatrix4fv(m1, 1, GL_FALSE, &mvp2[0][0]);
	glUniformMatrix4fv(m2, 1, GL_FALSE, &mv2[0][0]);
	glUniformMatrix4fv(m3, 1, GL_FALSE, &normal_matrix[0][0]);


	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (char*)NULL + 0);

	modelM = mat_stack.top();
	mat_stack.pop();
	mat_stack.push(modelM);



	/////////fifth Surface of the encironment///////////////////////////Right



	use_texture = 1;
	glUniform1i(b1, use_texture);
	tex_loc = glGetUniformLocation(programObject, "Tex1");
	if (!use_gradient) glUniform1i(tex_loc, 14);
	else glUniform1i(tex_loc, 14);



	modelM = mat_stack.top();
	mat_stack.pop();
	mat_stack.push(modelM);

	modelM = glm::rotate(90.0f*(22 / 7.0f) / 180.0f, glm::vec3(0.0f, 0.0f, 1.0f));
	modelM = glm::translate(modelM, glm::vec3(0.0f, -4.9999999f, 0.0f));
	modelM = glm::scale(modelM, glm::vec3(10.0f, 10.0f, 10.0f));

	mvp2 = mvp*modelM;
	mv2 = mv*modelM;

	glUniformMatrix4fv(m1, 1, GL_FALSE, &mvp2[0][0]);
	glUniformMatrix4fv(m2, 1, GL_FALSE, &mv2[0][0]);
	glUniformMatrix4fv(m3, 1, GL_FALSE, &normal_matrix[0][0]);


	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (char*)NULL + 0);

	modelM = mat_stack.top();
	mat_stack.pop();
	mat_stack.push(modelM);



	/////////sixth Surface of the encironment///////////////////////////Bottom

	use_texture = 1;
	glUniform1i(b1, use_texture);
	tex_loc = glGetUniformLocation(programObject, "Tex1");
	if (!use_gradient) glUniform1i(tex_loc, 16);
	else glUniform1i(tex_loc, 16);




	modelM = mat_stack.top();
	mat_stack.pop();
	mat_stack.push(modelM);

	modelM = glm::rotate(90.0f*(22 / 7.0f) / 180.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	modelM = glm::translate(modelM, glm::vec3(0.0f, -4.999999f, 0.0f));
	modelM = glm::scale(modelM, glm::vec3(10.0f, 10.0f, 10.0f));

	mvp2 = mvp*modelM;
	mv2 = mv*modelM;

	glUniformMatrix4fv(m1, 1, GL_FALSE, &mvp2[0][0]);
	glUniformMatrix4fv(m2, 1, GL_FALSE, &mv2[0][0]);
	glUniformMatrix4fv(m3, 1, GL_FALSE, &normal_matrix[0][0]);


	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (char*)NULL + 0);

	modelM = mat_stack.top();
	mat_stack.pop();
	mat_stack.push(modelM);



	use_texture = 0;
	glUniform1i(b1, use_texture);
	glBindBuffer(GL_ARRAY_BUFFER, vboHandle[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVBO[0]);

	glEnableVertexAttribArray(c0);
	glEnableVertexAttribArray(c1);
	glEnableVertexAttribArray(c2);


	glVertexAttribPointer(c0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (char*)NULL + 0);
	glVertexAttribPointer(c1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (char*)NULL + 16);
	glVertexAttribPointer(c2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (char*)NULL + 32);



	///////////////////////////////
	//      draw Robot
	//////////////////////////////

	mat_stack.push(modelM);

	SetMaterialColor(Kd, 0.7, 0, 0.7, 1);
	glm::mat4 modelM1 = glm::mat4(1.0);
	modelM1 = glm::rotate(modelM1, angle123, glm::vec3(1.0f, 0.0f, 0.0f));
	modelM1 = glm::translate(modelM1, glm::vec3(-0.75, -0.0, 1.2));
	
	modelM1 = glm::scale(modelM1, glm::vec3(0.3, 0.3, 0.3));
	
	glm::mat4 mvp1 = mvp * modelM1;
	glm::mat4 mv1 = mv*modelM1;

	

	r.Robot::draw(mvp1, mv1, view, color, c0, c1, c2, m1, m2, m3, m4);
	
	modelM = mat_stack.top();
	mat_stack.pop();


	///////////////////////////////
	//      draw a light
	//////////////////////////////
	
	SetMaterialColor(Kd, 1, 1, 1, 1);

	glutSwapBuffers();
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glm::mat4 lightM = model;
	lightM = glm::translate(lightM, glm::vec3(light_pos[0], light_pos[1], light_pos[2]));
	lightM = glm::scale(lightM, glm::vec3(2, 2, 2));

	mvp = projection*view*lightM;
	mv = view*lightM;

	draw_cube(&mvp[0][0], &mv[0][0], &view[0][0], color, c0, c1, c2, m1, m2, m3, m4, m5);


	///////////////////////////////
	//      draw Maze walls
	//////////////////////////////
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap_texture1);

	use_texture = 2;
	glUniform1i(b1, use_texture);
	int tex_loc1 = glGetUniformLocation(programObject, "cubeMap");
	//if (!use_gradient) glUniform1i(tex_loc, 0);
	//else 
	glUniform1i(tex_loc1, 1);
	//SetMaterialColor(Kd, 1, 1, 0, 1);


	/*use_texture = 1;
	glUniform1i(b1, use_texture);
	tex_loc = glGetUniformLocation(programObject, "Tex1");
	glUniform1i(tex_loc, 5);
*/

//	SetMaterialColor(Kd, 1, 1, 0, 1);
	mvp = projection*view*model;
	mv = view * model;


	glm::mat4 modelM = glm::mat4(1.0f);
	mat_stack.push(modelM);


	for (int i = 0; i < 9; i++){
		for (int j = 0; j < 9; j++){

			vector <int>::iterator k = find(abc[i * 9 + j].begin(), abc[i * 9 + j].end(), i * 9 + j + 1);

			if (k != abc[i * 9 + j].end()){

				modelM = glm::translate(modelM, glm::vec3((j + 1)*0.2 + (-0.9), (i*0.2) - 0.9f + 0.05, 0.0f));
				modelM = glm::rotate(modelM, angle123, glm::vec3(0.0, 0.0, 1.0));
				modelM = glm::scale(modelM, glm::vec3(2, .1, 3));

				glm::mat4 mv1 = mv * modelM;
				modelM = mvp*modelM;

				draw_cube(&modelM[0][0], &mv1[0][0], &view[0][0], color, c0, c1, c2, m1, m2, m3, m4,m5);
				modelM = mat_stack.top();

			}

			k = find(abc[i * 9 + j].begin(), abc[i * 9 + j].end(), (i + 1) * 9 + j);
			if (k != abc[i * 9 + j].end()){

				modelM = glm::translate(modelM, glm::vec3((j*0.2) + (-0.9) + 0.1, (i + 1)*0.2 + -0.95f, 0.0f));
				modelM = glm::scale(modelM, glm::vec3(2, .1, 3));

				glm::mat4 mv1 = mv * modelM;
				modelM = mvp*modelM;

				draw_cube(&modelM[0][0], &mv1[0][0], &view[0][0], color, c0, c1, c2, m1, m2, m3, m4,m5);
				modelM = mat_stack.top();

			}

			if (!(j == 0)){
				modelM = glm::translate(modelM, glm::vec3(j*0.2 - 0.9 + 0.1, -1.0, 0.0f));
				modelM = glm::scale(modelM, glm::vec3(2, .1, 3));

				glm::mat4 mv1 = mv * modelM;
				modelM = mvp*modelM;

				draw_cube(&modelM[0][0], &mv1[0][0], &view[0][0], color, c0, c1, c2, m1, m2, m3, m4,m5);
				modelM = mat_stack.top();
			}

			modelM = glm::translate(modelM, glm::vec3(-0.9, (i)*0.2 - 0.80f, 0.0f));
			modelM = glm::rotate(modelM, angle123, glm::vec3(0.0, 0.0, 1.0));
			modelM = glm::scale(modelM, glm::vec3(2, .1, 3));

			glm::mat4 mv1 = mv * modelM;
			modelM = mvp*modelM;

			draw_cube(&modelM[0][0], &mv1[0][0], &view[0][0], color, c0, c1, c2, m1, m2, m3, m4,m5);
			modelM = mat_stack.top();

			if (!(j == 8)){

				modelM = glm::translate(modelM, glm::vec3(j*0.2 - 0.9 + 0.1, 0.90f, 0.0f));
				modelM = glm::scale(modelM, glm::vec3(2, .1, 3));

				glm::mat4 mv1 = mv * modelM;
				modelM = mvp*modelM;

				draw_cube(&modelM[0][0], &mv1[0][0], &view[0][0], color, c0, c1, c2, m1, m2, m3, m4,m5);
				modelM = mat_stack.top();
			}

			//			right most
			modelM = glm::translate(modelM, glm::vec3(0.9, (i)*0.2 - 0.90f, 0.0f));
			modelM = glm::rotate(modelM, angle123, glm::vec3(0.0, 0.0, 1.0));
			modelM = glm::scale(modelM, glm::vec3(2, .1, 3));

			mv1 = mv * modelM;
			modelM = mvp*modelM;

			draw_cube(&modelM[0][0], &mv1[0][0], &view[0][0], color, c0, c1, c2, m1, m2, m3, m4,m5);
			modelM = mat_stack.top();
			
	
		}

		//std::cout << endl;
	}

	
	modelM = mat_stack.top();
	SetMaterialColor(Kd, 1.0, 0.0, 0.0,1.0);
	

	GLuint renderTex2;
	glGenTextures(1, &renderTex2);
	glActiveTexture(GL_TEXTURE5);
	glBindTexture(GL_TEXTURE_2D, renderTex2);
	read_Image(donkey_fur);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 256,
		256, 0, GL_RGBA, GL_UNSIGNED_BYTE,
		texImage);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glDisable(GL_TEXTURE20);

	
	
	use_texture = 1;
	glUniform1i(b1, use_texture);
	
	tex_loc1 = glGetUniformLocation(programObject, "cubeMap");
	//if (!use_gradient) glUniform1i(tex_loc, 0);
	//else 
	glUniform1i(tex_loc1, 20);
	//SetMaterialColor(Kd, 1, 1, 0, 1);


	modelM = glm::translate(modelM, glm::vec3(1.0f, 1.0f, 0.0f));
	modelM = glm::rotate(90.0f*(22 / 7.0f) / 180.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	modelM =glm::scale(modelM, glm::vec3(50.0f, 50.0f, 50.0f));
	
	mvp2 = mvp*modelM;
	mv2 = mv*modelM;
	SetMaterialColor(Kd,1.0f,1.0f,1.0f,1.0f);
	obj.Model::drawModel(mvp2, mv2, view, color, c0, c1, c2, m1, m2, m3, m4);
	
	glDisable(GL_TEXTURE_2D);
	///////////////////////////////
	//     ENVIRONMENT CubeMap
	//////////////////////////////
	
	use_texture = 2;
	glUniform1i(b1, use_texture);
	tex_loc1 = glGetUniformLocation(programObject, "cubeMap");
	//if (!use_gradient) glUniform1i(tex_loc, 0);
	//else 
	glUniform1i(tex_loc1, 1);
	//SetMaterialColor(Kd, 1, 1, 0, 1);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_CUBE_MAP, skybox_texture);

	glm::mat4 floorM = glm::translate(model, glm::vec3(-1.0, -1.0, -0.8));
	floorM = glm::scale(floorM, glm::vec3(15.0, 15.0, 15.0));

	mvp = projection*view*floorM;
	mv = view * floorM;
	draw_cube(&mvp[0][0], &mv[0][0], &view[0][0], color, c0, c1, c2, m1, m2, m3, m4, m5);
	
	glutSwapBuffers();
	glDisableClientState(GL_VERTEX_ARRAY);
	glFlush();
}


void mymotion(int x, int y)
{
	if (xform_mode == XFORM_ROTATE) {
		z_angle += (x - press_x) / 5.0;
		if (z_angle > 180) z_angle -= 360;
		else if (z_angle <-180) z_angle += 360;
		press_x = x;

		x_angle -= (y - press_y) / 5.0;
		if (x_angle > 180) x_angle -= 360;
		else if (x_angle < -180) x_angle += 360;
		press_y = y;
	}
	else if (xform_mode == XFORM_SCALE){
		float old_size = scale_size;
		scale_size *= (1 + (y - press_y) / 60.0);
		if (scale_size < 0) scale_size = old_size;
		press_y = y;
	}
	glutPostRedisplay();
}


void mymouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN) {
		press_x = x; press_y = y;
		if (button == GLUT_LEFT_BUTTON)
			xform_mode = XFORM_ROTATE;
		else if (button == GLUT_RIGHT_BUTTON)
			xform_mode = XFORM_SCALE;
	}
	else if (state == GLUT_UP) {
		xform_mode = XFORM_NONE;
	}
	glutPostRedisplay();
}



///////////////////////////////////////////////////////////////

void mykey(unsigned char key, int x, int y)
{
	float d_angle = 10;
	if (key == 'q') exit(1);
	if (key == 'R')
		modelM = glm::rotate(modelM, d_angle, glm::vec3(0.0f, 0.0f, 1.0f));
	//  modelM =  rotatez(modelM, d_angle);
	if (key == 'r')
		modelM = glm::translate(modelM, glm::vec3(0.1f, 0.0f, 0.0f));
	//  modelM =  translate(modelM, .1,0,0);
	if (key == 'l')
		modelM = glm::translate(modelM, glm::vec3(-0.1f, 0.0f, 0.0f));
	//modelM =  translate(modelM, -.1,0,0);
	if (key == 'f')
		modelM = glm::translate(modelM, glm::vec3(0.0f, 0.1f, 0.0f));
	//modelM =  translate(modelM, 0,.1,0);
	if (key == 'b')
		modelM = glm::translate(modelM, glm::vec3(0.0f, -0.1f, 0.0f));
	//modelM =  translate(modelM, 0,-.1,0);
	if (key == 'c') {
		modelM = glm::mat4(1.0f);
		angle1 = angle2 = angle3 = angle4 = 0;
	}

	if (key == '[') {
		angle1 += 5;
		printf(" hello!\n");
	}
	if (key == ']')
		angle2 += 5;

	if (key == ';')
		mat_shine[0] += 1;
	if (key == 'b')
		mat_shine[0] -= 1;
	if (key == 'k')
		light_pos[0] += 0.5;
	if (key == 'h')
		light_pos[0] -= 0.5;
	if (key == 't')
		light_pos[1] += 0.5;
	if (key == 'g')
		light_pos[1] -= 0.5;
	if (key == 'u')
		light_pos[2] += 0.5;
	if (key == 'j')
		light_pos[2] -= 0.5;
	r.Robot::keys1(key, x, y);
	glutPostRedisplay();
}

//void Robot::keys1(unsigned char key, int x, int y){
//	float x1 = -0.1f / 40.0f;
//	float d_angle = 15.0 * (22 / 7.0) / 180;
//	switch (key){
//	case (char)27:
//		exit(1);
//		break;
//
//		/*case 'q':
//		exit(1);
//		break;*/
//	case 'a':
//		r.Robot::modelMR = glm::translate(r.Robot::modelMR, glm::vec3(-0.1f, 0.0f, 0.0f));
//		modelV = glm::translate(modelV, glm::vec3(-x1, 0.0f, 0.0f));
//		posx = posx + 0.1;
//
//		break;
//	case 'd':
//		r.Robot::modelMR = glm::translate(r.Robot::modelMR, glm::vec3(0.1f, 0.0f, 0.0f));
//		modelV = glm::translate(modelV, glm::vec3(x1, 0.0f, 0.0f));
//		posx = posx - 0.1;
//		break;
//	case 'w':
//		r.Robot::modelMR = glm::translate(r.Robot::modelMR, glm::vec3(0.0f, 0.0f, -0.1f));
//		view = glm::translate(view, glm::vec3(0.0f, 0.0f, x1));
//		posy = posy + 0.1;
//		break;
//	case 's':
//		r.Robot::modelMR = glm::translate(r.Robot::modelMR, glm::vec3(0.0f, 0.0f, 0.1f));
//		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -x1));
//		posy = posy - 0.1;
//		break;
//
//
//	case 'q':
//		modelMR = glm::rotate(modelMR, d_angle, glm::vec3(0.0, 1.0, 1.0));
//		break;
//
//	case 'e':
//		modelMR = glm::rotate(modelMR, -d_angle, glm::vec3(0.0, 1.0, 1.0));
//		break;
//
//	case 'u':
//		modelMR = glm::rotate(modelMR, d_angle, glm::vec3(0.0, 0.0, 1.0));
//		break;
//
//	case 'i':
//		modelMR = glm::rotate(modelMR, -d_angle, glm::vec3(0.0, 0.0, 1.0));
//		break;
//
//	case 'c':
//		modelMR = glm::mat4(1.0f);
//		angle1 = angle2 = angle3 = angle4 = d_angle = 0;
//
//	case '-':
//		modelMR = glm::scale(modelMR, glm::vec3(0.8, 0.8, 1.0));
//		break;
//
//	case '+':
//		modelMR = glm::scale(modelMR, glm::vec3(1.2, 1.2, 1.0));
//		break;
//
//	case '1':
//		count1++;
//		if (count1 % 2 == 0)angle1 += ((3.14159) / 180) * 50;
//		else angle1 -= ((3.14159) / 180) * 50;
//		break;
//
//	case '2':
//		count2++;
//		if (count2 % 2 == 0)angle2 += ((3.14159) / 180) * 50;
//		else angle2 -= ((3.14159) / 180) * 50;
//		break;
//
//	case '3':
//		count3++;
//		if (count3 % 2 == 0)angle3 += ((3.14159) / 180) * 50;
//		else angle3 -= ((3.14159) / 180) * 50;
//		break;
//
//	case '4':
//		count4++;
//		if (count4 % 2 == 0)angle4 += ((3.14159) / 180) * 50;
//		else angle4 -= ((3.14159) / 180) * 50;
//		break;
//
//	case '6':
//		angle4 += ((3.14159) / 180) * 50;
//		break;
//
//	case'7':
//		angle3 += ((3.14159) / 180) * 50;
//
//	default:
//		cout << "Wrong Input";
//
//	}
//	glutPostRedisplay();
//}
//
void process_Normal_Keys(int key, int x, int y)
{
	switch (key)
	{
	case 27:      break;
	case 100: light_pos[1] -= 0.5; printf("GLUT_KEY_LEFT %d\n", key);   break;
	case 102: light_pos[0] -= 0.5; printf("GLUT_KEY_RIGHT %d\n", key);;  break;
	case 101: light_pos[0] += 0.5; printf("GLUT_KEY_UP %d\n", key);;  break;
	case 103: light_pos[1] += 0.5; printf("GLUT_KEY_DOWN %d\n", key);;  break;
	}

}


void makeCheckImage()
{
	for (int i = 0; i<256; i++)
	for (int j = 0; j<256; j++) {
		int c = ((((i & 0x8) == 0) ^ ((j & 0x8)) == 0)) * 255;
		texImage[i][j][0] = (GLubyte)c;
		texImage[i][j][1] = (GLubyte)c;
		texImage[i][j][2] = (GLubyte)c;
		texImage[i][j][3] = (GLubyte)255;
	};
}

///////////////////////////////////////////////////////////


void Init_texture(int tex) {

	GLuint renderTex1;
	GLuint gradientTex1;

	GLuint renderTex2;
	GLuint gradientTex2;


	read_Image(fname);
	
	glGenTextures(1, &renderTex1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, renderTex1);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 256,
		256, 0, GL_RGBA, GL_UNSIGNED_BYTE,
		texImage);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); 
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); 


	glGenTextures(1, &gradientTex1);
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 256,
		256, 0, GL_RGBA, GL_UNSIGNED_BYTE,
		gradientImage);
	//  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
	//  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);



	read_Image(fname);
	
	glGenTextures(1, &renderTex1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, renderTex1);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 256,
		256, 0, GL_RGBA, GL_UNSIGNED_BYTE,
		texImage);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); 
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); 

	glGenTextures(1, &gradientTex1);
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, gradientTex1);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 256,
		256, 0, GL_RGBA, GL_UNSIGNED_BYTE,
		gradientImage);
	//  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
	//  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

/////////////////////////////GRASS For the Maze//////////////////////////////////////

	/*read_Image(fname1);

	glGenTextures(1, &renderTex);
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, renderTex);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 256,
		256, 0, GL_RGBA, GL_UNSIGNED_BYTE,
		texImage);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);*/

	
	glGenTextures(1, &renderTex2);
	glActiveTexture(GL_TEXTURE5);
	glBindTexture(GL_TEXTURE_2D, renderTex2);
	read_Image(fname1);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 256,
		256, 0, GL_RGBA, GL_UNSIGNED_BYTE,
		texImage);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glDisable(GL_TEXTURE5);

	glGenTextures(1, &renderTex2);
	glActiveTexture(GL_TEXTURE6);
	glBindTexture(GL_TEXTURE_2D, renderTex2);
	read_Image(fname2);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 256,
		256, 0, GL_RGBA, GL_UNSIGNED_BYTE,
		texImage);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glDisable(GL_TEXTURE6);




	glGenTextures(1, &renderTex2);
	glActiveTexture(GL_TEXTURE11);
	glBindTexture(GL_TEXTURE_2D, renderTex2);
	read_Image(sky1);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 256,
		256, 0, GL_RGBA, GL_UNSIGNED_BYTE,
		texImage);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glDisable(GL_TEXTURE5);

	glGenTextures(1, &renderTex2);
	glActiveTexture(GL_TEXTURE12);
	glBindTexture(GL_TEXTURE_2D, renderTex2);
	read_Image(sky2);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 256,
		256, 0, GL_RGBA, GL_UNSIGNED_BYTE,
		texImage);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glDisable(GL_TEXTURE6);

	glGenTextures(1, &renderTex2);
	glActiveTexture(GL_TEXTURE13);
	glBindTexture(GL_TEXTURE_2D, renderTex2);
	read_Image(sky3);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 256,
		256, 0, GL_RGBA, GL_UNSIGNED_BYTE,
		texImage);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glDisable(GL_TEXTURE5);

	glGenTextures(1, &renderTex2);
	glActiveTexture(GL_TEXTURE14);
	glBindTexture(GL_TEXTURE_2D, renderTex2);
	read_Image(sky4);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 256,
		256, 0, GL_RGBA, GL_UNSIGNED_BYTE,
		texImage);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glDisable(GL_TEXTURE6);

	glGenTextures(1, &renderTex2);
	glActiveTexture(GL_TEXTURE15);
	glBindTexture(GL_TEXTURE_2D, renderTex2);
	read_Image(sky5);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 256,
		256, 0, GL_RGBA, GL_UNSIGNED_BYTE,
		texImage);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glDisable(GL_TEXTURE5);

	glGenTextures(1, &renderTex2);
	glActiveTexture(GL_TEXTURE16);
	glBindTexture(GL_TEXTURE_2D, renderTex2);
	read_Image(sky6);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 256,
		256, 0, GL_RGBA, GL_UNSIGNED_BYTE,
		texImage);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glDisable(GL_TEXTURE6);



}



void InitSquare()
{

	sqverts[0].location[0] = -0.5; sqverts[0].location[1] = 0;  sqverts[0].location[2] = -0.5;  sqverts[0].location[3] = 1;
	sqverts[0].normal[0] = 0; sqverts[0].normal[1] = 1;  sqverts[0].normal[2] = 0;  sqverts[0].normal[3] = 0;
	sqverts[0].texCoord[0] = 0; sqverts[0].texCoord[1] = 0;
	sqverts[0].color[0] = 0.5; sqverts[0].color[1] = 0.5;  sqverts[0].color[2] = 1;  sqverts[0].color[3] = 1;

	sqverts[1].location[0] = 0.5; sqverts[1].location[1] = 0;  sqverts[1].location[2] = -0.5;  sqverts[1].location[3] = 1;
	sqverts[1].normal[0] = 0; sqverts[1].normal[1] = 1;  sqverts[1].normal[2] = 0;  sqverts[1].normal[3] = 0;
	sqverts[1].texCoord[0] = 1.0; sqverts[1].texCoord[1] = 0;
	sqverts[1].color[0] = 0.5; sqverts[1].color[1] = 0.5;  sqverts[1].color[2] = 1;  sqverts[1].color[3] = 1;

	sqverts[2].location[0] = 0.5; sqverts[2].location[1] = 0;  sqverts[2].location[2] = 0.5;  sqverts[2].location[3] = 1;
	sqverts[2].normal[0] = 0; sqverts[2].normal[1] = 1;  sqverts[2].normal[2] = 0;  sqverts[2].normal[3] = 0;
	sqverts[2].texCoord[0] = 1.0; sqverts[2].texCoord[1] = 1.0;
	sqverts[2].color[0] = 0.5; sqverts[2].color[1] = 0.5;  sqverts[2].color[2] = 1;  sqverts[2].color[3] = 1;

	sqverts[3].location[0] = -0.5; sqverts[3].location[1] = 0;  sqverts[3].location[2] = 0.5;  sqverts[3].location[3] = 1;
	sqverts[3].normal[0] = 0; sqverts[3].normal[1] = 1;  sqverts[3].normal[2] = 0;  sqverts[3].normal[3] = 0;
	sqverts[3].texCoord[0] = 0.0; sqverts[3].texCoord[1] = 1.0;
	sqverts[3].color[0] = 1; sqverts[3].color[1] = 1;  sqverts[3].color[2] = 1;  sqverts[3].color[3] = 1;


	sqindices[0] = 0;   sqindices[1] = 1;   sqindices[2] = 2;
	sqindices[3] = 2;   sqindices[4] = 3;   sqindices[5] = 0;

}


//////////////////////////////////////////////////////////////////////////////////
//
// create VBO objects and send the triangle vertices/colors to the graphics card
// 
void InitVBOSquare()
{
	glGenBuffers(1, &vboHandleSquare[0]);   // create an interleaved VBO object

	glBindBuffer(GL_ARRAY_BUFFER, vboHandleSquare[0]);   // bind the second handle 
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)* 4, sqverts, GL_STATIC_DRAW); // allocate space and copy the position data over

	glBindBuffer(GL_ARRAY_BUFFER, 0);   // clean up 

	glGenBuffers(1, &indexVBOSquare[0]);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVBOSquare[0]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)* 6, sqindices, GL_STATIC_DRAW);  // load the index data 

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);  // clean up 

	// by now, we moved the position and color data over to the graphics card. There will be no redundant data copy at drawing time 
}



void Robot::keys1(unsigned char key, int x, int y){

	float d_angle = 10;
	switch (key){
	case 'q':
		exit(1);
		break;
	case 'a':
		r.Robot::modelMR = glm::translate(r.Robot::modelMR, glm::vec3(-0.1f, 0.0f, 0.0f));
		posx = posx - 0.04;
		//mainFile::model = glm::translate(file.mainFile::model, glm::vec3(-0.1f, 0.0f, 0.0f));
		break;
	case 'd':
		posx = posx + 0.04;
		r.Robot::modelMR = glm::translate(r.Robot::modelMR, glm::vec3(0.1f, 0.0f, 0.0f));
		break;
	case 'w':
		posy = posy + 0.04;
		r.Robot::modelMR = glm::translate(r.Robot::modelMR, glm::vec3(0.0f, 0.0f, -0.1f));
		break;
	case 's':
		posy = posy - 0.04;
		r.Robot::modelMR = glm::translate(r.Robot::modelMR, glm::vec3(0.0f, 0.0f, 0.1f));
		break;
	case 'z':
		r.Robot::modelMR = glm::rotate(r.Robot::modelMR, d_angle, glm::vec3(0.0, 1.0, 1.0));
		break;

	case '-':
		r.Robot::modelMR = glm::scale(r.Robot::modelMR, glm::vec3(0.8, 0.8, 1.0));
		break;

	case '+':
		r.Robot::modelMR = glm::scale(r.Robot::modelMR, glm::vec3(1.2, 1.2, 1.0));
		break;

	case '1':

		r.Robot::count1++;
		if (r.Robot::count1 % 2 == 0)r.Robot::angle1 += ((3.14159) / 180) * 50;
		else r.Robot::angle1 -= ((3.14159) / 180) * 50;
		break;

	case '2':
		r.Robot::count2++;
		if (r.Robot::count2 % 2 == 0)r.Robot::angle2 -= ((3.14159) / 180) * 50;
		else r.Robot::angle2 += ((3.14159) / 180) * 50;
		break;

	case '3':
		r.Robot::count3++;
		if (r.Robot::count3 % 2 == 0)r.Robot::angle3 += ((3.14159) / 180) * 50;
		else r.Robot::angle3 -= ((3.14159) / 180) * 50;
		break;

	case '4':
		r.Robot::count4++;
		if (r.Robot::count4 % 2 == 0)r.Robot::angle4 -= ((3.14159) / 180) * 50;
		else r.Robot::angle4 += ((3.14159) / 180) * 50;
		break;

	default:
		std::cout << "Wrong Input";

	}
	glutPostRedisplay();
}



int main(int argc, char** argv)
{
	


	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	Graph g(9);
	abc = g.getRemoved();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(600, 600);

	glutCreateWindow("fixed function pipeline: simple");
	glutDisplayFunc(display);
	glutSpecialFunc(process_Normal_Keys);
	glutMouseFunc(mymouse);
	glutKeyboardFunc(mykey);
	glutMotionFunc(mymotion);

	glewInit();

//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	color[0] = 0.2; color[1] = 0.4; color[2] = 0.2;
	c.InitCylinder(r.nslices, r.nstacks, 1.0, 0.0, 1.0, &modelM[0][0], color, c0, c1, c2, m1);

	c.InitCylVBO(r.nstacks, r.nslices);
	r.Robot::InitVBOCube();
	s.InitSphere(0.5, r.nstacks, r.nslices, 1.0, 0.0, 1.0);
	s.InitVBOSphere(r.nstacks, r.nslices);

	InitCube_VBO();

	programObject = SetupGLSL("do_nothing");

	// initialize geometry 

	InitSquare();
	InitVBOSquare();

	// initialize the texture object 
	
	Init_texture(1);
	init_cubemap();
	init_cubemap2();
	init_skybox();
	obj.plyInit();
	
	glutMainLoop();
}







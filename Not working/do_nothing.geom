#version 330

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

out vec3 N1;
out vec3 L1;
out vec3 R1;
out vec3 V1;

in vec3 N[3];
in vec3 L[3];
in vec3 R[3];
in vec3 V[3];

uniform mat4 local2clip;
uniform mat4 local2eye;
uniform mat4 normal_matrix;
uniform mat4 world2eye; 

uniform vec4 light_ambient;
uniform vec4 light_diffuse;
uniform vec4 light_specular;
uniform vec4 light_pos;

uniform vec4 mat_ambient;
uniform vec4 mat_diffuse;
uniform vec4 mat_specular;
uniform float mat_shine; 

//varying vec3 v_normal;  // vertex normal 
out vec4 v_color1; 	// vertex color 
out vec4 pos_in_eye1;  //vertex position in eye space 
out vec2 FtexCoord1; 

in vec4 v_color[3]; 	// vertex color 
in vec4 pos_in_eye[3];  //vertex position in eye space 
in vec2 FtexCoord[3]; 

void main(void)
{
    int i;
		


    for (i = 0; i < gl_in.length(); i++)
    {
		N1=N[i];
		L1=L[i];
		R1=R[i];
		V1=R[i];

		FtexCoord1=FtexCoord[i];
		v_color1=v_color[i];
		pos_in_eye1=pos_in_eye[i];


        gl_Position = gl_in[i].gl_Position;
        EmitVertex();
    }
    EndPrimitive();
}
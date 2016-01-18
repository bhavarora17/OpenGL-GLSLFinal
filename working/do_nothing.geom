#version 430 core

layout (triangles) in;
layout (triangle) out;
layout (max_vertices = 3) out;

out vec3 N1;
out vec3 L1;
out vec3 R1;
out vec3 V1;

in vec3 N;
in vec3 L;
in vec3 R;
in vec3 V;

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

in vec4 v_color; 	// vertex color 
in vec4 pos_in_eye;  //vertex position in eye space 
in vec2 FtexCoord; 

void main(void)
{
	N1=N;
	L1=L;
	R1=R;
	V1=R;

	FtexCoord1=FtexCoord;
	v_color1=v_color;
	pos_in_eye1=pos_in_eye;

    int i;

    for (i = 0; i < gl_in.length(); i++)
    {
        gl_Position = gl_in[i].gl_Position;
        EmitVertex();
    }
    EndPrimitive();
}
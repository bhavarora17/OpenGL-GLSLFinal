in vec4 position; 
in vec4 color1;
in vec4 normal; 
in vec2 texCoord; 

uniform sampler2D Tex1; 

uniform int use_texture;

out vec4 pcolor;

out vec3 N;
out vec3 L;
out vec3 R;
out vec3 V;


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
out vec4 v_color; 	// vertex color 
out vec4 pos_in_eye;  //vertex position in eye space 
out vec2 FtexCoord; 

//
// this shader just pass the vertex position and color along, doesn't actually do anything 
// Note that this means the vertex position is assumed to be in clip space already 
//

void main(){
     
       gl_Position = local2clip * position;
	  
	   N =     normalize(vec3(normal_matrix * normal));    //v_normal
	   vec4 Lpos =  world2eye * light_pos; 					//light pos. in eye
       vec4 Vpos =  local2eye * position; 					//pos_in_eye
       L = normalize(vec3(Lpos - Vpos)); 					//light_vector
	   
	   R = normalize(reflect(-L, N)); 
       V = normalize(vec3(-Vpos)); 							//eye vector
	   
	   vec3 halfv = normalize(L+V);
	   FtexCoord = texCoord; 

	   //pcolor = color1;
}
uniform int use_texture; 

in vec4 pcolor; 

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

uniform sampler2D Tex1; 
in vec2 FtexCoord; 

//
// this shader just passes the interpolated fragment color along 
//
void main() { 
 
	   vec4 ambient = light_ambient * mat_ambient;
	   float NdotL; 
       if (dot(N,L) <0.0) NdotL = 0.0; 
       else NdotL = dot(N, L); 

       vec4 diffuse = light_diffuse * mat_diffuse * NdotL;

	   float RdotV; 
       RdotV = dot(R, V); 

       if (NdotL == 0.0) RdotV = 0.0; 
       if (RdotV <0.0) RdotV = 0.0; 

       vec4 specular = light_specular * mat_specular * pow(RdotV,mat_shine);   
	 
	   vec4 texcolor;
	 
		
	   if( use_texture == 1 ) {
		  texcolor = texture2D(Tex1, FtexCoord); 
		  gl_FragColor = texcolor; 
	   }
	   else
		  gl_FragColor = (diffuse + ambient + specular); 
 } 
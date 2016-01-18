uniform int use_texture; 

in vec4 pcolor; 

in vec3 N;
in vec3 L;
in vec3 R;
in vec3 V;

in vec4 pos_in_eye;


uniform mat4 local2clip;
uniform mat4 local2eye;
uniform mat4 normal_matrix;
uniform mat4 world2eye;
uniform mat4 eye2world; 

uniform vec4 light_ambient;
uniform vec4 light_diffuse;
uniform vec4 light_specular;
uniform vec4 light_pos;

uniform vec4 mat_ambient;
uniform vec4 mat_diffuse;
uniform vec4 mat_specular;
uniform float mat_shine;

uniform sampler2D Tex1;
uniform sampler2D Tex2;
uniform sampler2D Tex3;
uniform sampler2D Tex4;
uniform sampler2D Tex5;
uniform sampler2D Tex6;
uniform sampler2D Tex7;

uniform samplerCube cubeMap;

in vec2 FtexCoord; 




struct FogInfo {
  float maxDist;
  float minDist;
  vec3 color;
};

uniform FogInfo Fog;

const vec3 FogBaseColor = vec3(1., 1., 1.);
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
	   vec3 ref, view_vector;
	   vec4 env_color = vec4(1, 0, 0, 1);
		
	    vec4 light = diffuse + ambient + specular;


		float dist = abs( pos_in_eye.z );

		//float fogFactor = (Fog.maxDist - dist) / 
        //              (Fog.maxDist - Fog.minDist);

		float fogFactor = (10 - dist) / (10 + 10);

		vec3 color = mix( FogBaseColor, vec3(light), fogFactor );
			

	   if( use_texture == 1 ) {
		  texcolor = texture2D(Tex1, FtexCoord); 
		  gl_FragColor = texcolor * light;//vec4(color,1.0); 
	   }
	   else if( use_texture == 2 ){
		  view_vector = normalize(vec3(vec4(0, 0, 0, 1)-pos_in_eye));
		  ref = normalize(reflect(-view_vector, N)); // in eye-space
		  ref = vec3(eye2world * vec4(ref, 0));
		  env_color = textureCube(cubeMap, ref);
		  gl_FragColor = env_color * light;//vec4(color,1.0);
	   }
	   else
		  gl_FragColor = light;vec4(color,1.0); 
 }
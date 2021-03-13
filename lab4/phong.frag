#version 120

//
// Fragment shader for PHONG shading.
//
// @author  RIT CS Department
// @author  Jimmy Dugan
//

// incoming vectors
varying vec4 normal_vec;
varying vec4 trans_vposition;
varying vec4 trans_ls_position;

//
// Shading matrices
//

// Ambient color
uniform vec4 ambient_color; 
// Ambient reflection coefficient
uniform float ambient_reflect_coef;
// Diffuse color
uniform vec4 diffuse_color; 
// Diffuse reflection coefficient
uniform float diffuse_reflect_coef; 
// Specular color
uniform vec4 spec_color; 
// Specular exponent
uniform float spec_exp; 
// Specular reflection coefficient
uniform float spec_reflect_coef; 
// Light source color
uniform vec4 ls_color; 
// Ambient light color
uniform vec4 ls_ambient_color; 


void main()
{
    // color components
    vec4 ambient = ls_ambient_color * ambient_reflect_coef * ambient_color;
    vec4 diffuse = diffuse_reflect_coef * diffuse_color * max(dot(normalize(trans_ls_position - trans_vposition).xyz, normalize(normal_vec).xyz), 0);
    vec4 specular = spec_color * ls_color * spec_reflect_coef * pow(max(dot(reflect(normalize(trans_ls_position - trans_vposition), 
    	normalize(normal_vec)).xyz, normalize(trans_vposition).xyz), 0), spec_exp);

    gl_FragColor =  ambient + ls_color * (diffuse + specular);
}
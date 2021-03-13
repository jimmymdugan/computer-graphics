///
///  Lighting
///
///  Simple module for setting up the parameters for lighting and shading
///  for the Shading Assignment.
///
///  Created by Warren R. Carithers 2019/11/18.
///  Copyright 2019 Rochester Institute of Technology.  All rights reserved.
///

#include "Lighting.h"
#include "Shapes.h"
#include "Utils.h"

using namespace std;

//teapot properties
static GLfloat tp_ambient_color[] = {0.5, 0.1, 0.9, 1.0};
static GLfloat tp_ambient_reflect_coef = 0.5;
static GLfloat tp_diffuse_color[] = {0.89, 0.0, 0.0, 1.0};
static GLfloat tp_diffuse_reflect_coef = 0.7;
static GLfloat tp_spec_color[] = {1.0, 1.0, 1.0, 1.0 };
static GLfloat tp_spec_exp = 10.0;
static GLfloat tp_spec_reflect_coef = 1.0f;

//torus properties
static GLfloat tor_ambient_color[] = {0.1, 0.85, 0.2, 1.0 };
static GLfloat tor_ambient_reflect_coef = 0.5;
static GLfloat tor_diffuse_color[] = {0.1, 0.85, 0.2, 1.0};
static GLfloat tor_diffuse_reflect_coef = 0.7;
static GLfloat tor_spec_color[] = {1.0, 1.0, 1.0, 1.0 };
static GLfloat tor_spec_exp = 50.0;
static GLfloat tor_spec_reflect_coef = 1.0;

//light properties
static GLfloat ls_color[] = {1.0, 1.0, 0.0, 1.0};
static GLfloat ls_position[] = {0.0, 5.0, 2.0, 1.0};
static GLfloat ls_ambient_color[] = {0.5, 0.5, 0.5, 1.0};

///
/// This function sets up the lighting, material, and shading parameters
/// for the shaders.
///
/// You will need to write this function, and maintain all of the values
/// needed to be sent to the vertex shader.
///
/// @param program  The ID of an OpenGL (GLSL) shader program to which
///    parameter values are to be sent
/// @param object   Which object is currently being drawn
/// @param shading  Type of shading being used
///
void setLighting( GLuint program, int object, int shading )
{
    glUniform4fv(getUniformLoc(program, "ls_color"), 1, ls_color);
    glUniform4fv(getUniformLoc(program, "ls_position"), 1, ls_position);
    glUniform4fv(getUniformLoc(program, "ls_ambient_color"), 1, ls_ambient_color);
    
    switch(object){
        case TEAPOT: {
            glUniform4fv(getUniformLoc(program, "ambient_color"), 1, tp_ambient_color);
            glUniform1f(getUniformLoc(program, "ambient_reflect_coef"), tp_ambient_reflect_coef);
            glUniform4fv(getUniformLoc(program, "diffuse_color"), 1, tp_diffuse_color);
            glUniform1f(getUniformLoc(program, "diffuse_reflect_coef"), tp_diffuse_reflect_coef);
            
            if(shading != FLAT){
                glUniform4fv(getUniformLoc(program, "spec_color"), 1, tp_spec_color);
                glUniform1f(getUniformLoc(program, "spec_exp"), tp_spec_exp);
                glUniform1f(getUniformLoc(program, "spec_reflect_coef"), tp_spec_reflect_coef);
            }
            break;
        }
            
        case TORUS: {
            glUniform4fv(getUniformLoc(program, "ambient_color"), 1, tor_ambient_color);
            glUniform1f(getUniformLoc(program, "ambient_reflect_coef"), tor_ambient_reflect_coef);
            glUniform4fv(getUniformLoc(program, "diffuse_color"), 1, tor_diffuse_color);
            glUniform1f(getUniformLoc(program, "diffuse_reflect_coef"), tor_diffuse_reflect_coef);
            
            if(shading != FLAT){
                glUniform4fv(getUniformLoc(program, "spec_color"), 1, tor_spec_color);
                glUniform1f(getUniformLoc(program, "spec_exp"), tor_spec_exp);
                glUniform1f(getUniformLoc(program, "spec_reflect_coef"), tor_spec_reflect_coef);
            }
            break;
        }
    }
}


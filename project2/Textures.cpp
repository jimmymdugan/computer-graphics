///
///  Textures.cpp
///
///  Simple class for setting up texture mapping parameters.
///
///  Created by Warren R. Carithers 2016/11/22.
///  Updates: 2019/11/23, 2020/11/10 by wrc.
///  Based on code created by Joe Geigel on 1/23/13.
///  Copyright 2019, 2020 Rochester Institute of Technology.
///  All rights reserved.
///
///  Contributor:  Jimmy Dugan
///

#include <iostream>
#include "Textures.h"
#include "Shapes.h"
#include "Utils.h"
#include <SOIL/SOIL.h>

#ifdef __cplusplus
using namespace std;
#endif

GLfloat cap_grey_specExp1 = 20.0f;
GLfloat ground_specExp1 = 10.0f;

GLfloat k[3] = { 0.5f, 0.7f, 1.0f };

GLfloat lpDefault1[4] = { 15.0f, 18.0f, 20.0f, 1.0f };
GLfloat lightpos1[4] = { 15.0f, 18.0f, 20.0f, 1.0f };

// private lighting data
static GLfloat lightcolor1[4] = {  1.0f,  1.0f,  1.0f, 1.0f };
static GLfloat amblight1[4] = {  0.7f,  0.7f,  0.7f, 1.0f };

GLfloat cap_grey_ambient1[4] = { 0.50f, 0.10f, 0.90f, 1.00f };
GLfloat cap_grey_diffuse1[4] = { 0.89f, 0.00f, 0.00f, 1.00f };
GLfloat ground_ambient1[4] = { 0.50f, 0.10f, 0.90f, 1.00f };
GLfloat ground_diffuse1[4] = { 0.89f, 0.00f, 0.00f, 1.00f };
GLfloat specular1[4] = { 1.00f, 1.00f, 1.00f, 1.00f };

///
/// This function initializes all texture-related data structures for
/// the program.  This is where texture buffers should be created, where
/// texture images should be loaded, etc.
///
/// You will need to write this function, and maintain all of the values
/// needed to be sent to the various shaders.
///
void initTextures( void )
{
    int width, height;
    unsigned char *image;
    GLuint tex_silo, tex_barn_wall;
    glGenTextures(1, &tex_silo);
    glGenTextures(1, &tex_barn_wall);
    
    // Load silo texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex_silo);
    image = SOIL_load_image("silo.jpg", &width, &height, 0, SOIL_LOAD_RGB ); // loading the image
    if( image == 0 ) {     
        printf( "SOIL loading error: '%s'\n", SOIL_last_result() ); 
    }
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    SOIL_free_image_data(image);

    // Load barn texture
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, tex_barn_wall);
    image = SOIL_load_image("barnwall.jpg", &width, &height, 0, SOIL_LOAD_RGB );
    if( image == 0 ) {     
        printf( "SOIL loading error: '%s'\n", SOIL_last_result() ); 
    }
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    SOIL_free_image_data(image);
    
}

///
/// This function sets up the parameters for texture use.
///
/// You will need to modify this function, and maintain all of the values
/// needed to be sent to the various shaders.
///
/// @param program The ID of an OpenGL (GLSL) shader program to which
///    parameter values are to be sent
/// @param obj     The object type of the object being drawn
///
void setTextures( GLuint program, int obj )
{
    ///////////////////////////////////////////////////
    // CODE COMMON TO PHONG SHADING AND TEXTURE MAPPING
    //
    // DO NOT REMOVE THIS SECTION OF CODE
    ///////////////////////////////////////////////////

    // Set the specular exponent for the object
    GLint loc  = getUniformLoc( program, "specExp" );
    switch( obj ) {
        case SILO_CAP:
            glUniform1f( loc, cap_grey_specExp1 );
            break;
        case ROUND_BARN_ROOF:
        case MINI_BARN:
        case SILO:
        case SIDE_BARN_ROOF:
            glUniform1f( loc, cap_grey_specExp1 );
            break;
        case ROUND_BARN:  
        case GROUND:
            glUniform1f( loc, ground_specExp1 );
            break;
    }

    // Send down the reflective coefficients
    loc = getUniformLoc( program, "kCoeff" );
    glUniform3fv( loc, 1, k );

    //
    // Add your code here to implement texture mapping.
    //
    switch( obj ) {
        case SILO:
            glUniform1i(glGetUniformLocation(program, "tex"), 0);
            break;
        case ROUND_BARN:
            glUniform1i(glGetUniformLocation(program, "tex"), 1);
            break;
    }

    // Lighting parameters
    loc = getUniformLoc( program, "lightPosition" );
    glUniform4fv( loc, 1, lightpos1 );

    loc = getUniformLoc( program, "lightColor" );
    glUniform4fv( loc, 1, lightcolor1 );

    loc = getUniformLoc( program, "ambientLight" );
    glUniform4fv( loc, 1, amblight1 );
}

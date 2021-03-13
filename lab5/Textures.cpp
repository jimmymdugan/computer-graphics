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

using namespace std;

/// These variables are used in both Phong shading and texture mapping
GLfloat cyl_specExp  = 20.0f;
GLfloat quad_specExp = 50.0f;
GLfloat sph_specExp  = 80.0f;
GLfloat k[3]         = { 0.5f, 0.7f, 1.0f };

/// These variables are used in the framework only when doing Phong
/// shading; they will be unused once you have implemented texture mapping.
GLfloat cyl_ambient[4]      = { 0.50f, 0.10f, 0.90f, 1.00f };
GLfloat cyl_diffuse[4]      = { 0.89f, 0.00f, 0.00f, 1.00f };
GLfloat quad_ambdiffuse[4]  = { 0.10f, 0.85f, 0.20f, 1.00f };
GLfloat sph_ambient[4]      = { 0.50f, 0.50f, 0.50f, 1.00f };
GLfloat sph_diffuse[4]      = { 0.49f, 0.49f, 0.80f, 1.00f };
GLfloat specular[4]         = { 1.00f, 1.00f, 1.00f, 1.00f };

/// Are we doing texture mapping instead of material properties?
bool usingTextures = true;

/// Add any global definitions and/or variables you need here.

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
    // Load happy
    glActiveTexture(GL_TEXTURE0);
    GLuint tex_0 = SOIL_load_OGL_texture("happy.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
                                             SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_TEXTURE_REPEATS);
    // check if happy image was loaded
    if(tex_0 == 0){
        printf( "SOIL loading error with 'happy.png': '%s'\n", SOIL_last_result() );
    }
    
    // Load angry
    glActiveTexture(GL_TEXTURE1);
    GLuint tex_1 = SOIL_load_OGL_texture("angry.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
                                             SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_TEXTURE_REPEATS);
    // check if angry image was loaded
    if(tex_1 == 0){
        printf( "SOIL loading error with 'angry.png': '%s'\n", SOIL_last_result() );
    }
    
    glBindTexture(GL_TEXTURE_2D, tex_0);
    glBindTexture(GL_TEXTURE_2D, tex_1);
    
    // sphere and cyl
    int width, height;
    unsigned char *image;
    
    // cyl curved, cyl end, and sphere
    GLuint tex_2;
    GLuint tex_3;
    GLuint tex_4;
    
    glGenTextures(1, &tex_2);
    glGenTextures(1, &tex_3);
    glGenTextures(1, &tex_4);

    // Load cyl curve
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, tex_2);
    image = SOIL_load_image("wall.png", &width, &height, 0, SOIL_LOAD_RGB );
    
    // check if wall image was loaded
    if( image == 0 ) {
        printf( "SOIL loading error for 'wall.png': '%s'\n", SOIL_last_result() );
    }
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    SOIL_free_image_data(image);

    // Load cyl ends
    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, tex_3);
    image = SOIL_load_image("disc.png", &width, &height, 0, SOIL_LOAD_RGB );
    
    // check if disc image was loaded
    if( image == 0 ) {
        printf( "SOIL loading error for 'disc.png': '%s'\n", SOIL_last_result() );
    }
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    SOIL_free_image_data(image);
    
    // Load Sphere
    glActiveTexture(GL_TEXTURE4);
    glBindTexture(GL_TEXTURE_2D, tex_4);
    image = SOIL_load_image("jupiter.jpg", &width, &height, 0, SOIL_LOAD_AUTO );
    
    // check if jupiter image was loaded
    if( image == 0 ) {
        printf( "SOIL loading error for 'jupiter.jpg': '%s'\n", SOIL_last_result() );
    }
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    SOIL_free_image_data(image);
    
    // since we want textures set this value to true
    usingTextures = true;
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
    GLint loc  = getUniformLoc(program, "specExp");
    switch( obj ) {
    case OBJ_QUAD:
        glUniform1f( loc, quad_specExp );
        break;
    case OBJ_CYLINDER:  // FALL THROUGH
    case OBJ_DISCS:
        glUniform1f( loc, cyl_specExp );
        break;
    case OBJ_SPHERE:
        glUniform1f( loc, sph_specExp );
        break;
    }

    // Send down the reflective coefficients
    loc = getUniformLoc( program, "kCoeff" );
    glUniform3fv( loc, 1, k );

    // Send down the "are we texture mapping?" flag
    loc = getUniformLoc( program, "usingTextures" );
    glUniform1i( loc, usingTextures );

    ///////////////////////////////////////////////////////////
    // CODE DIFFERING BETWEEN PHONG SHADING AND TEXTURE MAPPING
    ///////////////////////////////////////////////////////////

    //
    // Check to see whether or not we are using texture mapping
    // on the object being drawn at the moment.
    //

    if( !usingTextures ) {

        ///////////////////////////////////////////////////////////
        // THIS CODE IS USED ONLY IF TEXTURE MAPPING IS ***NOT***
        // BEING DONE ON THIS OBJECT
        ///////////////////////////////////////////////////////////

        // specular color is identical for the objects
        loc = getUniformLoc( program, "specularColor" );
        glUniform4fv( loc, 1, specular );

        // ambient and diffuse vary from one object to another
        GLint dloc = getUniformLoc( program, "diffuseColor" );
        GLint aloc = getUniformLoc( program, "ambientColor" );

        switch( obj ) {
        case OBJ_QUAD:
            glUniform4fv( aloc, 1, quad_ambdiffuse );
            glUniform4fv( dloc, 1, quad_ambdiffuse );
            break;
        case OBJ_CYLINDER: // FALL THROUGH
        case OBJ_DISCS:
            glUniform4fv( aloc, 1, cyl_ambient );
            glUniform4fv( dloc, 1, cyl_diffuse );
            break;
        case OBJ_SPHERE:
            glUniform4fv( aloc, 1, sph_ambient );
            glUniform4fv( dloc, 1, sph_diffuse );
            break;
        }
    }
    else {
        // if using texture mapping
        GLint loc_f = glGetUniformLocation(program, "tex_f");
        GLint loc_b = glGetUniformLocation(program, "tex_b");
        
        switch( obj ) {
        case OBJ_QUAD:
            glUniform1i(loc_f, 0);
            glUniform1i(loc_b, 1);
            break;
        case OBJ_CYLINDER:
            glUniform1i(loc_f, 2);
            break;
        case OBJ_DISCS:
            glUniform1i(loc_f, 3);
            break;
        case OBJ_SPHERE:
            glUniform1i(loc_f, 4);
            break;
        }
    }
}

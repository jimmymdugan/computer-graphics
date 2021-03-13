///
///  Transforms
///
///  Simple module for setting up the model and camera transformations
///  for the Transformation Assignment.
///
///  Created by Warren R. Carithers 2016/11/11.
///  Updates: 2019/04/04, 2019/10/12 by wrc.
///  Based on code created by Joe Geigel on 1/23/13.
///  Copyright 2019 Rochester Institute of Technology.  All rights reserved.
///
///  Contributor:  Jimmy Dugan
///

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#endif

#ifndef __APPLE__
#include <GL/glew.h>
#endif

#include <GLFW/glfw3.h>

#include "Transforms.h"

/// standard camera information
static GLfloat std_eye[] =    { 0.0f, 0.0f, 0.0f };
static GLfloat std_lookat[] = { 0.0f, 0.0f, -1.0f };
static GLfloat std_up[] =     { 0.0f, 1.0f, 0.0f };

/// default transformations
static GLfloat std_scale[] =  { 1.0f, 1.0f, 1.0f };
static GLfloat std_rotate[] = { 0.0f, 0.0f, 0.0f };
static GLfloat std_xlate[] =  { 0.0f, 0.0f, 0.0f };

/// clipping boundaries: left, right, top, bottom, near, far
static GLfloat bounds[] = { -1.0f, 1.0f, 1.0f, -1.0f, 0.9f, 4.5f };

///
/// This function sets up the view and projection parameters for the
/// desired projection of the scene. See the assignment description for
/// the values for the projection parameters.
///
/// You will need to write this function, and maintain all of the values
/// needed to be sent to the vertex shader.
///
/// @param program - The ID of an OpenGL (GLSL) shader program to which
///    parameter values are to be sent
/// @param mode - The desired projection mode (Frustum or Ortho)
///
void setProjection( GLuint program, ViewMode mode )
{
    //clipping boundaries
    float left = bounds[0];
    float right = bounds[1];
    float top = bounds[2];
    float bottom = bounds[3];
    float near = bounds[4];
    float far = bounds[5];
    
    switch(mode) {
        case Frustum: {
            GLfloat frustumProjection[] {2 * near / (right - left), 0, 0, 0,
            0, 2 * near / (top - bottom), 0, 0,
            (right + left)/(right - left), (top + bottom)/(top - bottom), - (far + near)/(far - near), -1,
            0, 0, (- 2 * far * near)/(far - near), 0};
            glUniformMatrix4fv(glGetUniformLocation(program, "projection"), 1, GL_FALSE, frustumProjection);
            break;
        }
        case Ortho: {
            GLfloat orthoProjection[] {2 / (right - left), 0, 0, 0,
            0, 2 / (top - bottom), 0, 0,
            0, 0, - 2 / (far - near), 0,
            - (right + left)/(right - left), - (top + bottom)/(top - bottom), - (far + near)/(far - near), 1};
            glUniformMatrix4fv(glGetUniformLocation(program, "projection"), 1, GL_FALSE, orthoProjection);
            break;
        }
    }
}

///
/// This function clears any model transformations, setting the values
/// to the defaults.
///
/// You will need to write this function, and maintain all of the values
/// which must be sent to the vertex shader.
///
/// @param program - The ID of an OpenGL (GLSL) shader program to which
///    parameter values are to be sent
///
void clearTransforms( GLuint program )
{
    glUniform3fv(glGetUniformLocation(program, "translateVec"), 1, std_xlate);
    glUniform3fv(glGetUniformLocation(program, "scaleVec"), 1, std_scale);
    glUniform3fv(glGetUniformLocation(program, "rotateVec"), 1, std_rotate);
    
}

///
/// This function sets up the transformation parameters for the vertices
/// of the teapot.  The order of application is specified in the driver
/// program.
///
/// You will need to write this function, and maintain all of the values
/// which must be sent to the vertex shader.
///
/// @param program - The ID of an OpenGL (GLSL) shader program to which
///    parameter values are to be sent
/// @param scale  - scale factors for each axis
/// @param rotate - rotation angles around the three axes, in degrees
/// @param xlate  - amount of translation along each axis
///
void setTransforms( GLuint program, GLfloat scale[],
                    GLfloat rotate[], GLfloat xlate[] )
{
    glUniform3fv(glGetUniformLocation(program, "translateVec"), 1, xlate);
    glUniform3fv(glGetUniformLocation(program, "scaleVec"), 1, scale);
    glUniform3fv(glGetUniformLocation(program, "rotateVec"), 1, rotate);
}

///
/// This function clears any changes made to camera parameters, setting the
/// values to the defaults.
///
/// You will need to write this function, and maintain all of the values
/// which must be sent to the vertex shader.
///
/// @param program - The ID of an OpenGL (GLSL) shader program to which
///    parameter values are to be sent
///
void clearCamera( GLuint program )
{
    glUniform3fv(glGetUniformLocation(program, "eye"), 1, std_eye);
    glUniform3fv(glGetUniformLocation(program, "lookat"), 1, std_lookat);
    glUniform3fv(glGetUniformLocation(program, "up"), 1, std_up);
}

///
/// This function sets up the camera parameters controlling the viewing
/// transformation.
///
/// You will need to write this function, and maintain all of the values
/// which must be sent to the vertex shader.
///
/// @param program - The ID of an OpenGL (GLSL) shader program to which
///    parameter values are to be sent
/// @param eye    - camera location
/// @param lookat - lookat point
/// @param up     - the up vector
///
void setCamera( GLuint program, GLfloat eye[], GLfloat lookat[], GLfloat up[] )
{
    glUniform3fv(glGetUniformLocation(program, "eye"), 1, eye);
    glUniform3fv(glGetUniformLocation(program, "lookat"), 1, lookat);
    glUniform3fv(glGetUniformLocation(program, "up"), 1, up);
}

///
//  Application.h
//
//  Assignment-specific code for this assignment.
//
//  Created by Warren R. Carithers on 2019/09/09.
//  Based on earlier versions created by Joe Geigel and Warren R. Carithers
//  Copyright 2019 Rochester Institute of Technology. All rights reserved.
//
///  Contributor:  Jimmy Dugan
//

#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include <cstdlib>
#include <iostream>

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#endif

//
// GLEW and GLFW header files also pull in the OpenGL definitions
//

#ifndef __APPLE__
#include <GL/glew.h>
#endif

#include <GLFW/glfw3.h>

#include "Buffers.h"
#include "Canvas.h"

///
// PUBLIC GLOBALS
///

// scale & translate vectors for objects
extern GLfloat silo_s[3];
extern GLfloat silo_x[3];
extern GLfloat silo_cap_s[3];
extern GLfloat silo_cap_x[3];
extern GLfloat round_barn_s[3];
extern GLfloat round_barn_x[3];
extern GLfloat round_barn_roof_s[3];
extern GLfloat round_barn_roof_x[3];
extern GLfloat mini_barn_s[3];
extern GLfloat mini_barn_x[3];
extern GLfloat mini_barn_roof_s[3];
extern GLfloat mini_barn_roof_x[3];
extern GLfloat side_barn_s[3];
extern GLfloat side_barn_x[3];
extern GLfloat side_barn_roof_s[3];
extern GLfloat side_barn_roof_x[3];
extern GLfloat ground_s[3];
extern GLfloat ground_x[3];
extern GLfloat back_barn_s[3];
extern GLfloat back_barn_x[3];
extern GLfloat back_barn_roof_s[3];
extern GLfloat back_barn_roof_x[3];
extern GLfloat window_barn_s[3];
extern GLfloat window_barn_x[3];
extern GLfloat window_barn_roof_s[3];
extern GLfloat window_barn_roof_x[3];
extern GLfloat round_barn_window_s[3];
extern GLfloat round_barn_window_x[3];
extern GLfloat mini_barn_window_s[3];
extern GLfloat mini_barn_window_x[3];

///
// Drawing-related variables
///

// dimensions of the drawing window
extern int w_width;
extern int w_height;

// drawing window title
extern const char *w_title;

// GL context we're using (we assume 3.0, for GLSL 1.30)
extern int gl_maj;
extern int gl_min;

// our GLFWwindow
extern GLFWwindow *w_window;

// our Canvas
extern Canvas *canvas;

// shader programs
extern GLuint program, flat, phong, textures;

void application( int argc, char *argv[] );

#endif

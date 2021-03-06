#version 120

//
// Vertex shader for FLAT shading.
//
// @author  RIT CS Department
// @author  Jimmy Dugan
//

//
// Vertex attributes
//

// Vertex location (in model space)
attribute vec4 vPosition;

// Normal vector at vertex (in model space)
attribute vec3 vNormal;

//
// Uniform data
//

// Camera and projection matrices
uniform mat4 vMat;  // view (camera)
uniform mat4 pMat;  // projection

// Model transformation matrices
uniform mat4 tMat;  // translation
uniform mat4 sMat;  // scaling
uniform mat4 xMat;  // x rotation
uniform mat4 yMat;  // y rotation
uniform mat4 zMat;  // z rotation

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
// Light source color
uniform vec4 ls_color;
// Light source position
uniform vec4 ls_position;
// Ambient light color
uniform vec4 ls_ambient_color;

// outgoing color vector to frag shader
varying vec4 color;

//
// Inversion function for 3x3 matrices by Mikola Lysenko.
// Origin: https://github.com/glslify/glsl-inverse/blob/master/index.glsl
//
// The MIT License (MIT)
//
// Copyright (c) 2014 Mikola Lysenko
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
// OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
// OTHER DEALINGS IN THE SOFTWARE.
//

mat3 inverse(mat3 m) {
  float a00 = m[0][0], a01 = m[0][1], a02 = m[0][2];
  float a10 = m[1][0], a11 = m[1][1], a12 = m[1][2];
  float a20 = m[2][0], a21 = m[2][1], a22 = m[2][2];

  float b01 = a22 * a11 - a12 * a21;
  float b11 = -a22 * a10 + a12 * a20;
  float b21 = a21 * a10 - a11 * a20;

  float det = a00 * b01 + a01 * b11 + a02 * b21;

  return mat3(b01, (-a22 * a01 + a02 * a21), (a12 * a01 - a02 * a11),
              b11, (a22 * a00 - a02 * a20), (-a12 * a00 + a02 * a10),
              b21, (-a21 * a00 + a01 * a20), (a11 * a00 - a01 * a10)) / det;
}

void main()
{
    // create the model and modelview matrices
    // transformation order: scale, rotate Z, rotate Y, rotate X, translate
    mat4 modelMat = tMat * xMat * yMat * zMat * sMat;
    mat4 modelViewMat = vMat * modelMat;

    // normal and light source vectors
    vec4 normal_vec = normalize(vec4(transpose(inverse(mat3(modelViewMat))) * vNormal, 0)); 
    vec4 light_vec = normalize((vMat * ls_position) - (modelViewMat * vPosition)); 

    // color components
    vec4 ambient = ls_ambient_color * ambient_reflect_coef * ambient_color;
    vec4 diffuse = diffuse_reflect_coef * diffuse_color * max(dot(normal_vec, light_vec), 0);
    
    // outgoing color sent to frag shader
    color = ambient + ls_color * diffuse; 

    gl_Position =  pMat * modelViewMat * vPosition;
}

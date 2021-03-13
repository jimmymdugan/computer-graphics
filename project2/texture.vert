#version 120

//
// Vertex shader for TEXTURE shading.
//
// @author  RIT CS Department
// @author  Jimmy Dugan
//

//
// Vertex attributes
//


attribute vec4 vPosition;
attribute vec3 vNormal;
attribute vec2 vTexCoord;

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

uniform vec4 lightPosition;

varying vec3 lPos;
varying vec3 vPos;
varying vec3 vNorm;

//outgoing
varying vec2 texCoord;

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
    mat4 modelMat = tMat * xMat * yMat * zMat * sMat;
    mat4 modelViewMat = vMat * modelMat;

    vec4 vert_eye = modelViewMat * vPosition;
    vec4 light_eye = vMat * lightPosition;

    mat3 norm = inverse( transpose( mat3(modelViewMat) ) );
    vec4 norm_eye = vec4( norm * vNormal, 0.0 );

    lPos = light_eye.xyz;
    vPos = vert_eye.xyz;
    vNorm = norm_eye.xyz;

    texCoord = vTexCoord;

    gl_Position =  pMat * modelViewMat * vPosition;
}

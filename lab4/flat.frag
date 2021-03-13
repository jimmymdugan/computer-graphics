#version 120

//
// Fragment shader for FLAT shading.
//
// @author  RIT CS Department
// @author  Jimmy Dugan
//

// incoming color vec
varying vec4 color;

void main()
{
    gl_FragColor = color;
}

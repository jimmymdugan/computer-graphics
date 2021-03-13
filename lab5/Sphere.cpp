///
///  Sphere.cpp
///
///  Code for drawing the sphere.
///
///  Created by Warren R. Carithers 2019/11/23.
///  Updates:  2020/11/10 by wrc
///  Copyright 2019, 2020 Rochester Institute of Technology.
///  All rights reserved.
///
///  Contributor:  Jimmy Dugan
///

#include <cmath>
#include "Canvas.h"
#include "SphereData.h"
#include "Sphere.h"

using namespace std;

///
/// makeSphere() - create a sphere object
///
void makeSphere( Canvas &C )
{
    for( int i = 0; i < sphereElementsLength - 2; i += 3 ) {

        // Calculate the base indices of the three vertices
        int point1 = sphereElements[i];
        int point2 = sphereElements[i + 1];
        int point3 = sphereElements[i + 2];

        Vertex p1 = sphereVertices[point1];
        Vertex p2 = sphereVertices[point2];
        Vertex p3 = sphereVertices[point3];

        // Calculate the surface normals
        // We just re-use the point indices because the normals
        // for points on a sphere are equal to the coordinates
        // of the points themselves.
        Normal n1 = { sphereVertices[point1].x,
                      sphereVertices[point1].y,
                      sphereVertices[point1].z };

        Normal n2 = { sphereVertices[point2].x,
                      sphereVertices[point2].y,
                      sphereVertices[point2].z };

        Normal n3 = { sphereVertices[point3].x,
                      sphereVertices[point3].y,
                      sphereVertices[point3].z };

        // Add triangle and vertex normals
        C.addTriangleWithNorms( p1, n1, p2, n2, p3, n3 );
        
        TexCoord p1_c = {0.00, 0.00};
        TexCoord p2_c = {0.00, 0.00};
        TexCoord p3_c = {0.00, 0.00};
        
        float pi = 3.141592654;
        float u;
        float v;
        
        //p1
        u = atan(p1.x / p1.z)/pi;
        p1_c.u  = u;
        v = acos(p1.y * 2.0)/pi;
        p1_c.v = 1.0 - v; // invert
        
        //p2
        u = atan(p2.x / p2.z)/pi;
        p2_c.u  = u;
        v = acos(p2.y * 2.0)/pi;
        p2_c.v = 1.0 - v; // invert
        
        //p3
        u = atan(p3.x / p3.z)/pi;
        p3_c.u  = u;
        v = acos(p3.y * 2.0)/pi;
        p3_c.v = 1.0 - v; // invert
        
        C.addTextureCoords(p1_c, p2_c, p3_c);
    }
}

///
///  Cylinder.cpp
///
///  Code for drawing the cylinder.
///
///  Created by Warren R. Carithers 2019/11/23.
///  Updates:  2020/11/10 by wrc
///  Copyright 2019, 2020 Rochester Institute of Technology.
///  All rights reserved.
///
///  Contributor:  Jimmy Dugan
///

#include <cmath>
#include <iostream>
#include "Canvas.h"
#include "CylinderData.h"
#include "Cylinder.h"

using namespace std;

///
/// makeCylinder() - create the cylinder body
///
void makeCylinder( Canvas &C )
{
    // Only use the vertices for the body itself
    for( int i = body.first; i <= body.last - 2; i += 3 ) {

        // Calculate the base indices of the three vertices
        int point1 = cylinderElements[i];
        int point2 = cylinderElements[i + 1];
        int point3 = cylinderElements[i + 2];

        Vertex p1 = cylinderVertices[point1];
        Vertex p2 = cylinderVertices[point2];
        Vertex p3 = cylinderVertices[point3];

        // Calculate the normal vectors for each vertex
        Normal n1, n2, n3;

        // Normals on the body run from the axis to the vertex, and
        // are in the XZ plane; thus, for a vertex at (Px,Py,Pz), the
        // corresponding point on the axis is (0,Py,0), and the normal is
        // P - Axis, or just (Px,0,Pz).

        n1 = (Normal) { p1.x, 0.0f, p1.z };
        n2 = (Normal) { p2.x, 0.0f, p2.z };
        n3 = (Normal) { p3.x, 0.0f, p3.z };

        // Add this triangle to the collection
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
        v = p1.y + 0.5;
        p1_c.v = 1.0 - v; // invert
        
        //p2
        u = atan(p2.x / p2.z)/pi;
        p2_c.u  = u;
        v = p2.y + 0.5;
        p2_c.v = 1.0 - v; // invert
        
        //p3
        u = atan(p3.x / p3.z)/pi;
        p3_c.u  = u;
        v = p3.y + 0.5;
        p3_c.v = 1.0 - v; // invert
        
        C.addTextureCoords(p1_c, p2_c, p3_c);
    }
}

///
/// makeDiscs() - create the cylinder discs
///
void makeDiscs( Canvas &C )
{
    // Only use the vertices for the top and bottom discs

    for( int disc = 0; disc < 2; ++disc ) {

        // Select the starting and ending indices, and create the surface
        // normal for this disc.  For the top and bottom, the normals are
        // parallel to the Y axis.  Points on the disk all have Y == 0.5,
        // and those on the bottom have Y == -0.5.
        int first, last;
        Normal nn;

        if( disc == 0 ) { // bottom disc
            first = bdisc.first;
            last  = bdisc.last;
            nn = (Normal) { 0.0f, -1.0f, 0.0f };
        } else {
            first = tdisc.first;
            last  = tdisc.last;
            nn = (Normal) { 0.0f, 1.0f, 0.0f };
        }

        // Create the triangles
        for( int i = first; i <= last - 2; i += 3 ) {

            // Calculate the base indices of the three vertices
            int point1 = cylinderElements[i];
            int point2 = cylinderElements[i + 1];
            int point3 = cylinderElements[i + 2];

            Vertex p1 = cylinderVertices[point1];
            Vertex p2 = cylinderVertices[point2];
            Vertex p3 = cylinderVertices[point3];

            // Add this triangle to the collection
            C.addTriangleWithNorms( p1, nn, p2, nn, p3, nn );
            
            TexCoord p1_c = {0.00, 0.00};
            TexCoord p2_c = {0.00, 0.00};
            TexCoord p3_c = {0.00, 0.00};
            
            float u;
            float v;
            
            //p1
            u = p1.x + 0.5;
            p1_c.u  = u;
            v = p1.z + 0.5;
            p1_c.v = 1.0 - v; // invert
            
            //p2
            u = p2.x + 0.5;
            p2_c.u  = u;
            v = p2.z + 0.5;
            p2_c.v = 1.0 - v; // invert
            
            //p3
            u = p3.x + 0.5;
            p3_c.u  = u;
            v = p3.z + 0.5;
            p3_c.v = 1.0 - v; // invert
            
            C.addTextureCoords(p1_c, p2_c, p3_c);
        }
    }
}

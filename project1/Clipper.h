///
//  Clipper.h
//
//  Simple module that performs clipping
//
//  Created by Warren R. Carithers on 02/27/14.
//  Last updated 2019/02/16 by wrc.
//  Based on a C++ version created by Joe Geigel on 11/30/11.
//  Copyright 2011 Rochester Institute of Technology. All rights reserved.
//
//  This code can be compiled as either C or C++.
//
//  Contributor:  Jimmy Dugan
///

#ifndef _CLIPPER_H_
#define _CLIPPER_H_

#include "Types.h"
#include <vector>

//struct to hold edge information
struct edge {
    Vertex p1;
    Vertex p2;
} ;


///
// clipPolygon
//
// Clip the polygon with vertex count in and vertices inV against the
// rectangular clipping region specified by lower-left corner ll and
// upper-right corner ur. The resulting vertices are placed in outV.
//
// The routine should return the with the vertex count of polygon
// resulting from the clipping.
//
// @param num   the number of vertices in the polygon to be clipped
// @param inV   the incoming vertex list
// @param outV  the outgoing vertex list
// @param ll    the lower-left corner of the clipping rectangle
// @param ur    the upper-right corner of the clipping rectangle
//
// @return number of vertices in the polygon resulting after clipping
//
///
int clipPolygon( int num, const Vertex inV[], Vertex outV[],
                 Vertex ll, Vertex ur );

///
// shClip
//
// shClip takes in a vector of vertices and the current edge. If a
// vertex is inside the clipping region it is added to the final vertices vector
//
// The routine should return the with the list of vertices after clipping
//
// @param inV       the incoming vertex list
// @param currEdge  the current edge each vertex is compared to
//
// @return vector of vertices in the polygon resulting after clipping
///
vector<Vertex> shClip(vector<Vertex> inV, edge currEdge);


///
// getIntersectionPoint
//
// getIntersectionPoint takes in two vertices and the current edge and
// finds the intersection point of these who lines
//
// The routine should return the intersection point between the two lines
//
// @param p1        the P vertex in the shape
// @param p2        the S vertex in the shape
// @param currEdge  the current edge each vertex is compared to
//
// @return the vertex for the intersection point
///
Vertex getIntersectionPoint (Vertex p1, Vertex p2, edge currEdge);


///
// isInside
//
// isInside takes in the current vertex and the current edge and determines
// if the current vertex is inside that edge based on different scenarios
//
// The routine should return a boolean value based on if the vertex is inside
// the given edge.
//
// @param currVertex    the current vertex being compared to the given edge
// @param currEdge      the current edge each vertex is compared to
//
// @return the vertex for the intersection point
///
bool isInside(Vertex currVertex, edge edge);

#endif

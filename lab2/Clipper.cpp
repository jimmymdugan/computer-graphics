///
//  Clipper
//
//  Simple module that performs clipping
//
//  Created by Warren R. Carithers on 01/15/14.
//  Updates: 2019/02/16, 2019/09/17 by wrc.
//  Based on a C++ version created by Joe Geigel on 11/30/11.
//  Copyright 2019 Rochester Institute of Technology. All rights reserved.
//
//  This code can be compiled as either C or C++.
//
//  Contributor:  Jimmy Dugan
///

#ifdef __cplusplus
using namespace std;
#else
#include <stdbool.h>
#endif

#include "Types.h"
#include "Clipper.h"


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
///
int clipPolygon( int num, const Vertex inV[], Vertex outV[],
                 Vertex ll, Vertex ur )
{
    //load initial vertices into vector
    vector<Vertex> initialVector;
    initialVector.insert(initialVector.end(), &inV[0], &inV[num]);
    
    //left edge
    edge leftEdge;
    leftEdge.p1 = {ll.x, ur.y};        //top left vertex
    leftEdge.p2 = {ll.x, ll.y};        //bottom left vertex
    vector<Vertex> postLeftClipVerts = shClip(initialVector, leftEdge);
    
    //bottom edge
    edge bottomEdge;
    bottomEdge.p1 = {ll.x, ll.y};      //bottom left vertex
    bottomEdge.p2 = {ur.x, ll.y};      //bottom right vertex
    vector<Vertex> postBottomClipVerts = shClip(postLeftClipVerts, bottomEdge);
    
    //right edge
    edge rightEdge;
    rightEdge.p1 = {ur.x, ll.y};       //bottom right vertex
    rightEdge.p2 = {ur.x, ur.y};       //top right vertex
    vector<Vertex> postRightClipVerts = shClip(postBottomClipVerts, rightEdge);
    
    //top edge
    edge topEdge;
    topEdge.p1 = {ur.x, ur.y};         //top right vertex
    topEdge.p2 = {ll.x, ur.y};         //top left vertex
    vector<Vertex> finalVertexList = shClip(postRightClipVerts, topEdge);
    
    //load final vector verticies into final array
    copy(finalVertexList.begin(), finalVertexList.end(), outV);
    
    //the final vector count in the clipped image
    int finalVertexCount = (int)finalVertexList.size();
    
    return(finalVertexCount);
}

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
vector<Vertex> shClip(vector<Vertex> inV, edge currEdge){
    Vertex sVertex;
    Vertex pVertex;
    Vertex intersectVertex;
    vector<Vertex> tempVOutList;
    int vertexCount = (int)inV.size();
    
    if(vertexCount){
        // vertex p in line segment
        pVertex = inV.back();
    }
    for(int vertexIter = 0; vertexIter < vertexCount; vertexIter++){
        // vertex s in line segment
        sVertex = inV[vertexIter];
        if(isInside(sVertex, currEdge)){
            // if the vertex is inside of the current edge
            if(isInside(pVertex, currEdge)){
                tempVOutList.push_back(sVertex);
            }else{
                // find the intersection and add vertex s and intersection to final vertices
                intersectVertex = getIntersectionPoint(pVertex, sVertex, currEdge);
                tempVOutList.push_back(intersectVertex);
                tempVOutList.push_back(sVertex);
            }
        }else{
            if(isInside(pVertex, currEdge)){
                intersectVertex = getIntersectionPoint(pVertex, sVertex, currEdge);
                tempVOutList.push_back(intersectVertex);
            }
        }
        //update the new point to compare each vertex to
        pVertex = sVertex;
    }
    return tempVOutList;
}

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
Vertex getIntersectionPoint (Vertex p1, Vertex p2, edge currEdge){
    Vertex intersectPoint;
    Vertex currEdgeP1 = currEdge.p1;
    Vertex currEdgeP2 = currEdge.p2;
    float slope = (p2.y - p1.y)/(p2.x-p1.x);
    
    //horiz
    if(currEdgeP1.y == currEdgeP2.y){
        intersectPoint.x = p1.x + (currEdgeP1.y - p1.y) / slope;
        intersectPoint.y = currEdgeP1.y;
        return intersectPoint;
    }
    //vert
    else{
        intersectPoint.x = currEdgeP1.x;
        intersectPoint.y = p1.y + (currEdgeP1.x - p1.x) * slope;
        return intersectPoint;
    }
}

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
bool isInside(Vertex currVertex, edge currEdge){
    Vertex currEdgeP1 = currEdge.p1;
    Vertex currEdgeP2 = currEdge.p2;
    //bottom
    if(currEdgeP2.x > currEdgeP1.x){
        if(currVertex.y >= currEdgeP1.y){
            return true;
        }
    }
    //top
    if(currEdgeP2.x < currEdgeP1.x){
        if(currVertex.y <= currEdgeP1.y){
            return true;
        }
    }
    //right
    if(currEdgeP2.y > currEdgeP1.y){
        if(currVertex.x <= currEdgeP2.x){
            return true;
        }
    }
    //left
    if(currEdgeP2.y < currEdgeP1.y){
        if(currVertex.x >= currEdgeP2.x){
            return true;
        }
    }
    return false;
}

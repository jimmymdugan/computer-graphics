///
//  Rasterizer.cpp
//
//  Simple module that provides rasterization algorithms
//
//  Created by Joe Geigel on 11/30/11.
//  Updates: 2019/02/09, 2019/09/14 by wrc.
//  Copyright 2019 Rochester Institute of Technology. All rights reserved.
//
//  Contributor:  Jimmy Dugan
///

#include <list>
#include <algorithm>
#include <iostream>
#include <vector>
#include <math.h>
#include "Types.h"
#include "Rasterizer.h"
#include "Canvas.h"

using namespace std;

///
// Constructor
//
// @param n number of scanlines
// @param C The Canvas to use
///
Rasterizer::Rasterizer(int n, Canvas & canvas): n_scanlines(n), C(canvas) {

}

///
// Draw a filled polygon.
//
// Implementation should use the scan-line polygon fill algorithm
// discussed in class.
//
// The polygon has n distinct vertices.  The coordinates of the vertices
// making up the polygon are supplied in the 'v' array parameter, such
// that the ith vertex is in v[i].
//
// You are to add the implementation here using only calls to the
// addPixel() function.
//
// @param n - number of vertices
// @param v - array of vertices
///
void Rasterizer::drawPolygon(int n, const Vertex v[]) {
    //max canvas Y value
    int maxYVal = 600;

    //initial edge list and active edges list
    list <edge> edgeList[maxYVal];
    list <edge> activeEdgeTable = list<edge>();
    
    // for all vertices, create edges with neighboring points
    for (int vertexIter = 0; vertexIter < n; vertexIter++) {
        edge e;
        int currMinYVal;
        Vertex edgeP1;
        Vertex edgeP2;
        //compare last vertex with first
        if (vertexIter == n - 1) {
            edgeP1 = v[0];
            edgeP2 = v[vertexIter];
            //horizontal
            if (edgeP1.y == edgeP2.y) {
                continue;
            } else if (edgeP1.y < edgeP2.y) {
                currMinYVal = edgeP1.y;
                e.xVal = edgeP1.x;
                e.maxYValue = edgeP2.y;
            } else {
                currMinYVal = edgeP2.y;
                e.xVal = edgeP2.x;
                e.maxYValue = edgeP1.y;
            }
        } else {
            edgeP1 = v[vertexIter];
            edgeP2 = v[vertexIter + 1];
            //horizontal
            if (edgeP1.y == edgeP2.y) {
                continue;
            }
            if (edgeP1.y < edgeP2.y) {
                currMinYVal = edgeP1.y;
                e.xVal = edgeP1.x;
                e.maxYValue = edgeP2.y;
            } else {
                currMinYVal = edgeP2.y;
                e.xVal = edgeP2.x;
                e.maxYValue = edgeP1.y;
            }
        }
        e.slopeRecip = (edgeP2.x - edgeP1.x) / (edgeP2.y - edgeP1.y);
        edgeList[currMinYVal].push_back(e);
    }

    // iterate over all scan lines
    for (int yValIter = 0; yValIter < maxYVal; yValIter++) {

        //remove values from active edge table if the max Y value is equal to the current scan line
        for (auto activeTableIter = activeEdgeTable.begin(); activeTableIter != activeEdgeTable.end(); activeTableIter++) {
            edge currActiveEdge = * activeTableIter;
            if (currActiveEdge.maxYValue == yValIter) {
                activeEdgeTable.erase(activeTableIter);
            }
        }

        //initialize active edge table from current scan line value (where y values are equal to current scan line value)
        for (auto edgeListIter = edgeList[yValIter].begin(); edgeListIter != edgeList[yValIter].end(); edgeListIter++) {
            edge currEdge = * edgeListIter;
            activeEdgeTable.push_back(currEdge);
        }

        //sort the active edge table by the x value if the x values are the same then sort the values by the slope recip
        for (auto activeTableIter = activeEdgeTable.begin(); activeTableIter != activeEdgeTable.end(); advance(activeTableIter, 2)) {
            edge currActiveEdge = * activeTableIter;
            if (activeEdgeTable.size() > 1) {
                auto nextEdgeIter = next(activeTableIter, 1);
                edge nextActiveEdge = * nextEdgeIter;
            if (currActiveEdge.xVal > nextActiveEdge.xVal) {
                iter_swap(activeTableIter, nextEdgeIter);
            } else if ((currActiveEdge.xVal == nextActiveEdge.xVal) && (currActiveEdge.slopeRecip > nextActiveEdge.slopeRecip)) {
                iter_swap(activeTableIter, nextEdgeIter);
                }
            }
        }

        //iterate through each pair of edges in the active edge table and determine the start and end indices for where a line must be drawn.
        for (auto activeTableIter = activeEdgeTable.begin(); activeTableIter != activeEdgeTable.end(); advance(activeTableIter, 2)) {
            auto nextEdgeIter = next(activeTableIter, 1);
            edge currEdge = * activeTableIter;
            edge nextEdge = * nextEdgeIter;
            float startIndex = floor(currEdge.xVal);
            float endIndex = ceil(nextEdge.xVal);

            for (int xValIter = startIndex; xValIter <= endIndex; xValIter++) {
                Vertex v = {
                    float(xValIter),
                    float(yValIter)};
                C.addPixel(v);
            }
        }

        //update active table x values with the slope recip for each edge in the active edge table
        for (auto activeTableIter = activeEdgeTable.begin(); activeTableIter != activeEdgeTable.end(); advance(activeTableIter, 1)) {
            float currXVal = activeTableIter -> xVal;
            float currSlopeRecip = activeTableIter -> slopeRecip;
            activeTableIter -> xVal = currXVal + currSlopeRecip;
        }
    }
}

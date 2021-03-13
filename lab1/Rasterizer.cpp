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
Rasterizer::Rasterizer( int n, Canvas &canvas ) : n_scanlines(n), C(canvas)
{
    
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
void Rasterizer::drawPolygon( int n, const Vertex v[] )
{
    const int maxHeight = 600;
    
    //List of edges created from neighboring vertices
    vector<edge> edgeList;
    
    //initialize edges with values invluding min and max X and Y values and the slope reciprical
    for(int i = 0; i < n; i++){
        edge e;
        //compare last vertex with first
        if(i == n-1){
            if(v[i].y < v[0].y){
                e.minYValue = v[i].y;
                e.xValforMinY = v[i].x;
                e.maxYValue = v[0].y;
            }else{
                e.minYValue = v[0].y;
                e.xValforMinY = v[0].x;
                e.maxYValue = v[i].y;
            }
            //find min and max x values
            if(v[i].x < v[0].x){
                e.minXValue = v[i].x;
                e.maxXValue = v[0].x;
            }else{
                e.minXValue = v[0].x;
                e.maxXValue = v[i].x;
            }
            float slopeRecip = (v[i].x - v[0].x) / (v[i].y - v[0].y);
            e.slopeRecip = slopeRecip;
        }else{
            if(v[i].y < v[i+1].y){
                e.minYValue = v[i].y;
                e.xValforMinY = v[i].x;
                e.maxYValue = v[i+1].y;
            }else{
                e.minYValue = v[i+1].y;
                e.xValforMinY = v[i+1].x;
                e.maxYValue = v[i].y;
            }
            //find min and max x values
            if(v[i].x < v[i+1].x){
                e.minXValue = v[i].x;
                e.maxXValue = v[i+1].x;
            }else{
                e.minXValue = v[i+1].x;
                e.maxXValue = v[i].x;
            }
            float slopeRecip = (v[i+1].x - v[i].x) / (v[i+1].y - v[i].y);
            e.slopeRecip = slopeRecip;
        }
        //add edge to edge list if the slope is not 0 (slope inverse is not inf or nan)
        if(!isinf(e.slopeRecip) && !isnan(e.slopeRecip)){
            edgeList.push_back(e);
        }
    }
    
    //the active edge table is used to keep track of edges for a given scan line
    //for each scan line this vector is updated with the required edges
    vector<edge> activeEdgeTable;
    
    //fill polygon
    for(int y = 0; y<maxHeight ;y++){
        
        //remove values from active edge table if the max Y value is equal to the current scan line
        for(int i = 0; i<activeEdgeTable.size();i++){
            if(activeEdgeTable[i].maxYValue == y){
                activeEdgeTable.erase(activeEdgeTable.begin()+i);
            }
        }
        
        //initialize active edge table from current scan line value (where y values are equal to current scan line value)
        for(int i=0; i< edgeList.size();i++){
            edge currentEdge = edgeList[i];
            if(currentEdge.minYValue == y){
                activeEdgeTable.push_back(currentEdge);
            }
        }
        
        //sort the active edge table, if the x values for the minimum Y value are the same then sort the values by the recip
        //otherwise, sort the edges by the x value
        sort(activeEdgeTable.begin(), activeEdgeTable.end(),
            [](const edge & a, const edge & b) -> bool
        {
            if(a.xValforMinY == b.xValforMinY){
                return a.slopeRecip <= b.slopeRecip;
            }else{
                return a.xValforMinY <= b.xValforMinY;
            }
        });

        if(activeEdgeTable.size()>0){
            //iterate through each pair of edges in the active edge table and determine the start and end indices for where a line must be drawn.
            for(int i = 0; i<activeEdgeTable.size()-1; i++){
                int startIndex = activeEdgeTable[i].xValforMinY;
                int endIndex = activeEdgeTable[i+1].xValforMinY;
                i++;
                for(int j = floor(startIndex); j<= ceil(endIndex); j++){
                    Vertex v = {float(j), float(y)};
                    C.addPixel(v);
                }
            }
        }
        
        //update active table x values with the slope recip for each edge in the active edge table
        for(int i = 0; i< activeEdgeTable.size();i++){
            activeEdgeTable[i].xValforMinY += activeEdgeTable[i].slopeRecip;
        }
        
        //sort the edges again since the sum of the x values and slope recip may have changed the required order
        sort(activeEdgeTable.begin(), activeEdgeTable.end(),
            [](const edge & a, const edge & b) -> bool
        {
            if(a.xValforMinY == b.xValforMinY){
                return a.slopeRecip <= b.slopeRecip;
            }else{
                return a.xValforMinY <= b.xValforMinY;
            }
        });
        }
    }

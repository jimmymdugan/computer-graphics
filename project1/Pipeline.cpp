///
///  Pipeline.cpp
///
///  Created by Warren R. Carithers on 2016/10/19.
///  Based on a version created by Joe Geigel on 11/30/11.
///  Updates: 2019/02/25, 2019/10/01 by wrc.
///  Copyright 2019 Rochester Institute of Technology. All rights reserved.
///
///  Contributor:  Jimmy Dugan
///

#ifdef __cplusplus
using namespace std;
#else
#include <stdbool.h>
#endif
#include <iostream>
#include "Pipeline.h"
#include "Rasterizer.h"
#include "Clipper.h"
#include <math.h>

///
/// Simple wrapper class for midterm assignment
///
/// Only methods in the implementation file whose bodies
/// contain the comment
///
///    // YOUR IMPLEMENTATION HERE
///
/// are to be modified by students.
///

///
/// Constructor
///
/// @param w width of canvas
/// @param h height of canvas
///
Pipeline::Pipeline(int w, int h): Canvas(w, h) {
    float identityMatrix[] {
        1, 0, 0,
        0, 1, 0,
        0, 0, 1
    };
    modelTransformation = Matrix(3, 3, identityMatrix);
    normTransformation = Matrix(3, 3, identityMatrix);
    viewPortTransformation = Matrix(3, 3, identityMatrix);
}

///
/// addPoly - Add a polygon to the canvas.  This method does not draw
///           the polygon, but merely stores it for later drawing.
///           Drawing is initiated by the drawPoly() method.
///
///           Returns a unique integer id for the polygon.
///
/// @param n - Number of vertices in polygon
/// @param p - Array containing the vertices of the polygon to be added.
///
/// @return a unique integer identifier for the polygon
///
int Pipeline::addPoly(int n,
    const Vertex p[]) {
    vector < Vertex > tempVector;
    tempVector.insert(tempVector.end(), & p[0], & p[n]);
    polyRepository.push_back(tempVector);
    return polyID++;
}

///
/// drawPoly - Draw the polygon with the given id.  The polygon should
///            be drawn after applying the current transformation to
///            the vertices of the polygon.
///
/// @param polyID - the ID of the polygon to be drawn.
///
void Pipeline::drawPoly(int polyID) {
    vector < Vertex > polyPoints = polyRepository.at(polyID);
    int numberOfPoints = int(polyPoints.size());
    Vertex pointsArr[numberOfPoints];
    copy(polyPoints.begin(), polyPoints.end(), pointsArr);
    

    //apply model transformation
    Matrix modelTransformedMatrices[numberOfPoints];
    applyTransformation(numberOfPoints, pointsArr, modelTransformedMatrices, modelTransformation);
    Vertex postModelTransVertices[numberOfPoints];
    convertMatrixToVertexArray(numberOfPoints, modelTransformedMatrices, postModelTransVertices);

    //apply normalization transformation
    Matrix normTransformedMatrices[numberOfPoints];
    applyTransformation(numberOfPoints, postModelTransVertices, normTransformedMatrices, normTransformation);
    Vertex postNormalizationVertices[numberOfPoints];
    convertMatrixToVertexArray(numberOfPoints, normTransformedMatrices, postNormalizationVertices);

    //apply clipping
    Vertex postClippedVertices[numberOfPoints * 2];
    int numberOfPointsPostClip = clipPolygon(numberOfPoints, postNormalizationVertices, postClippedVertices,
                                 Vertex {-1, -1}, Vertex {1, 1});

    //apply viewport transformation
    Matrix viewPortTransformedMatrices[numberOfPointsPostClip];
    applyTransformation(numberOfPointsPostClip, postClippedVertices, viewPortTransformedMatrices, viewPortTransformation);
    Vertex finalVertices[numberOfPointsPostClip];
    convertMatrixToVertexArray(numberOfPointsPostClip, viewPortTransformedMatrices, finalVertices);

    Rasterizer rasterizer = Rasterizer(numberOfPointsPostClip, * this);
    rasterizer.drawPolygon(numberOfPointsPostClip, finalVertices);
}

///
/// convertMatrixToVertexArray - convert the matrices to an array of vertices
/// @param n - number of incoming vertices in the matrix array
/// @param inM - incoming array of matrices
/// @param outV - outgoing vertices array
///
void Pipeline::convertMatrixToVertexArray(int n, Matrix inM[], Vertex outV[]) {
    for (int matrixIter = 0; matrixIter < n; matrixIter++) {
        float currXVal = inM[matrixIter][0][0];
        float currYVal = inM[matrixIter][1][0];
        outV[matrixIter] = Vertex {
            currXVal,
            currYVal
        };
    }
}

///
/// applyTransformation - Apply a transformation to vectors of vertices
/// @param n - number of incoming vertices in the array
/// @param inV - incoming vertices array
/// @param outM - array of matrices after the applied transformation
/// @param transformation - the transformation to apply
///
void Pipeline::applyTransformation(int n, Vertex inV[], Matrix outM[], Matrix transformation) {
    for (int vertexIter = 0; vertexIter < n; vertexIter++) {
        float currPolyXVal = inV[vertexIter].x;
        float currPolyYVal = inV[vertexIter].y;
        float fv[] {
            currPolyXVal,
            currPolyYVal,
            1
        };
        Matrix currV(3, 1, fv);
        outM[vertexIter] = transformation * currV;
    }
}

///
/// clearTransform - Set the current transformation to the identity
///            matrix.
///
void Pipeline::clearTransform(void) {
    float identityMatrix[] {
        1, 0, 0,
        0, 1, 0,
        0, 0, 1
    };
    Matrix clearM(3, 3, identityMatrix);
    modelTransformation = clearM;
}

///
/// translate - Add a translation to the current transformation by
///             premultiplying the appropriate translation matrix to
///             the current transformation matrix.
///
/// @param tx - Amount of translation in x.
/// @param ty - Amount of translation in y.
///
void Pipeline::translate(float tx, float ty) {
    float translateMatrix[] {
        1, 0, tx,
        0, 1, ty,
        0, 0, 1
    };
    Matrix translateM(3, 3, translateMatrix);
    modelTransformation = translateM * modelTransformation;
}

///
/// rotate - Add a rotation to the current transformation by premultiplying
///          the appropriate rotation matrix to the current transformation
///          matrix.
///
/// @param degrees - Amount of rotation in degrees.
///
void Pipeline::rotate(float degrees) {
    float rad = degrees * float(M_PI) / 180;
    float rotateMatrix[] {
        cos(rad), -sin(rad), 0,
        sin(rad), cos(rad), 0,
        0, 0, 1
    };
    Matrix rotateM(3, 3, rotateMatrix);
    modelTransformation = rotateM * modelTransformation;
}

///
/// scale - Add a scale to the current transformation by premultiplying
///         the appropriate scaling matrix to the current transformation
///         matrix.
///
/// @param sx - Amount of scaling in x.
/// @param sy - Amount of scaling in y.
///
void Pipeline::scale(float sx, float sy) {
    float scale[] {
        sx, 0, 0,
        0, sy, 0,
        0, 0, 1
    };
    Matrix scaleM(3, 3, scale);
    modelTransformation = scaleM * modelTransformation;
}

///
/// setClipWindow - Define the clip window.
///
/// @param bottom - y coord of bottom edge of clip window (in world coords)
/// @param top - y coord of top edge of clip window (in world coords)
/// @param left - x coord of left edge of clip window (in world coords)
/// @param right - x coord of right edge of clip window (in world coords)
///
void Pipeline::setClipWindow(float bottom, float top, float left, float right) {
    float normalization[] {
        float(2 / (right - left)), 0, float(-2 * left / (right - left) - 1),
        0, float(2 / (top - bottom)), float(-2 * bottom / (top - bottom) - 1),
        0, 0, 1
    };
    Matrix normM(3, 3, normalization);
    normTransformation = normM;
}

///
/// setViewport - Define the viewport.
///
/// @param x - x coord of lower left of view window (in screen coords)
/// @param y - y coord of lower left of view window (in screen coords)
/// @param w - width of view window (in pixels)
/// @param h - width of view window (in pixels)
///
void Pipeline::setViewport(int x, int y, int w, int h) {
    float viewPort[] {
        float(w / 2), 0, float((2 * x + w) / 2),
        0, float(h / 2), float((2 * y + h) / 2),
        0, 0, 1
    };
    Matrix viewM(3, 3, viewPort);
    viewPortTransformation = viewM;
}

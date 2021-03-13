///
///  Pipeline.h
///
///  Created by Warren R. Carithers on 2016/10/19.
///  Based on a version created by Joe Geigel on 11/30/11.
///  Updates: 2019/02/25, 2019/10/01 by wrc.
///  Copyright 2019 Rochester Institute of Technology. All rights reserved.
///
///  Contributor:  Jimmy Dugan
///

#ifndef _PIPELINE_H_
#define _PIPELINE_H_

#include "Canvas.h"
#include "Types.h"
#include "cmatrix"

using namespace std;

// used for a Matrix
typedef techsoft::matrix<float> Matrix;

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

class Pipeline : public Canvas {
    
public:
    // Vector of all polygons
    // Each polygon's vertices are represented as a vector in the polyRepository vector
    vector<vector<Vertex>> polyRepository;
    // ID associated to each polygon in the polyRepository
    int polyID = 0;
    // variables to store current transformation
    Matrix modelTransformation;
    Matrix normTransformation;
    Matrix viewPortTransformation;
    
    ///
    /// Constructor
    ///
    /// @param w width of canvas
    /// @param h height of canvas
    ///
    Pipeline(int w, int h);

    ///
    /// addPoly - Add a polygon to the canvas.  This method does not draw
    ///           the polygon, but merely stores it for later drawing.
    ///           Drawing is initiated by the drawPoly() method.
    ///
    /// @param n - Number of vertices in polygon
    /// @param p - Array of Vertex entries defining the polygon to be added
    ///
    /// @return a unique integer identifier for the polygon
    ///
    int addPoly( int n, const Vertex p[] );

    ///
    /// drawPoly - Draw the polygon with the given id.  The polygon should
    ///            be drawn after applying the current transformation to
    ///            the vertices of the polygon.
    ///
    /// @param polyID - the ID of the polygon to be drawn.
    ///
    void drawPoly( int polyID );
    
    ///
    /// convertMatrixToVertexArray - convert the matrices to an array of vertices
    /// @param n - number of incoming vertices in the matrix array
    /// @param inM - incoming array of matrices
    /// @param outV - outgoing vertices array
    ///
    void convertMatrixToVertexArray(int n, Matrix inM[], Vertex outV[]);
    
    ///
    /// applyTransformation - Apply a transformation to vectors of vertices
    /// @param n - number of incoming vertices in the array
    /// @param inV - incoming vertices array
    /// @param outM - array of matrices after the applied transformation
    /// @param transformation - the transformation to apply
    ///
    void applyTransformation(int n, Vertex inV[], Matrix outM[], Matrix transformation);

    ///
    ///
    /// clearTransform - Set the current transformation to the identity
    ///            matrix.
    ///
    ///
    void clearTransform( void );

    ///
    /// translate - Add a translation to the current transformation by
    ///             premultiplying the appropriate translation matrix to
    ///             the current transformation matrix.
    ///
    /// @param tx - Amount of translation in x.
    /// @param ty - Amount of translation in y.
    ///
    ///
    void translate( float tx, float ty );

    ///
    /// rotate - Add a rotation to the current transformation by premultiplying
    ///          the appropriate rotation matrix to the current transformation
    ///          matrix.
    ///
    /// @param degrees - Amount of rotation in degrees.
    ///
    void rotate( float degrees );

    ///
    /// scale - Add a scale to the current transformation by premultiplying
    ///         the appropriate scaling matrix to the current transformation
    ///         matrix.
    ///
    /// @param sx - Amount of scaling in x.
    /// @param sy - Amount of scaling in y.
    ///
    void scale( float sx, float sy );

    ///
    // setClipWindow - Define the clip window.
    ///
    /// @param bottom - y coord of bottom edge of clip window (in world coords)
    /// @param top - y coord of top edge of clip window (in world coords)
    /// @param left - x coord of left edge of clip window (in world coords)
    /// @param right - x coord of right edge of clip window (in world coords)
    ///
    void setClipWindow( float bottom, float top, float left, float right );

    ///
    /// setViewport - Define the viewport.
    ///
    /// @param x - x coord of lower left of view window (in screen coords)
    /// @param y - y coord of lower left of view window (in screen coords)
    /// @param w - width of view window (in world coords)
    /// @param h - height of view window (in world coords)
    ///
    void setViewport( int x, int y, int w, int h );

};

#endif

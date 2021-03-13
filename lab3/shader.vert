//
// Alternate vertex shader for the transformation assignment
//
// Created by Warren R. Carithers 2016/04/22.
//
// Contributor:  Jimmy Dugan
//

#version 120

//specifies the type of projection
uniform mat4 projection;

//camera location, lookat point, up vector
uniform vec3 eye;
uniform vec3 lookat;
uniform vec3 up;

uniform vec3 translateVec;
uniform vec3 scaleVec; 
uniform vec3 rotateVec;

attribute vec4 vPosition;

///
/// This function takes in the translate vector and creates the matrix to apply to the final view
///
/// @param translateVec - vector used for translate transformation
/// @return translateTransformation - the translation transformation matrix
///
mat4 translate(vec3 translateVec){
	mat4 translateTransformation = mat4( 1, 0, 0, 0,
									0, 1, 0, 0,
						  			0, 0, 1, 0,
						  			translateVec.x, translateVec.y, translateVec.z, 1);
	return translateTransformation;
}

///
/// This function takes in the rotate vector and creates the matrix to apply to the final view
///
/// @param rotateVec - vector used for rotate transformation
/// @return rotateTransfomation - the rotation transformation matrix
///
mat4 rotate(vec3 rotateVec){
	vec3 rotateRad = radians(rotateVec);
	mat4 rotateTransformationX = mat4(1, 0, 0, 0,
								0, cos(rotateRad).x, sin(rotateRad).x, 0,
								0, - sin(rotateRad).x, cos(rotateRad).x, 0,
								0, 0, 0, 1);

    mat4 rotateTransformationY = mat4(cos(rotateRad).y, 0, - sin(rotateRad).y, 0,
								0, 1, 0, 0,
								sin(rotateRad).y, 0, cos(rotateRad).y, 0,
								0, 0, 0, 1);

    mat4 rotateTransformationZ = mat4(cos(rotateRad).z, sin(rotateRad).z, 0, 0,
								- sin(rotateRad).z, cos(rotateRad).z, 0, 0,
								0, 0, 1, 0,
								0, 0, 0, 1);
    mat4 rotateTransfomation = rotateTransformationX * rotateTransformationY * rotateTransformationZ;
    return rotateTransfomation;
}

///
/// This function takes in the scale vector and creates the matrix to apply to the final view
///
/// @param scaleVec - vector used for scale transformation
/// @return scaleTransformation - the scale transformation matrix
///
mat4 scale(vec3 scaleVec){
	mat4 scaleTransformation = mat4(scaleVec.x, 0, 0, 0,
							0, scaleVec.y, 0, 0,
							0, 0, scaleVec.z, 0,
							0, 0, 0, 1);
	return scaleTransformation;

}

///
/// This function takes in camera location information and creates the matrix to apply to the final view
///
/// @param eye - camera location vector
/// @param lookat - camera lookat point vector
/// @param up - camera up vector
/// @return cameraTransformation - the camera transformation matrix
///
mat4 camera(vec3 eye, vec3 lookat, vec3 up){
	vec3 n = normalize(eye - lookat);
    vec3 u = normalize(cross(normalize(up), n));
    vec3 v = normalize(cross(n, u));
    mat4 cameraTransformation = mat4(u.x, v.x, n.x, 0,
							u.y, v.y, n.y, 0,
							u.z, v.z, n.z, 0,
							- dot(u, eye), - dot(v, eye), - dot(n, eye), 1);
    return cameraTransformation;
}

///
/// This function calls the functions to compute the transformation matrices and computes gl_Position
///
void main()
{
	mat4 cameraTransformation = camera(eye, lookat, up);
	mat4 translateTransformation = translate(translateVec);
	mat4 rotateTransfomation = rotate(rotateVec);
	mat4 scaleTransformation = scale(scaleVec);
    gl_Position = projection * cameraTransformation * translateTransformation * rotateTransfomation * scaleTransformation * vPosition;
}

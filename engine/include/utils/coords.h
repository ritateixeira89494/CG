#ifndef __COORDS_H__
#define __COORDS_H__

#include <tuple>

using namespace std;

/**
 * @brief Converts a radian angle into degrees
 * 
 * @param angle Angle in radian
 * @return float Angle in degrees
 */
float radian2degree(float angle);

/**
 * @brief Converts spherical coordinates into cartesian coordinates
 * 
 * @param radius Radius
 * @param alpha Horizontal angle
 * @param beta Vertical angle
 * @return tuple<float, float, float> (x,y,z) coordinates in cartesian
 */
tuple<float, float, float> spherical2cartesian(float radius, float alpha, float beta); 

/**
 * @brief Converts cartesian coordinates into spherical coordinates
 * 
 * @param x x coordinate
 * @param y y coordinate
 * @param z z coordinate
 * @return tuple<float, float, float> (radius, alpha, beta) coordinates in spherical
 */
tuple<float, float, float> cartesian2spherical(float x, float y, float z);

#endif // __COORDS_H__
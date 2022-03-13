#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__

#include <GL/gl.h>
#include <GL/glut.h>

#include <tuple>

using namespace std;

namespace triangle {
    class Triangle {
    private:
        /// Point 1 of the triangle
        tuple<GLfloat, GLfloat, GLfloat> p1;
        /// Point 2 of the triangle
        tuple<GLfloat, GLfloat, GLfloat> p2;
        /// Point 3 of the triangle
        tuple<GLfloat, GLfloat, GLfloat> p3;
    public:
        /**
         * @brief Create a new triangle with the 3 points passed as arguments
         * 
         * @param p1 Point 1 of the triangle
         * @param p2 Point 2 of the triangle
         * @param p3 Point 3 of the triangle
         */
        Triangle(
            tuple<GLfloat, GLfloat, GLfloat> p1,
            tuple<GLfloat, GLfloat, GLfloat> p2,
            tuple<GLfloat, GLfloat, GLfloat> p3
        );

        /**
         * @brief Create a new triangle with the 3 points passed as arguments
         * 
         * @param x1 x coordinate of point 1
         * @param y1 y coordinate of point 1
         * @param z1 z coordinate of point 1
         * @param x2 x coordinate of point 2
         * @param y2 y coordinate of point 2
         * @param z2 z coordinate of point 2
         * @param x3 x coordinate of point 3
         * @param y3 y coordinate of point 3
         * @param z3 z coordinate of point 3
         */
        Triangle(
                GLfloat x1, GLfloat y1, GLfloat z1,
                GLfloat x2, GLfloat y2, GLfloat z2,
                GLfloat x3, GLfloat y3, GLfloat z3
        );

        /**
         * @brief Get the coordinates of point 1
         * 
         * @return tuple<GLfloat, GLfloat, GLfloat> (x,y,z) coordinates of point 1
         */
        tuple<GLfloat, GLfloat, GLfloat> get_p1();

        /**
         * @brief Get the coordinates of point 
         * 
         * @return tuple<GLfloat, GLfloat, GLfloat> (x,y,z) coordinates of point 2
         */
        tuple<GLfloat, GLfloat, GLfloat> get_p2();

        /**
         * @brief Get the coordinates of point 3
         * 
         * @return tuple<GLfloat, GLfloat, GLfloat> (x,y,z) coordinates of point 3
         */
        tuple<GLfloat, GLfloat, GLfloat> get_p3();
    };
}

#endif // __TRIANGLE_H__

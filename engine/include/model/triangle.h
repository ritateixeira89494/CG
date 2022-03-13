#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__

#include <tuple>

using namespace std;

namespace triangle {
    class Triangle {
    private:
        /// Point 1 of the triangle
        tuple<float, float, float> p1;
        /// Point 2 of the triangle
        tuple<float, float, float> p2;
        /// Point 3 of the triangle
        tuple<float, float, float> p3;
    public:
        /**
         * @brief Create a new triangle with the 3 points passed as arguments
         * 
         * @param p1 Point 1 of the triangle
         * @param p2 Point 2 of the triangle
         * @param p3 Point 3 of the triangle
         */
        Triangle(
            tuple<float, float, float> p1,
            tuple<float, float, float> p2,
            tuple<float, float, float> p3
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
                float x1, float y1, float z1,
                float x2, float y2, float z2,
                float x3, float y3, float z3
        );

        /**
         * @brief Get the coordinates of point 1
         * 
         * @return tuple<float, float, float> (x,y,z) coordinates of point 1
         */
        tuple<float, float, float> get_p1();

        /**
         * @brief Get the coordinates of point 
         * 
         * @return tuple<float, float, float> (x,y,z) coordinates of point 2
         */
        tuple<float, float, float> get_p2();

        /**
         * @brief Get the coordinates of point 3
         * 
         * @return tuple<float, float, float> (x,y,z) coordinates of point 3
         */
        tuple<float, float, float> get_p3();
    };
}

#endif // __TRIANGLE_H__

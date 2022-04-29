#ifndef CG2022_TRANSLATE_H
#define CG2022_TRANSLATE_H

#include "model/transforms/Transform.h"

#include <chrono>
#include <vector>

using namespace std;
using namespace std::chrono;

class Translate : public Transform {
    private:
// Variables //////////////////////////////////////////////////////////////////////////////////////
        /// Specifies if this translation is dynamic or static
        bool dynamic;
        /// Full time length of the translation
        milliseconds full_time;
        /**
         * @brief Time elapsed since the application started
         * @note This value is gotten from @b glutGet(GL_ELAPSED_TIME)
         */
        int start;
        /// Last Y used to calculate the direction of the object
        float last_y[3] = { 0, 1, 0 };
        /// Model alignment with the curve
        bool align;
        /// Control points used to calculate the curve
        vector<tuple<float,float,float>> ctrl_points;
        /// Specifies whether to draw or not the Catmull-Rom curve
        bool draw;
        /// Number of segments to divide the curve when drawing it
        /// @note This does @b not affect translation itself
        int curve_segments;

// Methods ////////////////////////////////////////////////////////////////////////////////////////
        /**
         * @brief Returns the position and derivative at any given time along the Catmull-Rom curve
         * 
         * @param t Time
         * @param p0 First control point
         * @param p1 Second control point
         * @param p2 Third control point
         * @param p3 Fourth controlo point
         * @param pos Position array in which the position will be returned
         * @param deriv Derivative of the curve at the specified point in time
         */
        void get_catmull_rom_point(float time, tuple<float,float,float> p0, tuple<float,float,float> p1, tuple<float,float,float> p2, tuple<float,float,float> p3, float *pos, float *deriv);
        /**
         * @brief Returns the position and derivative at the given time.
         * 
         * @param gt Time
         * @param pos Position array in which to store the position
         * @param deriv Derivative array in which to store the derivative of the position
         */
        void get_global_catmull_rom_point(float gt, float *pos, float *deriv);

    public:
// Constructors ///////////////////////////////////////////////////////////////////////////////////
        /**
         * @brief Construct a static translation
         * 
         * @param x x coordinate
         * @param y y coordinate
         * @param z z coordinate
         */
        Translate(float x, float y, float z);

        /**
         * @brief Construct a dynamic translation with all the control points already set
         * 
         * @param full_time animation length
         * @param ctrl_points vector with all control points
         */
        Translate(int full_time, bool align, bool draw, int curve_segments, vector<tuple<float,float,float>> ctrl_points);

        /**
         * @brief Construct a dynamic animation with no control points
         * 
         * @param full_time animation length
         */
        Translate(int full_time, bool align, bool draw, int curve_segments);

// Methods ////////////////////////////////////////////////////////////////////////////////////////

        /**
         * @brief Draw the Catmull-Rom curve
         * 
         * @param detail Number of segments in which to divide the curve
         */
        void draw_curve();

        /**
         * @brief Update and apply the transformation
         * 
         * @note If the translation is dynamic, then the current time is increased
         */
        void apply() override;


// Getters/Setters ////////////////////////////////////////////////////////////////////////////////

        /**
         * @brief Enables/Disables the translation dynamism
         * 
         * @param dynamic Value to set the dynamism
         */
        void set_dynamic(bool dynamic);
        /**
         * @brief Get the translation dynamism
         * 
         * @return true translation is dynamic
         * @return false translation is static
         */
        bool get_dynamic();

        /**
         * @brief Set the animation length in milliseconds
         * 
         * @param time New animation length in milliseconds
         */
        void set_full_time(int time);
        /**
         * @brief Get the animation length
         * 
         * @return float Full animation length
         */
        int get_full_time();

        /**
         * @brief Set the start of the animation
         * 
         * @param start New animation start
         */
        void set_start(int start);
        /**
         * @brief Get the time elapsed since the start of the application 
         * 
         * @return Time elapsed since the application started
         */
        int get_start();

        /**
         * @brief Set the model align
         * 
         * @param align Value to set to align
         */
        void set_align(bool align);
        /**
         * @brief Get the model alignment
         * 
         * @return true Model is aligned with the curve
         * @return false Model is not aligned with the curve
         */
        bool get_align();

        /**
         * @brief Set the control points
         * 
         * @param points control points to set
         */
        void set_ctrl_points(vector<tuple<float,float,float>> points);
        /**
         * @brief Get the ctrl_points vector
         * 
         * @return vector<tuple<float,float,float>> vector with all control points of this translation
         */
        vector<tuple<float,float,float>> get_ctrl_points();

        /**
         * @brief Set the draw flag
         */
        void set_draw(bool draw);
        /**
         * @brief Get the draw flag
         * 
         * @return true The Catmull-Rom curve is to be drawn
         * @return false The Catmull-Rom curve should not be drawn
         */
        bool get_draw();
};


#endif //CG2022_TRANSLATE_H

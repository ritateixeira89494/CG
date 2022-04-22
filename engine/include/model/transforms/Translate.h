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
        seconds full_time;
        /// Current time length of the translation
        milliseconds curr_time;
        /// Last clock cycle. Used to calculate time passed since last iteration. (Or for tweening)
        /// @note setting this clock to std::chrono::system_clock::time_point::min(), tells the object the animation is at the beginning.
        system_clock::time_point start_clock;
        /// Last Y used to calculate the direction of the object
        float last_y[3] = { 0, 1, 0 };
        /// Model alignment with the curve
        bool align;
        /// Control points used to calculate the curve
        vector<float *> ctrl_points;

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
        void get_catmull_rom_point(float time, float *p0, float *p1, float *p2, float *p3, float *pos, float *deriv);
        /**
         * @brief Returns the position and derivative at the current time.
         * @note This function uses the system clock to get the current time 
         * 
         * @param pos Position array in which to store the position
         * @param deriv Derivative array in which to store the derivative of the position
         */
        void get_global_catmull_rom_point(float *pos, float *deriv);

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
        Translate(int full_time, bool align, vector<float *> ctrl_points);

        /**
         * @brief Construct a dynamic animation with no control points
         * 
         * @param full_time animation length
         */
        Translate(int full_time, bool align);

// Methods ////////////////////////////////////////////////////////////////////////////////////////

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
         * @brief Set the full_time value
         * 
         * @param time new full_time
         */
        void set_full_time(float time);
        /**
         * @brief Get the full_time value
         * 
         * @return float Full animation length
         */
        float get_full_time();

        /**
         * @brief Set the curr_time value
         * 
         * @param time new curr_time @note Must be less than full_time
         */
        void set_curr_time(milliseconds time);
        /**
         * @brief Get the curr_time value
         * 
         * @return float curr_time value
         */
        milliseconds get_curr_time();

        /**
         * @brief Set the start clock cycle
         * 
         * @param start_clock clock cycle to set 
         */
        void set_start_clock(system_clock::time_point start_clock);
        /**
         * @brief Get the start clock cycle
         * 
         * @return time_point start clock cycle
         */
        system_clock::time_point get_start_clock();

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
        vector<float *> get_ctrl_points();
};


#endif //CG2022_TRANSLATE_H

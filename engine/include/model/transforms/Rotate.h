#ifndef CG2022_ROTATE_H
#define CG2022_ROTATE_H

#include "model/transforms/Transform.h"

class Rotate : public Transform {
    private:
        /**
         * @brief Specifies if the rotation is dynamic or not 
         */
        bool dynamic;

        /**
         * The angle of the rotate.
         */
        float angle;

        /**
         * @brief Full time of rotation
         * 
         */
        int full_time;

        /**
         * @brief Elapsed time at the start of the animation.
         * @note This is gotten from @b glutGet(GL_ELAPSED_TIME)
         */
        int start;

    public:
// Constructors ///////////////////////////////////////////////////////////////////////////////////
        /**
         * @brief Construct a new static rotation
         * 
         * @param angle Angle of rotation
         * @param x X coordinate
         * @param y Y coordinate
         * @param z Z coordinate
         */
        Rotate(float angle, float x, float y, float z);
        /**
         * @brief Construct a new dynamic rotation
         * 
         * @param t Full length of rotation in seconds
         * @param x X coordinate
         * @param y Y coordinate
         * @param z Z coordinate
         */
        Rotate(int t, float x, float y, float z);

// Methods ////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Applies the rotation, according to it's dynamism
        void apply() override;

// Getters/Setters ////////////////////////////////////////////////////////////////////////////////
        /// @brief Sets the dynamic variable
        void set_dynamic(bool dynamic);
        /// @brief Gets the dynamic variable
        bool get_dynamic();

        /// @brief Sets the angle of rotation
        void set_angle(float angle);
        /// @brief Gets the angle of rotation
        float get_angle();

        /// @brief Sets the full animation length
        void set_full_time(int full_time);
        /// @brief Gets the full animation length
        int get_full_time();

        /// @brief Sets the animation start
        void set_start(int start);
        /// @brief Gets the animation start
        int get_start();
};


#endif //CG2022_ROTATE_H

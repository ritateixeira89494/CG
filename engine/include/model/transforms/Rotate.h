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
         * @note This is gotten from glutGet(GL_ELAPSED_TIME)
         */
        int start;

    public:
// Constructors ///////////////////////////////////////////////////////////////////////////////////
        Rotate(float angle, float x, float y, float z);
        Rotate(int t, float x, float y, float z);

// Methods ////////////////////////////////////////////////////////////////////////////////////////
        void apply() override;

// Getters/Setters ////////////////////////////////////////////////////////////////////////////////
        void set_dynamic(bool dynamic);
        bool get_dynamic();

        void set_angle(float angle);
        float get_angle();

        void set_full_time(int full_time);
        int get_full_time();

        void set_start(int start);
        int get_start();
};


#endif //CG2022_ROTATE_H

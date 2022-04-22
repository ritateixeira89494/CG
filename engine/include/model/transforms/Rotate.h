#ifndef CG2022_ROTATE_H
#define CG2022_ROTATE_H

#include "model/transforms/Transform.h"

class Rotate : public Transform {
    public:
        Rotate(float angle, float x, float y, float z);
        Rotate(int t, float x, float y, float z);

        void apply() override;

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
};


#endif //CG2022_ROTATE_H

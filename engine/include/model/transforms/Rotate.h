#ifndef CG2022_ROTATE_H
#define CG2022_ROTATE_H

#include "model/transforms/Transform.h"

class Rotate : Transform {
    public:
        Rotate(float angle, float x, float y, float z);

        void apply() override;

    private:
        float angle;
};


#endif //CG2022_ROTATE_H

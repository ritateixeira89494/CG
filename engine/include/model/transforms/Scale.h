#ifndef CG2022_SCALE_H
#define CG2022_SCALE_H

#include "Transform.h"

class Scale : Transform {
    public:
        Scale(float x, float y, float z);

        void apply() override;
};


#endif //CG2022_SCALE_H

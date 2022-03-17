#ifndef CG2022_TRANSLATE_H
#define CG2022_TRANSLATE_H

#include "model/transforms/Transform.h"

class Translate : public Transform {
    public:
        Translate(float x, float y, float z);

        void apply() override;
};


#endif //CG2022_TRANSLATE_H

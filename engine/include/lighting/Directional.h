#ifndef __DIRECTIONAL_H__
#define __DIRECTIONAL_H__

#include "lighting/Light.h"

namespace lighting {
    class Directional : Light {
        private:
            /// X component of the lighting vector
            float dirX;
            /// Y component of the lighting vector
            float dirY;
            /// Z component of the lighting vector
            float dirZ;
        public:
            Directional(
                float diffuse[4], float ambient[4], float specular[4],
                float dirX, float dirY, float dirZ    
            );

            Directional(float dirX, float dirY, float dirZ);

            void place() override;
    };
}

#endif // __DIRECTIONAL_H__

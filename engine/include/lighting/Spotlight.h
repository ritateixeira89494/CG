#ifndef __SPOTLIGHT_H__
#define __SPOTLIGHT_H__

#include "lighting/Light.h"

namespace lighting {
    class Spotlight : Light {
        private:
            /// X coordinate of the light's position
            float posX = 0;
            /// Y coordinate of the light's position
            float posY = 0;
            /// Z coordinate of the light's position
            float posZ = 0;

            /// X coordinate of the light's direction
            float dirX = 0;
            /// X coordinate of the light's direction
            float dirY = 1;
            /// X coordinate of the light's direction
            float dirZ = 0;

            /// Light's maximum spread
            float cutoff = 180;

        public:
            /**
             * @brief Creates a white spotlight positioned at the origin and
             * directed at (0,1,0) with a cutoff of 180
             */
            Spotlight() = default;

            /**
             * @brief Creates a white spotlight positioned, directed and
             * with the cutoff specified
             */
            Spotlight(
                    float posX, float posY, float posZ,
                    float dirX, float dirY, float dirZ,
                    float cutoff
            );

            /**
             * @brief Creates a spotlight with the specified colors and positioned,
             * directed and with the specified cutoff
             */
            Spotlight(
                    float *diffuse, float *ambient, float *specular,
                    float posX, float posY, float posZ,
                    float dirX, float dirY, float dirZ,
                    float cutoff
            );

            void place() override;
    };
}

#endif // __SPOTLIGHT_H__

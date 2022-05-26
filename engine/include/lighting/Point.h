#ifndef __POINT_H__
#define __POINT_H__

#include "lighting/Light.h"

namespace lighting {
    class Point : Light {
        private:
            /// X coordinate of the light
            float posX;
            /// Y coordinate of the light
            float posY;
            /// Z coordinate of the light
            float posZ;
        public:
            /**
             * @brief Creates a white light positioned at the origin
             */
            Point();
            /**
             * @brief Creates a white light positioned at the specified coordinates
             */
            Point(float posX, float posY, float posZ);
            /**
             * @brief Creates a light with the specified colors and position
             */
            Point(
                    float *diffuse, float *ambient, float *specular,
                    float posX, float posY, float posZ
            );

            /// Places the light into the scene
            void place() override;
    };
}

#endif // __POINT_H__

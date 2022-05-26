#ifndef __LIGHT_H__
#define __LIGHT_H__

namespace lighting {
    class Light {
        protected:
            /// Number of lights currently active
            static int n_lights;
            /// Light number for GL_LIGHTX 
            int id;
            /// Diffuse lighting
            float diffuse[4] = { 1, 1, 1, 1 };
            /// Ambient lighting
            float ambient[4] = { 0.1, 0.1, 0.1, 1};
            /// Specular lighting
            float specular[4] = { 1, 1, 1, 1 };
        public: 
            /**
             * @brief Creates a white light with the folowing settings:
             *      diffuse = { 1, 1, 1, 1 }
             *      ambient = { 0.1, 0.1, 0.1, 1 }
             *      specular = { 1, 1, 1, 1 }
             */ 
            Light();
            /**
             * @brief Creates a light with the specified settings
             *
             * @param diffuse Diffuse lighting
             * @param ambient Ambient lighting
             * @param specular Specular lighting
             */ 
            Light(float diffuse[4], float ambient[4], float specular[4]);

            // Places the light into the scene
            virtual void place() = 0;
    };
}

#endif // __LIGHT_H__

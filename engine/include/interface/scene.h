#ifndef __SCENE_H__
#define __SCENE_H__

#include <vector>
#include "interface/perspective.h"
#include "../model/model.h"
#include "utils/Group.h"

using namespace model;

namespace interface {
    class Scene {
            /**
             * @brief Camera center
             *
             * These are the coordinates to which the camera is looking at
             */
            tuple<float, float, float> camera_center;
            /**
             * @brief Up vector
             *
             * This vector specifies which direction is up
             */
            tuple<float, float, float> up;
            /// Camera field of view
            float fov = 60;
            /// Distance to the near plane. Objects closer than this plane will get discarded
            float near = 1;
            /// Distance to the far plane. Objects farther than this plane will get discarded
            float far = 1000;
            /// Camera horizontal rotation
            float alpha = 0;
            /// Camera vertical rotation
            float beta = 0;
            /// Camera radius to the @link camera_center @endlink
            float radius = 1;
            /// List of models loaded into the scene
            vector<Group *> groups;
            /// Translation vector applied to all models
            tuple<float, float, float> position;
            /// Horizontal rotation applied to all models
            float m_rotation_alpha = 0;
            /// Vertical rotation applied to all models
            float m_rotation_beta = 0;
            /// Model scale;
            float scale = 1;

        public:
            /**
                @brief Creates an empty scene with the default settings
            */
            Scene();

            /**
                @brief Reads an xml file and loads all its settings and models

                @param path Path to the xml file
            */
            explicit Scene(const char *path);

            /**
             * @brief Returns a perspective object
             * @return Perspective object calculated from spherical coordinates
             */
            Perspective get_perspective();

            /**
                @brief Renders all models of the scene

                @param cam_mode bool telling if camera mode is active or not
            */
            void render_models(bool cam_mode);

            /**
                @brief Applies to all models, the vector passed as the argument

                @param angle Angle to move the object in relation to the camera
            */
            void move_models(float angle);

            /**
             * @brief Rotate all models by the specified angles
             *
             * @param angle_alpha Horizontal rotation to apply
             * @param angle_beta Vertical rotation to apply
             */
            void rotate_models(float angle_alpha, float angle_beta);

            /**
             * @brief Moves the camera in the vector direction
             *
             * @param angle Angle to move the camera in relation to its focused point
             * @return The updated perspective
             */
            Perspective move_camera(float angle);

            /**
             * @brief Rotates the models in the specified angle
             *
             * @param angle Angle in which to rotate the models
             * @return The updated perspective
            */
            Perspective rotate_camera(float angle_alpha, float angle_beta);

            /**
             * @brief Changes the model scale
             *
             * @param val Value to add to the scale
             */
            void change_scale(float val);

            /**
             * @brief Changes the camera zoom. In other words it adds the zoom value to the camera radius
             *
             * @param zoom Zoom amount
             * @return The updated perspective
             */
            Perspective zoom(float zoom);

            /**
             * @brief Get the translation vector applied to all the models
             *
             * @return tuple<float, float, float> translation vector applied to all models
             */
            tuple<float, float, float> get_position();

            /**
             * @brief Set the translation vector to apply to all arguments
             *
             * @note This is not like @link move_models @endlink where it adds this vector to
             *       all other translations previously made. This will instead @b overwrite all previous
             *       translations.
             *
             * @param x x coordinate of the vector
             * @param y y coordinate of the vector
             * @param z z coordinate of the vector
             */
            void set_position(float x, float y, float z);

            /**
             * @brief Get the model rotation
             *
             * @return float Model rotation angle
             */
            float get_rotation();

            /**
             * @brief Set the rotation angle to apply to the models
             *
             * @note This is not like @link rotate_models @endlink where it adds the rotation angle to
             *       all previous rotations. This will instead @b overwrite all previous rotations
             *
             * @param angle Rotation angle to set the models at
             */
            void set_rotation(float angle);

            /**
             * @brief Get the camera position
             *
             * @note This returns the coordinates in cartesian
             *
             * @return tuple<float, float, float> (x,y,z) coordinates of the camera
             */
            tuple<float, float, float> get_camera_pos();

            /**
             * @brief Set the camera position coordinates
             *
             * @note The coordinates of the arguments are in cartesian
             *
             * @param x x coordinate of the camera
             * @param y y coordinate of the camera
             * @param z z coordinate of the camera
             */
            void set_camera_pos(float x, float y, float z);

            /**
             * @brief Get the @link camera_center @endlink
             *
             * @return tuple<float, float, float> (x,y,z) coordinates of the camera center
             */
            tuple<float, float, float> get_camera_center();

            /**
             * @brief Set the @link camera_center @endlink
             *
             * @param x coordinate of the camera center
             * @param y coordinate of the camera center
             * @param z coordinate of the camera center
             */
            void set_camera_center(float x, float y, float z);

            /**
             * @brief Get the @link up @endlink vector
             *
             * @return tuple<float, float, float> up vector
             */
            tuple<float, float, float> get_up();

            /**
             * @brief Set the @link up @endlink vector
             *
             * @param x coordinate of the vector
             * @param y coordinate of the vector
             * @param z coordinate of the vector
             */
            void set_up(float x, float y, float z);

            /**
             * @brief Get the camera @link fov @endlink
             *
             * @return float field of view
             */
            float get_fov();

            /**
             * @brief Set the camera @link fov @endlink
             *
             * @param fov2 field of view to set to the camera
             */
            void set_fov(float fov2);

            /**
             * @brief Get the @link near @endlink value
             *
             * @return float Camera near value
             */
            float get_near();

            /**
             * @brief Set the near value
             *
             * @param near2 Near value to set to the camera
             */
            void set_near(float near2);

            /**
             * @brief Get the far value
             *
             * @return float Camera far value
             */
            float get_far();

            /**
             * @brief Set the far value
             *
             * @param far2 Far value to set to the camera
             */
            void set_far(float far2);

            /**
             * @brief Get the model horizontal rotation
             *
             * @return float Horizontal rotation applied to all models
             */
            float get_model_rotation_alpha();

            /**
             * @brief Get the model rotation vertical rotation
             *
             * @return float Vertical rotation applied to all models
             */
            float get_model_rotation_beta();

            /**
             * @brief Get the model scale
             *
             * @return float Model scale
             */
            float get_scale();

            /**
             * @brief Get the camera zoom
             * 
             * @return float camera zoom
             */
            float get_radius();

            /**
             * @brief Set the camera zoom
             * 
             * @param float camera zoom
             */
            void set_radius(float radius);
    };
} // namespace interface

#endif // __SCENE_H__
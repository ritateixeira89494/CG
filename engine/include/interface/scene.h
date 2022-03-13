#ifndef __SCENE_H__
#define __SCENE_H__

#include <vector>
#include "../model/model.h"

using namespace model;

namespace interface {
    class Scene {
        /**
         * @brief Camera center
         * 
         * These are the coordinates to which the camera is looking at
         */
        tuple<GLfloat, GLfloat, GLfloat> camera_center;
        /**
         * @brief Up vector
         * 
         * This vector specifies which direction is up
         */
        tuple<GLfloat, GLfloat, GLfloat> up;
        /// Camera field of view
        GLfloat fov;
        /// Distance to the near plane. Objects closer than this plane will get discarded
        GLfloat near;
        /// Distance to the far plane. Objects farther than this plane whill get discarded
        GLfloat far;
        /// Camera horizontal rotation
        GLfloat alpha;
        // Camera vertical rotation
        GLfloat beta;
        /// Camera radius to the @link camera_center @endlink 
        GLfloat radius;
        /// List of models loaded into the scene
        vector<Model *> models;
        /// Translation vector applied to all models
        tuple<GLfloat, GLfloat, GLfloat> position;
        /// Horizontal rotation applied to all models
        GLfloat m_rotation_alpha;
        /// Vertical rotation applied to all models
        GLfloat m_rotation_beta;

    public:
        /**
            @brief Creates an empty scene with the default settings
        */
        Scene();

        /**
            @brief Reads an xml file and loads all its settings and models

            @param path Path to the xml file
        */
        explicit Scene(char *path);

        /**
            @brief Creates a new scene with the list of passed as models

            @param models List of models to add to the scene
        */
        explicit Scene(vector<Model *> models);

        /**
            @brief Renders all models of the scene
        */
        void render_models();

        /**
            @brief Applies to all models, the vector passed as the argument

            @param x x coordinate of the vector 
            @param y y coordinate of the vector 
            @param z z coordinate of the vector 
        */
        void move_models(GLfloat x, GLfloat y, GLfloat z);

        /**
         * @brief Rotate all models by the specified angles 
         * 
         * @param angle_alpha Horizontal rotation to apply
         * @param angle_beta Vertical rotation to apply
         */
        void rotate_models(GLfloat angle_alpha, GLfloat angle_beta);

        /**
            @brief Rotates the models in the specified angle

            @param angle Angle in which to rotate the models
        */
        void rotate_camera(GLfloat angle_alpha, GLfloat angle_beta);

        /**
         * @brief Changes the camera zoom. In other words it adds the zoom value to the camera radius 
         * 
         * @param zoom Zoom amount
         */
        void zoom(GLfloat zoom);

        /**
         * @brief Get the translation vector applied to all the models
         * 
         * @return tuple<GLfloat, GLfloat, GLfloat> translation vector applied to all models
         */
        tuple<GLfloat, GLfloat, GLfloat> get_position();

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
        void set_position(GLfloat x, GLfloat y, GLfloat z);

        /**
         * @brief Get the model rotation
         * 
         * @return GLfloat Model rotation angle
         */
        GLfloat get_rotation();

        /**
         * @brief Set the rotation angle to apply to the models
         * 
         * @note This is not like @link rotate_models @endlink where it adds the rotation angle to
         *       all previous rotations. This will instead @b overwrite all previous rotations
         * 
         * @param angle Rotation angle to set the models at
         */
        void set_rotation(GLfloat angle);

        /**
         * @brief Get the camera position
         * 
         * @note This returns the coordinates in cartesian
         * 
         * @return tuple<GLfloat, GLfloat, GLfloat> (x,y,z) coordinates of the camera
         */
        tuple<GLfloat, GLfloat, GLfloat> get_camera_pos();

        /**
         * @brief Set the camera position coordinates
         * 
         * @note The coordinates of the arguments are in cartesian
         * 
         * @param x x coordinate of the camera
         * @param y y coordinate of the camera
         * @param z z coordinate of the camera
         */
        void set_camera_pos(GLfloat x, GLfloat y, GLfloat z);

        /**
         * @brief Get the @link camera_center @endlink
         * 
         * @return tuple<GLfloat, GLfloat, GLfloat> (x,y,z) coordinates of the camera center
         */
        tuple<GLfloat, GLfloat, GLfloat> get_camera_center();

        /**
         * @brief Set the @link camera_center @endlink
         * 
         * @param x coordinate of the camera center
         * @param y coordinate of the camera center
         * @param z coordinate of the camera center
         */
        void set_camera_center(GLfloat x, GLfloat y, GLfloat z);

        /**
         * @brief Get the @link up @endlink vector
         * 
         * @return tuple<GLfloat, GLfloat, GLfloat> up vector
         */
        tuple<GLfloat, GLfloat, GLfloat> get_up();

        /**
         * @brief Set the @link up @endlink vector
         * 
         * @param x coordinate of the vector
         * @param y coordinate of the vector
         * @param z coordinate of the vector
         */
        void set_up(GLfloat x, GLfloat y, GLfloat z);

        /**
         * @brief Get the camera @link fov @endlink 
         * 
         * @return GLfloat field of view
         */
        GLfloat get_fov();

        /**
         * @brief Set the camera @link fov @endlink 
         * 
         * @param fov2 field of view to set to the camera
         */
        void set_fov(GLfloat fov2);

        /**
         * @brief Get the @link near @endlink value
         * 
         * @return GLfloat Camera near value
         */
        GLfloat get_near();

        /**
         * @brief Set the near value
         * 
         * @param near2 Near value to set to the camera
         */
        void set_near(GLfloat near2);

        /**
         * @brief Get the far value
         * 
         * @return GLfloat Camera far value
         */
        GLfloat get_far();

        /**
         * @brief Set the far value
         * 
         * @param far2 Far value to set to the camera
         */
        void set_far(GLfloat far2);

        /**
         * @brief Get the model horizontal rotation
         * 
         * @return GLfloat Horizontal rotation applied to all models
         */
        GLfloat get_model_rotation_alpha();

        /**
         * @brief Get the model rotation vertical rotation
         * 
         * @return GLfloat Vertical rotation applied to all models
         */
        GLfloat get_model_rotation_beta();
    };
} // namespace interface

#endif // __SCENE_H__
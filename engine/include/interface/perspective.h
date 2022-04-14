#ifndef __PERSPECTIVE_H__
#define __PERSPECTIVE_H__

#include <tuple>

using namespace std;

namespace interface {
    class Perspective {
            tuple<float, float, float> cam_pos;
            tuple<float, float, float> cam_center;
            tuple<float, float, float> up;

        public:
            Perspective(float x, float y, float z);
            Perspective(
                    float pos_x, float pos_y, float pos_z,
                    float center_x, float center_y, float center_z,
                    float up_x, float up_y, float up_z
                    );

            void set_cam_pos(float x, float y, float z);
            tuple<float, float, float> get_cam_pos();

            void set_cam_center(float x, float y, float z);
            tuple<float, float, float> get_cam_center();

            void set_up(float x, float y, float z);
            tuple<float, float, float> get_up();
    };
}

#endif // __PERSPECTIVE_H__
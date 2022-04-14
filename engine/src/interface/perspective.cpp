#include "interface/perspective.h"
#include<tuple>

using namespace std;

namespace interface {
    Perspective::Perspective(float x, float y, float z) {
        cam_pos = make_tuple(x,y,z);
        cam_center = make_tuple(0,0,0);
        up = make_tuple(0,1,0);
    }

    Perspective::Perspective(float pos_x, float pos_y, float pos_z,
                             float center_x, float center_y, float center_z,
                             float up_x, float up_y, float up_z) {
        cam_pos = make_tuple(pos_x,pos_y,pos_z);
        cam_center = make_tuple(center_x,center_y,center_z);
        up = make_tuple(up_x,up_y,up_z);
    }

    void Perspective::set_cam_pos(float x, float y, float z) {
        cam_pos = make_tuple(x,y,z);
    }
    tuple<float,float,float> Perspective::get_cam_pos() {
        return cam_pos;
    }

    void Perspective::set_cam_center(float x, float y, float z) {
        cam_center = make_tuple(x,y,z);
    }
    tuple<float,float,float> Perspective::get_cam_center() {
        return cam_center;
    }

    void Perspective::set_up(float x, float y, float z) {
        up = make_tuple(x,y,z);
    }
    tuple<float,float,float> Perspective::get_up() {
        return up;
    }
}
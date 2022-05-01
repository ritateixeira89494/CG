#include "interface/view.h"

#include "interface/perspective.h"

namespace interface {
    View::View() {
        perspective = nullptr;

        div = 0.50;
        left = nullptr;
        right = nullptr;
    }

    View::View(Perspective *p) {
        perspective = p;

        div = 0.5;
        left = nullptr;
        right = nullptr;
    }

    View::View(float d) {
        perspective = nullptr;

        div = d;
        left = nullptr;
        right = nullptr;        
    }

    View::View(float d, View *l, View *r) {
        perspective = nullptr;

        div = d;
        left = l;
        right = r;
    }

    /*View::~View() {
        delete(left);
        delete(right);
    }*/

    void View::set_perspective(Perspective *p) {
        perspective = p;
    }
    Perspective *View::get_perpective() {
        return perspective;
    }

    void View::set_div(float d) {
        div = d;
    }
    float View::get_div() {
        return div;
    }

    void View::set_left(View *l) {
        left = l;
    }
    View **View::get_left() {
        return &left;
    }

    void View::set_right(View *r) {
        right = r;
    }
    View **View::get_right() {
        return &right;
    }
} // namespace interface
#ifndef __VIEW_H__
#define __VIEW_H__

#include "interface/perspective.h"

namespace interface {
    class View {
            Perspective *perspective;

            float div;
            View *left;
            View *right;

        public:
            View();
            explicit View(Perspective *p);
            explicit View(float div);
            View(float div, View *l, View *r);

            //~View();

            void set_perspective(Perspective *p);
            Perspective *get_perpective();

            void set_div(float d);
            float get_div();

            void set_left(View *l);
            View **get_left();

            void set_right(View *r);
            View **get_right();
    };
}

#endif // __VIEW_H__
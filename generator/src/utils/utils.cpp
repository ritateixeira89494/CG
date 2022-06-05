#include <tuple>
#include <fstream>

#include "utils/utils.h"
#include <cmath>

using namespace std;

void write_triangle(tuple<float, float, float> p1, tuple<float, float, float> p2, tuple<float, float, float> p3,
                    ofstream *file) {
    *file << "(" << get<0>(p1) << "," << get<1>(p1) << "," << get<2>(p1) << ");";
    *file << "(" << get<0>(p2) << "," << get<1>(p2) << "," << get<2>(p2) << ");";
    *file << "(" << get<0>(p3) << "," << get<1>(p3) << "," << get<2>(p3) << ")\n";
}

string replace_extension(string filepath, string newExt) {
    return filepath.replace(filepath.find_last_of(".") + 1, newExt.length(), newExt);
}

tuple<float,float,float> cross(tuple<float,float,float> a, tuple<float,float,float> b) {
    float xa,ya,za;
    float xb,yb,zb;

    std::tie(xa,ya,za) = a;
    std::tie(xb,yb,zb) = b;

    float x = ya*zb - za*yb;
	float y = za*xb - xa*zb;
	float z = xa*yb - ya*xb;

    return make_tuple(x,y,z);
}

tuple<float,float,float> normalize(tuple<float,float,float> p) {
    float x,y,z;
    std::tie(x,y,z) = p;

    float len = sqrt(x*x + y*y + z*z);

    return make_tuple(x/len,y/len,z/len);
}

}

void write_text_triangule(tuple<float, float> t1, tuple<float, float> t2, tuple<float, float> t3, ofstream &file) {
    file << "(" << get<0>(t1) << "," << get<1>(t1) << ");";
    file << "(" << get<0>(t2) << "," << get<1>(t2) << ");";
    file << "(" << get<0>(t3) << "," << get<1>(t3) << ")\n";
}
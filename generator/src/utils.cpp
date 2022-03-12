#include <tuple>
#include <fstream>

#include "utils.h"

using namespace std;

void write_triangle(tuple<float, float, float> p1, tuple<float, float, float> p2, tuple<float, float, float> p3, ofstream *file) {
    *file << "(" << get<0>(p1) << "," << get<1>(p1) << "," << get<2>(p1) << ");";
    *file << "(" << get<0>(p2) << "," << get<1>(p2) << "," << get<2>(p2) << ");";
    *file << "(" << get<0>(p3) << "," << get<1>(p3) << "," << get<2>(p3) << ")\n"; 
} 
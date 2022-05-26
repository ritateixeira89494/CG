#ifndef __UTILS_H__
#define __UTILS_H__

#include <tuple>

using namespace std;

void write_triangle(tuple<float, float, float> p1, tuple<float, float, float> p2, tuple<float, float, float> p3, ofstream *file);

string replace_extension(string filepath, string newExt);

#endif // __UTILS_H__
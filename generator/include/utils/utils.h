#ifndef __UTILS_H__
#define __UTILS_H__

#include <tuple>
#include <fstream>

using namespace std;

void write_triangle(tuple<float, float, float> p1, tuple<float, float, float> p2, tuple<float, float, float> p3,
                    ofstream *file);


void write_text_triangule(tuple<float, float> t1, tuple<float, float> t2, tuple<float, float> t3, ofstream &file);

string replace_extension(string filepath, string newExt);

tuple<float,float,float> cross(tuple<float,float,float> a, tuple<float,float,float> b);

tuple<float,float,float> normalize(tuple<float,float,float> p);

#endif // __UTILS_H__

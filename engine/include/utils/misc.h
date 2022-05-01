#ifndef __MISC_H__
#define __MISC_H__

#include <tuple>
#include <vector>
#include <cmath>

using namespace std;

template <typename T>

/**
 * @brief Splits the vector in two based on the parity of the indices
 * @tparam T Generic type
 * @return pair with both vectors (Evens on the left, Odds on the right)
 */
tuple<vector<T>,vector<T>> split_vector(vector<T> original) {
    int f_half = ceil(original.size() * 1.0f / 2);
    int s_half = original.size() - f_half;

    vector<T> first = {};
    vector<T> second = {};

    for(int i = 0; i < f_half; i++) {
        first.push_back(original[2*i]);
    }

    for(int i = 0; i < s_half; i++) {
        second.push_back(original[(2*i)+1]);
    }

    return make_tuple(first, second);
}

#endif //__MISC_H__

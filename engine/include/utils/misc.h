#ifndef __MISC_H__
#define __MISC_H__

#include <tuple>
#include <vector>
#include <cmath>

using namespace std;

template <typename T>

/**
 * @brief Splits the vector in half
 * @tparam T Generic type
 * @return pair with both halves of the original vector
 */
tuple<vector<T>,vector<T>> split_vector(vector<T> original) {
    size_t half = ceil(original.size() * 1.0f / 2);

    vector<T> first(original.begin(), original.begin() + half);
    vector<T> second(original.begin() + half, original.end());

    return make_tuple(first, second);
}

#endif //__MISC_H__

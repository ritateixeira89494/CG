#include "utils/misc.h"

#include <cmath>

string replace_extension(string filepath, string newExt) {
    return filepath.replace(filepath.find_last_of(".") + 1, newExt.length(), newExt);
}

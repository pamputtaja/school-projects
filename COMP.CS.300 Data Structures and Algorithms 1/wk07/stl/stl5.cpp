#include <iterator>
#include <vector>
#include <algorithm>

#include "test.hh"

using namespace std;

int compare(int a, int b) {
    if (a % 3 == b % 3) {
        if (a % 3 == 0) {
            return a < b;
        } else if (a % 3 == 1) {
            return a < b;
        } else {
            return a < b;
        }
    } else {
        return a % 3 < b % 3;
    }
}


/**
 * @brief Arrange vector in three subsequent sections:
 *        - those divisible by three (asc order)
 *        - those whose reminder is 1 (asc order)
 *        - those whose reminder is 2 (asc order)
 * @param v vector to be sorted
 * @return int EXIT_SUCCESS if everything went OK, EXIT_FAILURE otherwise
 */
int sortMod3(std::vector<int>& v)
{
    sort(v.begin(), v.end(), compare);
    return EXIT_SUCCESS;
}


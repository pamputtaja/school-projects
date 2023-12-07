#include <iterator>
#include <vector>
#include <algorithm>

#include "test.hh" // NOT_FOUND constant

using namespace std;


/**
 * @brief Find the median value of a given vector, whose elements are in random
 *        order. Return NOT_FOUND if the size of the vector is zero.
 *
 * @param v unsorted vector
 * @return int calculated median of parameter vector
 */
int findMedian(std::vector<int>& v)
{
    if (v.empty()) {
        return NOT_FOUND;
    }
    sort(v.begin(), v.end());
    int s = v.size();
    if(s % 2 == 0) {
        return((v.at(s/2-1)+v.at(s/2))/2); // parillinen
    } else {
        return v.at(s/2); // pariton
    }
}

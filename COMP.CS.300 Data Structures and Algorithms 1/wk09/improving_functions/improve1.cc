#include <iterator>
#include <vector>
#include <algorithm>


/**
 * @brief creates a vector of integers with ascending numbers from 0 - n-1
 *
 * @param n the size of the vector to be created
 * @return std::vector<int>
 */
std::vector<int> ascendingVector(int n){
    int i = 0;
    std::vector<int> v;
    v.reserve(n);
    while( i < n ) {
        v.push_back(i);
        i++;
    }
    return v;
}

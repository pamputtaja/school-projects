#include <iterator>
#include <vector>
#include <algorithm>

#include "test.hh"

using namespace std;

bool isEven(int i) {
   return ((i%2)==0);
}
/**
 * @brief Return an iterator which points to the last even integer of the vector
 *        If the value is not found, return v.rend()
 *
 * @param v the vector to be scanned through
 * @return std::vector<int>::reverse_iterator
 */
std::vector<int>::reverse_iterator findLastEven(std::vector<int>& v)
{
    vector<int>::reverse_iterator find_even = find_if(v.rbegin(), v.rend(), isEven);
    if (not isEven) {
        return v.rend();
    } else {
    return find_even;
    }
}




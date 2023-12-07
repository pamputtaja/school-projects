#include <iterator>
#include <vector>
#include <algorithm>

#include "test.hh"

using namespace std;


/**
 * @brief Return an iterator which points to the first instance of the given value
 *        If the value is not found, return v.end()
 * @param v vector to search for
 * @param given the value to be searched
 * @return std::vector<int>::iterator iterator to the found value
 */
std::vector<int>::iterator findGivenValue(std::vector<int>& v, int given)
{
    vector<int>::iterator find_value = find(v.begin(), v.end(), given);
    if (find_value != v.end()) {
        return find_value;
    } else {
        return v.end();
    }
}


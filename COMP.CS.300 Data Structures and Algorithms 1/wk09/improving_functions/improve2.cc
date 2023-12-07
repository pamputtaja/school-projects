#include <iterator>
#include <vector>
#include <algorithm>


/**
 * @brief Gets the smallest value from the vector passed as a parameter.
 *
 * @param vec vector which is searched for the smallest value.
 * @return int - the smallest value or 0 (zero) if vector is empty.
 */
int minValue(std::vector<int> vec){
    if ( vec.empty() ) { return 0; }

    int min = vec[0];
    for ( int i = 0; i < vec.size(); i++ ) {
        if( min > vec[i] ) {
            min = vec[i];
        }
    }
    return min;

    //if ( std::is_sorted(vec.begin(), vec.end()) ) {
    //    return vec[0];
    //} else {
    //    std::sort(vec.begin(), vec.end());
    //    return vec[0];
    //}
}

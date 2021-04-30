/*
 * Dynamic Programming Overview:
 * 1) Cast the problem as a search for an object over a certain "Search
 *    Space".
 * 2) Define clearly an objective function which is to be minimized (or
 *    maximized).
 * 3) Design an algorithm which partitions the search space, searches
 *    each partition recursively and finds the best in each partition,
 *    and returns the best of the best.
 * 4) Characterize the recursive calls in the above algorithm. Define a
 *    table for storing the results of the calls. Define a procedure
 *    "Fill" which will fill table entries using other table entries.
 *    "Fill" should not be recursive.
 */

#include <iostream>
#include <limits>
#include <vector>
#include <algorithm>

using namespace std;

int MAX = numeric_limits<int>::max();

int MCM(const vector<int>& D) {
    int size = (int)D.size();
    vector<vector<int>> table(size, vector<int>(size));
    
    for (int i = size-3; i >= 0; --i)
        for (int j = i+2; j < size; ++j) {
            int res = MAX;
            for (int k = i+1; k < j; ++k)
                res = min(
                    res,
                    table[i][k] + table[k][j] + D[i]*D[k]*D[j]
                );
            table[i][j] = res;
        }
        
    return table[0][size-1];
}

int main() {
    int N;
    cin >> N;
    
    vector<int> D(N+1);
    for (int i = 0; i < (int)D.size(); ++i)
        cin >> D[i];
        
    cout << MCM(D) << endl;
    
    return 0;
}

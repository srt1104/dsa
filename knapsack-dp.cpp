/*
 * Dynamic Programming review:
 * 1) Think about whether the optimization problem can be expressed
 *    as a sequence of decisions. (This is also needed in backtracking)
 * 2) Not "extending solution" but solving "solving smaller problem of
 *    the same kind". (Dynamic Programming idea 1)
 * 3) Check if the same problem is being solved again, if so save it so
 *    as to not solve it again.
 * 4) Do not use recurrence relations to estimate time.
 *    Instead use "transcript idea".
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> table;

int knapsackDP(
    const vector<int>& weights,
    const vector<int>& values,
    int C,
    int i
) {
    if (i == (int)weights.size()) {
        table[C][i] = 0;
        return table[C][i];
    }
        
    if (C < weights[i]) {
        if (table[C][i+1] == -1)
            table[C][i+1] = knapsackDP(weights, values, C, i+1);
        return table[C][i+1];
    }
    
    if (table[C][i+1] == -1)
        table[C][i+1] = knapsackDP(weights, values, C, i+1);
    if (table[C-weights[i]][i+1] == -1)
        table[C-weights[i]][i+1] =
            knapsackDP(weights, values, C-weights[i], i+1);
    
    return max(table[C][i+1], values[i] + table[C-weights[i]][i+1]);
}

int main() {
    int N;
    cin >> N;
    
    vector<int> weights(N), values(N);
    for (int i = 0; i < (int)weights.size(); ++i)
        cin >> weights[i];
    for (int i = 0; i < (int)values.size(); ++i)
        cin >> values[i];
        
    int C;
    cin >> C;
    
    table.resize(C+1, vector<int>(N+1, -1));
    cout << knapsackDP(weights, values, C, 0) << endl;
    
    return 0;
}

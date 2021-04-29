/*
 * 8-queens problem using backtracking.
 */

#include <iostream>
#include <vector>

using namespace std;

const int TOTAL_QUEENS = 8;

ostream& operator<< (ostream& out, const vector<int>& V) {
    for (int v: V)
        out << v << ' ';
    return out;
}

bool isValid(const vector<int>& columns) {
    for (int i = 0; i < (int)columns.size()-1; ++i)
        for (int j = i+1; j < (int)columns.size(); ++j)
            if (columns[i] == columns[j] ||
                abs(columns[i]-columns[j]) == abs(i-j))
                return false;
    return true;
}

bool search(vector<int>& columns, int column) {
    if (column == (int)columns.size()) {
        if (isValid(columns))
            return true;
        return false;
    }
    
    for (int row = 0; row < (int)columns.size(); ++row) {
        int temp = columns[column];
        columns[column] = row;
        if (search(columns, column+1))
            return true;
        columns[column] = temp;
    }
    return false;
}

int main() {
    vector<int> columns(TOTAL_QUEENS, -1);
    
    bool possible = search(columns, 0);
    if (possible)
        cout << columns << endl;
    
    return 0;
}

#include <iostream>
#include <vector>

using namespace std;

class BIT {
private:
    int size;
    vector<int> table;
    
public:
    BIT(int _size):
        size(_size), table(_size)
    {}
    
    void update(int i, int delta) {
        while (i < size) {
            table[i] += delta;
            i += i&-i;
        }
    }
    
    int sum(int i) {
        int sum = 0;
        
        while (i > 0) {
            sum += table[i];
            i -= i&-i;
        }
        
        return sum;
    }
    
    // calculate sum of range [i, j]
    int rangeSum(int i, int j) {
        return sum(j) - sum(i-1);
    }
    
    friend ostream& operator<< (ostream& out, const BIT& bit) {
        for (int v: bit.table)
            out << v << ' ';
        return out;
    }
};

int main() {
    int N;
    cin >> N;
    
    BIT bit(N+1);
    for (int i = 1; i <= N; ++i) {
        bit.update(i, i);
        cout << bit << endl;
    }
        
    for (int i = 1; i <= N; ++i)
        cout << bit.rangeSum(i, i) << ' ';
    cout << endl;
    
    cout << bit.rangeSum(1, N) << endl;
}

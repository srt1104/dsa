/*
 * Given a set of intervals, output the maximum no. intervals which they
 * pairwise do not overlap which each other.
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef pair<int, int> pii;

ostream& operator<< (ostream& out, const vector<pii>& V) {
    for (const pii& p: V)
        out << p.first << ' ' << p.second << endl;
    return out;
}

vector<pii> greedy(vector<pii>& I) {
    sort(I.begin(), I.end(), [](const pii& p1, const pii& p2) {
        return p1.second < p2.second;
    });
    
    vector<pii> res;
    for (int i = 0, end_time = 0; i < (int)I.size(); ++i) {
        if (I[i].first < end_time)
            continue;
            
        res.push_back(I[i]);
        end_time = I[i].second;
    }
    
    return res;
}

int main() {
    int N;
    cin >> N;
    
    vector<pii> I;
    for (int i = 0; i < N; ++i) {
        int s, e;
        cin >> s >> e;
        
        I.emplace_back(s, e);
    }
    
    cout << greedy(I) << endl;
    
    return 0;
}

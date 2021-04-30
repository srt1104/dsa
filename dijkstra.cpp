#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>

using namespace std;

typedef pair<int, int> pii;

int dijkstra(unordered_map<int, vector<pii>>& adj, int s, int t) {
    unordered_map<int, int> D;
    auto lambda = [](const pii& p1, const pii& p2) {
        return p1.second > p2.second;
    };
    priority_queue<pii, vector<pii>, decltype(lambda)> Q(lambda);
    
    Q.emplace(s, 0);
    while (!Q.empty()) {
        pii pu = Q.top();
        Q.pop();
        
        if (D.find(pu.first) != D.cend())
            continue;
        D[pu.first] = pu.second;
        
        for (pii& pv: adj[pu.first])
            Q.emplace(pv.first, pv.second + pu.second);
    }
    
    return D[t];
}

int main() {
    int E;
    cin >> E;
    
    unordered_map<int, vector<pii>> adj;
    for (int i = 0; i < E; ++i) {
        int u, v, cost;
        cin >> u >> v >> cost;
        
        adj[u].emplace_back(v, cost);
    }
    
    int s, t;
    cin >> s >> t;
    
    cout << dijkstra(adj, s, t) << endl;
    
    return 0;
}

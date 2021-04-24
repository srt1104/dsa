/*
 * diameter(G) = maximum distance between two vertices in G.
 * distance between two vertices = length of shortest path
 *      between two vertices
 * 
 * max level number <= diameter(G) <= 2 * max level number
 */

#include <iostream>
#include <vector>
#include <deque>

using namespace std;

pair<int, int> calculateDiameterUtil(
    const vector<vector<int>>& adj,
    int s
) {
    vector<int> levels(adj.size(), -1);
    
    deque<int> Q;
    
    Q.push_back(s);
    levels[s] = 0;
    pair<int, int> max_pair{s, 0};
    while (!Q.empty()) {
        int u = Q.front();
        Q.pop_front();
        
        for (int v: adj[u])
            if (levels[v] == -1) {
                Q.push_back(v);
                levels[v] = levels[u]+1;
                max_pair = make_pair(v, levels[v]);
            }
    }
    
    return max_pair;
}

int calculateDiameter(const vector<vector<int>>& adj) {
    pair<int, int> res;
    res = calculateDiameterUtil(adj, 0);
    res = calculateDiameterUtil(adj, res.first);
    
    return res.second;
}

int main() {
    int N;
    cin >> N;
    
    vector<vector<int>> adj(N);
    
    int M;
    cin >> M;
    for (int i = 0; i < M; ++i) {
        int u, v;
        cin >> u >> v;
        
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    cout << calculateDiameter(adj) << endl;
    
    return 0;
}

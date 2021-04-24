/*
 * G = (V, E) is a connected undirected graph.
 * G is bipartite if there exists a partition of V into U, W
 * such that V = U union W and U intersection W is null.
 * Every edge has one end point in U and the other in W.
*/

#include <iostream>
#include <vector>
#include <deque>

using namespace std;

bool isBipartite(const vector<vector<int>>& adj) {
    if (adj.empty())
        return true;
        
    vector<int> levels(adj.size(), -1);
    
    deque<int> Q;
    
    Q.push_back(0);
    levels[0] = 0;
    while (!Q.empty()) {
        int u = Q.front();
        Q.pop_front();
        
        for (int v: adj[u])
            if (levels[v] == -1) {
                Q.push_back(v);
                levels[v] = levels[u]+1;
            } else if (levels[v] == levels[u]) {
                return false;
            }
    }
    
    return true;
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
	
	cout << isBipartite(adj) << endl;
	
	return 0;
}

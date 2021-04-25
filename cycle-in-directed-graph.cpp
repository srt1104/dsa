/*
 * G = (V, E) is a directed graph.
 * If a back edge exists then there is a cycle.
 * It also means if there's no back edge then the graph is acyclic.
 * 
 * Tree edge:    arr[u] < arr[v] < dep[v] < dep[u]
 * Back edge:    arr[v] < arr[u] < dep[u] < dep[v]
 * Forward edge: arr[u] < arr[v] < dep[v] < dep[u]
 * Cross edge:   arr[v] < dep[v] < arr[u] < dep[u]
 * 
 * dep[u] < dep[v] holds only for back edge.
 */

#include <iostream>
#include <vector>

using namespace std;

int timer = 0;

void dfs(
    const vector<vector<int>>& adj,
    vector<bool>& visited,
    vector<int>& departure,
    int u
) {
    visited[u] = true;
    
    for (int v: adj[u])
        if (!visited[v])
            dfs(adj, visited, departure, v);
        
    departure[u] = timer++;
}

bool isCyclic(const vector<vector<int>>& adj) {
    int n = adj.size();
    vector<bool> visited(n);
    vector<int> departure(n);
    
    for (int i = 0; i < n; ++i)
        if (!visited[i])
            dfs(adj, visited, departure , i);
    
    for (int u = 0; u < (int)adj.size(); ++u)
        for (int v: adj[u])
            if (departure[u] < departure[v])
                return true;
    return false;
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
    }
    
    cout << isCyclic(adj) << endl;
    
    return 0;
}

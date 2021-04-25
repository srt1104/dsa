/*
 * G = (V, E) is a directed acyclic graph (DAG).
 * Topological sort of a DAG is the linear ordering of its vertices
 * such that for every directed edge u->v, u comes before v in ordering.
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

ostream& operator<< (ostream& out, const vector<int>& V) {
    for (int v: V)
        out << v << ' ';
    return out;
}

void dfs(
    const vector<vector<int>>& adj,
    vector<bool>& visited,
    vector<int>& sortedVertices,
    int u
) {
    visited[u] = true;
    
    for (int v: adj[u])
        if (!visited[v])
            dfs(adj, visited, sortedVertices, v);
            
    sortedVertices.push_back(u);
}

vector<int> topologicalSort(const vector<vector<int>>& adj) {
    int n = adj.size();
    vector<bool> visited(n);
    vector<int> sortedVertices;
        
    for (int i = 0; i < n; ++i)
        if (!visited[i])
            dfs(adj, visited, sortedVertices, i);
            
    reverse(sortedVertices.begin(), sortedVertices.end());
    return sortedVertices;
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
    
    cout << topologicalSort(adj) << endl;
    
    return 0;
}

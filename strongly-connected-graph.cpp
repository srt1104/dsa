/*
 * G = (V, E) is a directed graph
 * G is strongly connected if there is a path in each direction between
 * each pair of vertices of the graph. So basically, every edge of G
 * should be part of a cycle. For that, it is necessary and sufficient
 * that an edge goes out of the subtree (dfs tree) of every node in G.
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

constexpr int ROOT = 0;
int timer = 0;

int isStronglyConnectedUtil(
    const vector<vector<int>>& adj,
    vector<int>& arrival,
    int u
) {
    // deepest non-tree-edge
    int dnte = arrival[u] = timer++;
    
    for (int v: adj[u])
        if (arrival[v] == -1)   // corresponds to tree edge
            dnte = min(dnte, isStronglyConnectedUtil(adj, arrival, v));
        else                    // corresponds to non-tree-edge
            dnte = min(dnte, arrival[v]);
            
    if (u != ROOT && dnte == arrival[u])    // make exception for root
        return -1;
    return dnte;
}

void dfs(const vector<vector<int>>& adj, vector<bool>& visited, int u) {
    visited[u] = true;
    
    for (int v: adj[u])
        if (!visited[v])
            dfs(adj, visited, v);
}

bool isStronglyConnected(const vector<vector<int>>& adj) {
    int n = adj.size();
    vector<bool> visited(n);
    
    int count = 0;
    for (int i = 0; i < n; ++i)
        if (!visited[i]) {
            ++count;
            dfs(adj, visited, i);
        }
        
    // from an arbitrary vertex,
    // if it's not possible to reach other vertices,
    // the graph can't be strongly connected.
    if (count != 1)
        return false;
        
    vector<int> arrival(n, -1);
    int dnte = isStronglyConnectedUtil(adj, arrival, ROOT);
    return dnte == -1 ? false : true;
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
    
    cout << isStronglyConnected(adj) << endl;
    
    return 0;
}

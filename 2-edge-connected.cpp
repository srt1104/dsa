/*
 * G = (V, E) is a connected undirected graph.
 * G is 2-edge connected iff G-{e} is connected for all e in E.
 * 
 * Basically every edge should be part of a cycle.
 * So calculate the deepest back edge (dbe) emanating from the subtree
 * rooted at a node N (make sure to not count the tree edge with its
 * parent P as back edge) and if it ends up at it's parent P or above in
 * the dfs tree, this P->N edge is part of a cycle.
 * If this is true for every edge, the graph is 2-edge connected.
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int timer = 0;

int is2EdgeConnectedUtil(
    const vector<vector<int>>& adj,
    vector<int>& arrival,
    int p,
    int u
) {
    int dbe = arrival[u] = timer++;
    
    for (int v: adj[u])
        if (arrival[v] == -1)   // corresponds to tree edge
            dbe = min(dbe, is2EdgeConnectedUtil(adj, arrival, u, v));
        else if (v != p)        // corresponds to back edge
            dbe = min(dbe, arrival[v]);
            
    if (p != -1 && dbe == arrival[u])   // made exception for root
        return -1;
    return dbe;
}

bool is2EdgeConnected(const vector<vector<int>>& adj) {
    vector<int> arrival(adj.size(), -1);
    int dbe = is2EdgeConnectedUtil(adj, arrival, -1, 0);
    
    return dbe == -1 ? false : true;
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
    
    cout << is2EdgeConnected(adj) << endl;
    
    return 0;
}

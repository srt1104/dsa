#include <iostream>
#include <vector>
#include <deque>

using namespace std;

void connectedComponentsUtil(
	const vector<vector<int>>& adj,
	vector<bool>& visited,
	int s
) {
	deque<int> Q;
	
	Q.push_back(s);
	visited[s] = true;
	while (!Q.empty()) {
		int u = Q.front();
		Q.pop_front();
		
		for (int v: adj[u])
			if (!visited[v]) {
				Q.push_back(v);
				visited[v] = true;
			}
	}
}

int connectedComponents(const vector<vector<int>>& adj) {
	vector<bool> visited(adj.size());
	
	int count = 0;
	for (int i = 0; i < (int)visited.size(); ++i)
		if (!visited[i]) {
			++count;
			connectedComponentsUtil(adj, visited, i);
		}
		
	return count;
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
	
	cout << connectedComponents(adj) << endl;
	
	return 0;
}

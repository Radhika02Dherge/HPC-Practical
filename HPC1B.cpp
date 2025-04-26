#include <iostream>
#include <vector>
#include <stack>
#include <omp.h>
using namespace std;

const int MAX = 1e5;
vector<int> graph[MAX];
bool visited[MAX];

void dfs(int node) {
    stack<int> s;
    s.push(node);
    while (!s.empty()) {
        int curr = s.top(); s.pop();
        if (!visited[curr]) {
            visited[curr] = true;
            cout << curr << " ";
            #pragma omp parallel for
            for (int i = 0; i < graph[curr].size(); i++)
                if (!visited[graph[curr][i]])
                    s.push(graph[curr][i]);
        }
    }
}

int main() {
    int n, m, start;
    cout << "Enter No of Nodes, Edges, and Start Node: ";
    cin >> n >> m >> start;

    cout << "Enter Edge Pairs:\n";
    for (int i = 0, u, v; i < m; i++) {
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    #pragma omp parallel for
    for (int i = 0; i < n; i++) visited[i] = false;

    dfs(start);
    return 0;
}
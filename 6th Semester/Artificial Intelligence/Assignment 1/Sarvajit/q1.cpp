#include <bits/stdc++.h>
using namespace std;
vector<vector<int> > createGraph()
{
    vector<vector<int> > graph(11);
    graph[1].push_back(2);
    graph[1].push_back(5);
    graph[1].push_back(8);
    graph[2].push_back(9);
    graph[8].push_back(6);
    graph[8].push_back(4);
    graph[8].push_back(3);
    graph[6].push_back(10);
    graph[6].push_back(7);
    return graph;
}
bool dfs(vector<vector<int> > &graph, int root, int destination)
{
    if (root == destination)
    {
        cout << destination << " ";
        return true;
    }
    else
    {
        for (int i = 0; i < graph[root].size(); i++)
        {
            if (dfs(graph, graph[root][i], destination))
            {
                cout << root << " ";
                return true;
            }
        }
        return false;
    }
}
void printpath(vector<int> &path)
{
    int size = path.size();
    for (int i = size - 1; i >= 0; i--)
        cout << path[i] << " ";
    cout << endl;
}

// utility function to check if current
// vertex is already present in path
int isNotVisited(int x, vector<int> &path)
{
    int size = path.size();
    for (int i = 0; i < size; i++)
        if (path[i] == x)
            return 0;
    return 1;
}

void bfs(vector<vector<int> > &g, int src, int dst, int v)
{
    queue<vector<int> > q;
    vector<int> path;
    path.push_back(src);
    q.push(path);
    while (!q.empty())
    {
        path = q.front();
        q.pop();
        int last = path[path.size() - 1];
        if (last == dst)
            printpath(path);
        for (int i = 0; i < g[last].size(); i++)
        {
            if (isNotVisited(g[last][i], path))
            {
                vector<int> newpath(path);
                newpath.push_back(g[last][i]);
                q.push(newpath);
            }
        }
    }
}
signed main()
{
    vector<vector<int> > graph = createGraph();
    int source = 1, destination = 3;
    cout << "DFS : ";
    dfs(graph, source, destination);
    cout << endl;
    cout << "BFS : ";
    bfs(graph, source, destination, 11);
}
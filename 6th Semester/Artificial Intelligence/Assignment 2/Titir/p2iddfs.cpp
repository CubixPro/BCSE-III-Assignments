#include <iostream>
#include <vector>
using namespace std;

vector<int> dfs(vector<vector<int>> g, int s, int d, vector<bool> &visited, vector<int> p, int limit)
{

    p.push_back(s);
    if (p.size() > limit)
    {
        vector<int> g(1, -1);
        return g;
    }
    if (s == d)
    {
        cout << "Reached Goal Node\n";
        return p;
    }
    for (int i = 0; i < g[s].size(); i++)
    {
        if (visited[g[s][i]] == false)
        {
            vector<int> temp;
            temp = dfs(g, g[s][i], d, visited, p, limit);
            if (temp[0] != -1)
            {
                return temp;
            }
        }
    }
    {
        vector<int> g(1, -1);
        return g;
    }
}

void iddfs(vector<vector<int>> g, int s, int dest)
{
    int nodes = g.size();
    for (int i = 1; i < nodes; i++)
    {
        vector<bool> visited(nodes, false);
        vector<int> p;
        vector<int> path = dfs(g, s, dest, visited, p, i);
        if (path[0] == -1)
        {
            continue;
        }
        else
        {
            //cout << "Solution Found!";
            for (int i = 0; i < path.size(); i++)
            {
                cout << path[i] << ' ';
            }

            return;
        }
    }
    cout << "no solution";
}

int main()
{
    int nodes;
    int conn;
    cin >> nodes;
    cin >> conn;
    vector<vector<int>> graph(nodes);
    for (int i = 0; i < conn; i++)
    {
        int x, y;
        cin >> x >> y;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }
    int source;
    int dest;
    cin >> source >> dest;
    vector<bool> visited(nodes, false);
    iddfs(graph, source, dest);
}
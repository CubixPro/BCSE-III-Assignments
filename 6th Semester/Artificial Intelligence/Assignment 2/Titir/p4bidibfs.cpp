#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int foundS(vector<bool> v1, vector<bool> v2)
{
    for (int i = 0; i < v1.size(); i++)
    {
        if (v1[i] && v2[i])
        {
            return i;
        }
    }
    return -1;
}
bool bdibfs(vector<vector<int>> g, int s, int d)
{
    int nodes = g.size();

    int b = 1;

    for (int k = 1; k <= nodes; k++)
    {
        vector<bool> visited1(nodes, false);
        vector<bool> visited2(nodes, false);
        queue<int> queue1;
        queue<int> queue2;

        vector<vector<int>> path1(nodes), path2(nodes);
        queue1.push(s);
        queue2.push(d);

        while (!queue1.empty() && !queue2.empty())
        {
            queue<int> tempq1;
            queue<int> tempq2;

            while (!queue1.empty())
            {
                if (!visited1[queue1.front()])
                    tempq1.push(queue1.front());
                visited1[queue1.front()] = true;
                queue1.pop();
            }
            while (!queue2.empty())
            {
                if (!visited2[queue2.front()])
                    tempq2.push(queue2.front());
                visited2[queue2.front()] = true;
                queue2.pop();
            }
            int x = foundS(visited1, visited2);
            if (x != -1)
            {
                for (int i = 0; i < path1[x].size(); i++)
                {
                    cout << path1[x][i] << ' ';
                }
                cout << x << ' ' ;
                for (int i = path2[x].size() - 1 ; i >= 0; i--)
                {
                    cout << path2[x][i] << ' ';
                }
                return true;
            }

            while (!tempq1.empty())
            {
                int node = tempq1.front();
                tempq1.pop();
                int tempk = k;
                for (int i = 0; i < min(tempk, (int)g[node].size()); i++)
                {
                    if (!visited1[g[node][i]])
                    {
                        queue1.push(g[node][i]);
                        path1[g[node][i]] = path1[node];
                        path1[g[node][i]].push_back(node);
                    }
                    else
                    {
                        tempk++;
                    }
                }
            }
            while (!tempq2.empty())
            {
                int node = tempq2.front();
                tempq2.pop();
                int tempk = k;
                for (int i = 0; i < min(tempk, (int)g[node].size()); i++)
                {
                    if (!visited2[g[node][i]])
                    {
                        queue2.push(g[node][i]);
                        path2[g[node][i]] = path2[node];
                        path2[g[node][i]].push_back(node);
                    }
                    else
                    {
                        tempk++;
                    }
                }
            }
            string dummy;
        }
    }
    return false;
}

int main()
{
    int nodes;
    int conn;
    cin >> nodes;
    cin >> conn;
    vector<vector<int>> graph(nodes + 1);
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
    vector<bool> visited(nodes + 1, false);
    vector<int> path;
    //vector<int> finalans;
    bool finalans = bdibfs(graph, source, dest);
    if(finalans){
        cout << "\nSolution Found\n";
    } 
    else{
        cout << "\nSolution Not Found\n";
    }
}
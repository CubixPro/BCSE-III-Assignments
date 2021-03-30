#include <bits/stdc++.h>

using namespace std;


//--------------------DFS---------------------------//
vector<int> dfs(vector<vector<int>> g, int s, int d, vector<bool>& visited, vector<int> p){
    visited[s] = true;
    p.push_back(s);
    if(s == d){
        cout << "Reached Goal Node\n";
        return p;
    }
    for(int i = 0 ; i < g[s].size(); i++)
    {
        if(visited[g[s][i]] == false)
        {
            vector<int> temp;
            temp = dfs(g, g[s][i], d, visited, p);
            if(temp[0] != -1){
                return temp;
            }
        }
    }
    {
        vector<int> g(1, -1); 
        return g;
    }
}


//--------------------BFS------------------------------
vector<int> bfs(vector<vector<int>> g, int s, int d){
    vector<bool> visited(g.size() , false);
    queue<pair<int, vector<int>>> q;
    vector<int> path;
    path.push_back(s);
    q.push({s, path});
    while(!q.empty()){
        pair<int, vector<int>> p = q.front();
        visited[p.first] = true;
        q.pop();
        if(p.first == d){
            cout << "Found destination node! \n";
            return p.second;
        }
        else{
            for(int i  = 0 ; i < g[p.first].size() ; i++){
                int next_node = g[p.first][i];
                if(visited[next_node] == false)
                {
                    vector<int> temp = p.second;
                    temp.push_back(next_node);
                    q.push({next_node, temp});
                }
            }
        }

    }
    vector<int> res(1, -1);
    return res;
}


int main(){
    int nodes;
    int conn;
    cin >> nodes;
    cin >> conn;
    vector<vector<int>> graph(nodes + 1);
    for(int i = 0 ; i < conn ; i++){
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
    vector<int> finalans; 
    finalans = dfs(graph, source, dest, visited, path);
    for(int i = 0 ; i < finalans.size() ; i++){
        cout << finalans[i] << ' ';
    }
    //bfs(graph, source, dest);
    cout << '\n' ;
    finalans = bfs(graph, source, dest);
    for(int i = 0 ; i < finalans.size() ; i++){
        cout << finalans[i] << ' ';
    }

}
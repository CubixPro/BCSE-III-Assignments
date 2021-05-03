

#include<iostream>
#include<vector>
#include<queue>
using namespace std;
struct ComparePair{
    bool operator()(pair<int, int> a, pair<int, int> b){
        return a.second >  b.second;
    }
};

int bestfs(vector<vector<pair<int, int>>> graph, int s, int d, vector<bool> &visited, int count){
    if(s == d){
        cout << "solution found";
        return count;
    }
    else{
        visited[s] = true;
       priority_queue< pair<int, int>, vector<pair<int, int>>, ComparePair> q ;
        for(int i = 0 ; i < graph[s].size() ; i++){
            if(!visited[graph[s][i].first])
            {
                q.push(graph[s][i]);
            }
        }
        while(!q.empty()){
           int val = bestfs(graph, q.top().first, d, visited, ++count );
           if(val != -1)
           {
               return val;
           }
        }
        return -1;
    } 
}

int main(){
    int nodes;
    cin >> nodes;
    vector<vector<pair<int, int>>> graph(nodes);
    vector<bool> visited(nodes, false);
    int connections;
    cin >> connections;
    for(int i = 0 ; i < connections ; i++ )
    {
        int x, y, h;
        cin >> x >> y >> h;
        graph[x].push_back({y, h});//undirected graph
    }
    int s, d;
    cin >> s >> d;
    cout << bestfs(graph, s, d, visited, 0) << "\n";
}

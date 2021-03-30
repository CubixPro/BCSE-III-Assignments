#include <bits/stdc++.h>

using namespace std;
int n, m;

vector<pair<int, int>> bfs(pair<int, int> s, pair<int, int> d, vector<vector<bool>> maze){
    set<pair<int, int>> visited;
    queue<pair<pair<int, int>, vector<pair<int, int> > > > q;
    vector<pair<int, int>> path;

    path.push_back(s);
    q.push({s, path});
    
    while(!q.empty()){
        pair<pair<int, int>, vector<pair<int, int> > > p = q.front();
        visited.insert(p.first);
        q.pop();

        if(p.first == d){
            cout << "Reached end of maze! \n";
            return p.second;
        }
        else{
            vector<pair<int, int>> newnodes;
            pair<int, int> change[4] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
            for(int i = 0 ; i < 4 ; i++){
                newnodes.push_back({p.first.first + change[i].first, p.first.second + change[i].second});
            }
            for(int i = 0 ; i < 4 ; i++){
                pair<int, int> nextnode = newnodes[i];
                if(newnodes[i].first < 0 || newnodes[i].second < 0 || newnodes[i].first >= n || newnodes[i].second >= m){
                    continue;
                }
                if(visited.find(nextnode) == visited.end() && maze[nextnode.first][nextnode.second]){
                    vector<pair<int, int>> temp = p.second;
                    temp.push_back(nextnode);
                    q.push({nextnode, temp});
                }
            }

        }
    }
    vector<pair<int, int>> res(1, {-1, -1});
    return res;
}

int main(){
    cin >> n >> m;
    vector<vector<bool>> maze(n, vector<bool>(m));
    vector<string> mazerunner(n);
    for(int i = 0 ;  i < n ; i++){
        string str;
        cin >> str;
        mazerunner[i] = str;
        for(int j = 0 ; j < m ; j++){
            if(str[j] == '*')
            {
                maze[i][j] = false;
            }
            else{
                maze[i][j] = true;
            }
        }
    }

    int si, sj;
    int ei, ej;
    cin >> si >> sj;
    cin >> ei >> ej;

    vector<pair<int, int>> res_path;
    res_path = bfs({si, sj}, {ei, ej},  maze);

    for(int i = 0 ; i < res_path.size() ; i++){
        cout << res_path[i].first << ' ' << res_path[i].second << '\n';
    }

   for(int i = 0 ; i < res_path.size() ; i++){
       mazerunner[res_path[i].first][res_path[i].second] = '.';
   } 
   mazerunner[ei][ej] = 'X';
   for(int i = 0 ; i < mazerunner.size() ; i++){
       cout << mazerunner[i] << '\n';
   }

}
#include <bits/stdc++.h>
using namespace std;

set<pair<int, int>> nodes;


vector<pair<int, int>> dfs(pair<int, int> s, pair<int, int> d, int lj, int rj, vector<pair<int, int>> path)
{
    nodes.insert(s);
    path.push_back(s);
    if((d.first == -1 && s.second == d.second) || (d.second == -1 && s.first == d.first) || s == d){
        cout << "Reached final configuration\n";
        return path;
    }
    vector<pair<int, int>> nextnodes;
    nextnodes.push_back({s.first -  (min(s.first + s.second, rj) - s.second), min(s.first + s.second, rj)});
    nextnodes.push_back({min(s.first + s.second, lj), s.second - (min(s.first + s.second, lj) - s.first)});
    nextnodes.push_back({0, s.second});
    nextnodes.push_back({s.first, 0});
    nextnodes.push_back({lj, s.second});
    nextnodes.push_back({s.first, rj});

    for(int i = 0 ; i < nextnodes.size() ; i++){
        if(nextnodes[i].first < 0 || nextnodes[i].second < 0)
        {
            continue;
        }
        if(nodes.find(nextnodes[i]) == nodes.end())
        {
            vector<pair<int, int>> temp;
            temp = dfs(nextnodes[i], d, lj, rj, path);
            if(temp[0].first != -1)
            {
                return temp;
            }
        }
    }

    vector<pair<int, int>> res(1, {-1, -1});
    return res;



}

int main(){
    int lj, rj;//right jug and right jug min capacity
    int lrj, frj;//final left jug and right jug capacity (if -1 then it does not matter)


//     cin >> lj >> rj;
//     cin >> lrj >> frj;
    
    
    int n;
    cin >> n;
    int jugsize[n];
    for (int i = 0 ; i  < n ; i++){
        cin >> jugsize[i];
    }



    pair<int, int> source = {0, 0};
    pair<int, int> dest = {lrj, frj};

    vector<pair<int, int>> path;
    path = dfs(source, dest, lj, rj, path);
    for(int i = 0 ; i < path.size() ; i++){
        if(i != (path.size() - 1))
            cout << "(" << path[i].first << ", " << path[i].second << ") => ";
        else{
            cout << "(" << path[i].first << ", " << path[i].second << ")";
        }
    }
}


#include<iostream>
#include<vector>
#include <set>
using namespace std;

set<vector<vector<int>> > visited;

bool end(vector<vector<int>> a){
    vector<vector<int>> b;
    b = {{-1, 1, 2}, {3, 4, 5}, {6, 7, 8}};
    if(a == b){
        return true;
    }
    return false;
}

bool validGap(pair<int, int> gap){
    if(gap.first < 3 && gap.second < 3 && gap.first >= 0 && gap.second >= 0){
        return true;
    }
    return false;
}


vector<vector<int>> swap(vector<vector<int>> g, pair<int, int> a, pair<int, int> b){
    int temp = g[a.first][a.second];
    g[a.first][a.second] = g[b.first][b.second];
    g[b.first][b.second] = temp;
    return g;
}

void print(vector<vector<int>> g){
    for(int i =  0 ; i < 3 ; i++){
        for(int j = 0 ; j < 3 ; j++){
            cout << g[i][j] << ' ';
        }
        cout << '\n';
    }
    cout << '\n';
}

int dlimitedsearch(vector<vector<int>> start, pair<int, int> gap,  vector<vector<vector<int>> > path, int limit, int curr){
    if(end(start)){
        cout << "Solution found\n";
        for(int i = 0 ; i < path.size() ; i++){
            print(path[i]);
        }
        return 1;
    }
    visited.insert(start);
    //print(start);
    path.push_back(start);
    if(curr > limit){
        return -1;
    }
    pair<int, int> movement[4] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    for(int i = 0 ;  i < 4 ; i++){
        pair<int, int> new_gap = {gap.first + movement[i].first, gap.second + movement[i].second};
        if(validGap(new_gap)){
           vector<vector<int>> new_g = swap(start, new_gap, gap) ;
           if(visited.find(new_g) == visited.end()){

            int x = dlimitedsearch(new_g, new_gap, path, limit, curr + 1);
            if (x == 1){
                return 1;
            }
           }

        }
    }
    return -1;
}


int main(){
    cout << "Enter start State(if gap type -1) : \n";
    vector<vector<int>> puzzle(3, vector<int>(3));
    pair<int, int> gap;
    for(int i = 0 ; i < 3 ; i++){
        for(int j = 0 ; j < 3; j++){
            cin >> puzzle[i][j];
            if(puzzle[i][j] == -1){
                gap = {i, j};
            }
        }

    }
    vector<vector<vector<int>> > path;
    dlimitedsearch(puzzle, gap, path, 31, 0);
}
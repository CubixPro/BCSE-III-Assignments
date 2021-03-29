#include <bits/stdc++.h>
using namespace std;

int TOTALM, TOTALC;
class mcstate
{
public:
    int m, c;
    char side;
    mcstate()
    {
        m = 0;
        c = 0;
        side = 'L';
    }
    mcstate(int m, int c, char side)
    {
        this->m = m;
        this->c = c;
        this->side = side;
    }

    bool valid()
    {
        if (m >= 0 && c >= 0 && m <= TOTALM && c <= TOTALC && (m == 0 || m >= c) && ((TOTALM - m) == 0 || (TOTALM - m) >= (TOTALC - c)))
        {
            return true;
        }
        return false;
    }

    friend bool operator<(const mcstate a, const mcstate b);
    friend bool operator==(const mcstate a, const mcstate b);
};

bool operator==(const mcstate a, const mcstate b){
    return (a.m == b.m && a.c == b.c && a.side == b.side);
}

bool operator<(const mcstate a, const mcstate b)
{
    return (a.m < b.m) || (a.m == b.m && a.c < b.c) || (a.m == b.m && a.c == b.c && a.side < b.side);
}

vector<mcstate> bfs(mcstate s, mcstate d)
{
    set<mcstate> visited;
    queue<pair<mcstate, vector<mcstate>>> q;
    vector<mcstate> path;
    path.push_back(s);
    q.push({s, path});

    while (!q.empty())
    {
        pair<mcstate, vector<mcstate>> p = q.front();
        visited.insert(p.first);
        q.pop();

        if (p.first.m == d.m && p.first.c == d.c && p.first.side == d.side)
        {
            cout << "All of them have crossed the river\n";
            return p.second;
        }
        else
        {
            char toggle = (p.first.side == 'L') ? 'R' : 'L';
            vector<mcstate> nextnodes;
            pair<int, int> change[6] = {{1, 1}, {2, 0}, {0, 2}, {0, 1}, {1, 0}};

            if (p.first.side == 'L')
            {
                for (int i = 0; i < 5; i++)
                {
                    mcstate newmc(p.first.m - change[i].first, p.first.c - change[i].second, toggle);
                    nextnodes.push_back(newmc);
                }
            }
            else{
                for (int i = 0; i < 5; i++)
                {
                    mcstate newmc(p.first.m + change[i].first, p.first.c + change[i].second, toggle);
                    nextnodes.push_back(newmc);
                }
 
            }

            for (int i = 0; i < nextnodes.size(); i++)
            {
                mcstate nextnode = nextnodes[i];
                if (!nextnode.valid())
                    continue;
                else
                {
                    if (visited.find(nextnode) == visited.end())
                    {
                        vector<mcstate> temp = p.second;
                        temp.push_back(nextnode);
                        q.push({nextnode, temp});
                        //cout << nextnode.m << ' ' << nextnode.c << ' ' << nextnode.side << '\n';
                    }
                }
            }
        }
    }
    vector<mcstate> res(1);
    mcstate emp(-1, -1, 'L');
    res[0] = emp;
    return res;
}

int main()
{
    int m, c;
    cin >> m >> c;
    TOTALM = m;
    TOTALC = c;
    mcstate s(m, c, 'L');
    mcstate d(0, 0, 'R');

    vector<mcstate> respath = bfs(s, d);
    for(int i = 0 ; i < respath.size() ; i++){
        mcstate nextnode = respath[i];
        cout << nextnode.m << ' ' << nextnode.c << ' ' << nextnode.side << '\n';

    }
}

/*
3,3 
2,2 1,1
2,2 0,1
*/
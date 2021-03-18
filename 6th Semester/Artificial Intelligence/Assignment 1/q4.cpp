#include <bits/stdc++.h>
using namespace std;

struct node
{
    int x;
    int y;
    int pre;
};
int m, n;
int head = 0;
int tail = 1;
node start, EN;

int dis[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

// Print and retrospective output of final results
void print_path(int tail, node *que)
{
    if (que[tail].pre != -1)
        print_path(que[tail].pre, que);
    cout << "(" << que[tail].x << "," << que[tail].y << ")"
         << "\n";
    return;
}

int BFS(vector<vector<int> > map, node *que)
{
    node point;
    point = start;
    que[head] = point;
    vector<vector<int> > flag(m, vector<int>(n, 0));
    flag[point.x][point.y] = 1;
    while (head < tail)
    {
        for (int i = 0; i < 4; i++)
        {
            int tx = que[head].x + dis[i][0];
            int ty = que[head].y + dis[i][1];
            //cout << flag[0].size() << flag.size();
            //cout << map[tx][ty] << flag[tx][ty];
            if (tx < m && tx >= 0 && ty < n && ty >= 0 && map[tx][ty] == 0)
                if (flag[tx][ty] == 0)
                {
                    que[tail].x = tx;
                    que[tail].y = ty;
                    que[tail].pre = head;
                    flag[tx][ty] = 1;
                    if (tx == EN.x && ty == EN.y)
                    {
                        //head is the first step to the end point.
                        return tail;
                    }
                    tail++;
                }
        }
        head++;
    }
    return 0;
}

int main()
{
    while (cin >> m >> n)
    {
        node *que = new node[n * m];
        head = 0;
        tail = 1;
        start.x = 0;
        start.y = 0;
        start.pre = -1;
        EN.x = m - 1;
        EN.y = n - 1;
        EN.pre = -1;
        vector<vector<int> > map(m, vector<int>(n, 0));
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cin >> map[i][j];
            }
        }
        int tail = BFS(map, que);
        print_path(tail, que);
        delete[] que;
    }

    return 0;
}
/**
 *      USACO 2020 - 12 - Problem 1 - Replication
 *
 */

#include <bits/stdc++.h>

using namespace std;

int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};
const int N = 1000;
int dist1[N][N], dist2[N][N];
bool board[N][N], start[N][N], reach[N][N];
int n, d;

bool isValid(int x, int y) 
{
    return x >= 0 && x < n && y >= 0 && y < n;
}

void bfs1()
{
    memset(dist1, -1, sizeof dist1);

    queue<pair<int, int>> q;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            if (!board[i][j]) {
                q.push(make_pair(i, j));
                dist1[i][j] = 0;
            }
        }

    while (!q.empty())
    {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();

        for (int i = 0; i < 4; i++)
        {
            int newX = x + dx[i];
            int newY = y + dy[i];
            if (isValid(newX, newY) && dist1[newX][newY] == -1) {
                dist1[newX][newY] = dist1[x][y] + 1;
                q.push(make_pair(newX, newY));
            }
        }
    }
}

void bfs2()
{
    memset(dist2, -1, sizeof dist2);

    queue<pair<int, int>> q;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            if (start[i][j]) {
                q.push(make_pair(i, j));
                dist2[i][j] = 0;
            }
        }

    while (!q.empty())
    {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();

        if (dist2[x][y] / d >= dist1[x][y]) {
            continue;
        }

        for (int i = 0; i < 4; i++)
        {
            int newX = x + dx[i];
            int newY = y + dy[i];
            if (isValid(newX, newY) && board[newX][newY] && dist2[newX][newY] == -1) {
                if (dist2[newX][newY] / d >= dist1[newX][newY]) {
                    continue;
                }

                dist2[newX][newY] = dist2[x][y] + 1;
                q.push(make_pair(newX, newY));
            }
        }
    }
}

void bfs3()
{
    memset(reach, false, sizeof reach);

    priority_queue<pair<int, pair<int, int>>> pq;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            if (dist2[i][j] != -1) {
                pq.push(make_pair(min(dist1[i][j]-1, dist2[i][j]/d), make_pair(i, j)));
                reach[i][j] = true;
            }
        }

    while (!pq.empty())
    {
        int x = pq.top().second.first;
        int y = pq.top().second.second;
        int value = pq.top().first;
        pq.pop();

        if (value == 0) {
            continue;
        }

        for (int i = 0; i < 4; i++)
        {
            int newX = x + dx[i];
            int newY = y + dy[i];
            if (isValid(newX, newY) && board[newX][newY] && !reach[newX][newY]) {
                reach[newX][newY] = true;
                pq.push(make_pair(value-1, make_pair(newX, newY)));
            }
        }
    }
}

int main()
{
    cin >> n >> d;

    for (int i = 0; i < n; i++)
    { 
        string str;
        cin >> str;
        for (int j = 0; j < n; j++)
        {
            board[i][j] = (str[j] != '#');
            start[i][j] = (str[j] == 'S');
        }
    }

    bfs1();
    bfs2();
    bfs3();

    int result = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            if (reach[i][j]) {
                result++;
            }
        }

    cout << result << endl;

    return 0;
}

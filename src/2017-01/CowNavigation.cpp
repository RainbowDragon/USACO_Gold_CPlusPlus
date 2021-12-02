/**
 *      USACO 2017 - 01 - Problem 3 - Cow Navigation
 *
 */

#include <bits/stdc++.h>

using namespace std;

int n;

bool isValid(int x, int y) 
{
    return x >= 0 && x < n && y >= 0 && y < n;
}

bool isFinal(int x, int y)
{
    return x == 0 && y == n-1;
}

int main()
{
    string FileName = "cownav";

    ifstream fin (FileName + ".in");
    ofstream fout (FileName + ".out");

    fin >> n;

    char grid[n][n];
    for (int i = 0; i < n; i++)
    {
        string str;
        fin >> str;
        for (int j = 0; j < n; j++)
        {
            grid[i][j] = str[j];
        }
    } 

    int dx[4] = {-1, 0, 1, 0};
    int dy[4] = {0, 1, 0, -1};

    int distance[n][n][4][n][n][4];
    memset(distance, -1, sizeof distance);

    queue<pair<tuple<int,int,int>, tuple<int,int,int>>> q;
    q.push({{n-1,0,0}, {n-1,0,1}});
    distance[n-1][0][0][n-1][0][1] = 0;

    int result = 0;
    while (!q.empty())
    {
        pair<tuple<int,int,int>, tuple<int,int,int>> state = q.front();
        q.pop();

        int x1 = get<0>(state.first);
        int y1 = get<1>(state.first);
        int d1 = get<2>(state.first);

        int x2 = get<0>(state.second);
        int y2 = get<1>(state.second);
        int d2 = get<2>(state.second);
        
        if (x1 == 0 && y1 == n-1 && x2 == 0 && y2 == n-1) {
            result = distance[x1][y1][d1][x2][y2][d2];
            break;
        }

        int nd1 = (d1 + 3) % 4;
        int nd2 = (d2 + 3) % 4;
        if (distance[x1][y1][nd1][x2][y2][nd2] == -1) {
            q.push({{x1,y1,nd1}, {x2,y2,nd2}});
            distance[x1][y1][nd1][x2][y2][nd2] = distance[x1][y1][d1][x2][y2][d2] + 1;
        }

        nd1 = (d1 + 1) % 4;
        nd2 = (d2 + 1) % 4;
        if (distance[x1][y1][nd1][x2][y2][nd2] == -1) {
            q.push({{x1,y1,nd1}, {x2,y2,nd2}});
            distance[x1][y1][nd1][x2][y2][nd2] = distance[x1][y1][d1][x2][y2][d2] + 1;
        }

        int nx1 = x1 + dx[d1];
        int ny1 = y1 + dy[d1];
        if (!isValid(nx1, ny1) || isFinal(x1, y1) || grid[nx1][ny1] == 'H') {
            nx1 = x1;
            ny1 = y1;
        }

        int nx2 = x2 + dx[d2];
        int ny2 = y2 + dy[d2];
        if (!isValid(nx2, ny2) || isFinal(x2, y2) || grid[nx2][ny2] == 'H') {
            nx2 = x2;
            ny2 = y2;
        }

        if (distance[nx1][ny1][d1][nx2][ny2][d2] == -1) {
            q.push({{nx1,ny1,d1}, {nx2,ny2,d2}});
            distance[nx1][ny1][d1][nx2][ny2][d2] = distance[x1][y1][d1][x2][y2][d2] + 1;
        }
    }

    fout << result << endl;

    fin.close();
    fout.close();

    return 0;
}
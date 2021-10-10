/**
 *      USACO 2016 - 01 - Problem 2 - Radio Contact
 *
 */

#include <bits/stdc++.h>

using namespace std;

vector<pair<int, int>> FP;
vector<pair<int, int>> BP; 

long long getDistance(pair<int, int> p1, pair<int, int> p2)  
{
    long long result = (p1.first - p2.first)*(p1.first - p2.first) + (p1.second - p2.second)*(p1.second - p2.second);
    return result;
}

int main ()
{
    string FileName = "radio";

    ifstream fin (FileName + ".in");
    ofstream fout (FileName + ".out");

    int n, m;
    fin >> n >> m;
    int fx, fy, bx, by;
    fin >> fx >> fy >> bx >> by;
    string fs, bs;
    fin >> fs >> bs;

    map<char, int> dx, dy;
    dx['E'] = 1; dx['W'] = -1;
    dy['N'] = 1; dy['S'] = -1;

    FP.push_back(make_pair(fx, fy));
    for (int i = 0; i < n; i++)
    {
        fx += dx[fs[i]];
        fy += dy[fs[i]];
        FP.push_back(make_pair(fx, fy));
    }

    BP.push_back(make_pair(bx, by));
    for (int i = 0; i < m; i++)
    {
        bx += dx[bs[i]];
        by += dy[bs[i]];
        BP.push_back(make_pair(bx, by));
    }

    long long dp[n+1][m+1];
    dp[0][0] = 0;
    for (int i = 1; i <= n; i++)
    {
        dp[i][0] = dp[i-1][0] + getDistance(FP[i], BP[0]);    
    }

    for (int i = 1; i <= m; i++)
    {
        dp[0][i] = dp[0][i-1] + getDistance(FP[0], BP[i]);    
    }

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            dp[i][j] = min(dp[i-1][j], dp[i][j-1]);
            dp[i][j] = min(dp[i][j], dp[i-1][j-1]);
            dp[i][j] += getDistance(FP[i], BP[j]);
        }
    }

    fout << dp[n][m] << endl;

    fin.close();
    fout.close();

    return 0;
}
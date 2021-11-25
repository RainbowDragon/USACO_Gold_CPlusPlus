/**
 *      USACO 2020 - 01 - Problem 1 - Time is Mooney
 *
 */

#include <bits/stdc++.h>

using namespace std;

int main()
{
    string FileName = "time";

    ifstream fin (FileName + ".in");
    ofstream fout (FileName + ".out");

    int n, m, c;
    fin >> n >> m >> c;

    int moonies[n];
    for (int i = 0; i < n; i++)
    {
        fin >> moonies[i];
    }

    pair<int, int> edges[m];
    for (int i = 0; i < m; i++)
    {
        int s, t;
        fin >> s >> t;
        s--;
        t--;
        edges[i] = make_pair(s, t);
    }

    long long dp[1001][n];
    memset(dp, -1, sizeof dp);

    dp[0][0] = 0;
    long long result = 0;
    
    for (int t = 1; t <= 1000; t++)
    {
        for (int i = 0; i < m; i++)
        {
            if (dp[t-1][edges[i].first] >= 0) {
                dp[t][edges[i].second] = max(dp[t][edges[i].second], dp[t-1][edges[i].first] + moonies[edges[i].second]);
            }     
        }
        result = max(result, dp[t][0] - c*t*t);
    }

    fout << result << endl;

    fin.close();
    fout.close();

    return 0;
}
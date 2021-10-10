/**
 *      USACO 2015 - 12 - Problem 2 - Fruit Feast
 *
 */

#include <bits/stdc++.h>

using namespace std;

int main()
{
    string FileName = "feast";

    ifstream fin (FileName + ".in");
    ofstream fout (FileName + ".out");

    int t, a, b;
    fin >> t >> a >> b;

    bool dp[t+1][2];
    dp[0][0] = true;
    dp[0][1] = true;

    int result = 0;
    for (int i = 1; i <= t; i++)
    {
        dp[i][0] = false;
        dp[i][1] = false;
        if ((i >= a && dp[i-a][0]) || (i >= b && dp[i-b][0])) {
            dp[i][0] = true;
            dp[i/2][1] = true;
            result = max(result, i);
        }
    }

    for (int i = 1; i <= t; i++)
    {
        if ((i >= a && dp[i-a][1]) || (i >= b && dp[i-b][1])) {
            dp[i][1] = true;
            result = max(result, i);
        }
    }

    fout << result << endl;

    fin.close();
    fout.close();

    return 0;
}
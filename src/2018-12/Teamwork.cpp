/**
 *      USACO 2018 - 12 - Problem 3 - Teamwork
 *
 */

#include <bits/stdc++.h>

using namespace std;

int main()
{
    string FileName = "teamwork";

    ifstream fin (FileName + ".in");
    ofstream fout (FileName + ".out");

    int n, k;
    fin >> n >> k;

    int skills[n+1];
    for (int i = 1; i <= n; i++)
    {
        fin >> skills[i];
    }

    int dp[n+1];
    memset(dp, 0, sizeof dp);

    for (int i = 1; i <= n; i++)
    {
        int maxSkill = skills[i];
        for (int j = 0; j < k && i+j <= n; j++)
        {
            maxSkill = max(maxSkill, skills[i+j]);
            dp[i+j] = max(dp[i+j], dp[i-1] + maxSkill*(j+1));
        }
    }

    fout << dp[n] << endl;

    fin.close();
    fout.close();

    return 0;
}
/**
 *      USACO 2017 - 01 - Problem 2 - Hoof, Paper, Scissors
 *
 */

#include <bits/stdc++.h>

using namespace std;

int main()
{
    string FileName = "hps";

    ifstream fin (FileName + ".in");
    ofstream fout (FileName + ".out");

    int n, k;
    fin >> n >> k;

    unordered_map<char, int> map;
    map['H'] = 0;
    map['P'] = 1;
    map['S'] = 2;
    
    int gestures[n];
    for (int i = 0; i < n; i++)
    {
        char c;
        fin >> c;
        gestures[i] = map[c];    
    }

    int dp[n+1][k+1][3];
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= k; j++)
            for (int g = 0; g < 3; g++)
            {
                if (i == 0) {
                    dp[i][j][g] = 0;
                }
                else {
                    if (j == 0) {
                        dp[i][j][g] = dp[i-1][j][g] + (g == gestures[i-1] ? 1 : 0); 
                    }
                    else {
                        int g1 = (g + 1) % 3;
                        int g2 = (g + 2) % 3;
                        dp[i][j][g] = max(max(dp[i-1][j][g], dp[i-1][j-1][g1]), dp[i-1][j-1][g2]);
                        dp[i][j][g] += (g == gestures[i-1] ? 1 : 0);
                    }
                }
            }

    int result = max(max(dp[n][k][0], dp[n][k][1]), dp[n][k][2]);
    fout << result << endl;
    
    fin.close();
    fout.close();

    return 0;
}
/**
 *      USACO 2021 - 02 - Problem 2 - Modern Art 3
 *
 */

#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n;
    cin >> n;

    int paints[n+1];
    for (int i = 1; i <= n; i++)
    { 
        cin >> paints[i];
    }

    int dp[n+1][n+1];
    memset(dp, n+1, sizeof dp);
    for (int i = 1; i <= n; i++)
    {
        dp[i][i] = 1;
    }

    for (int length = 2; length <= n; length++)
        for (int i = 1; i+length-1 <= n; i++)
        {
            int j = i + length - 1;

            if (paints[i] == paints[j]) {
                dp[i][j] = dp[i][j-1];
            }
            else {
                for (int k = i; k < j; k++)
                {
                    dp[i][j] = min(dp[i][j], dp[i][k]+dp[k+1][j]);
                }
            }
        }
    
    cout << dp[1][n] << endl;

    return 0;
}
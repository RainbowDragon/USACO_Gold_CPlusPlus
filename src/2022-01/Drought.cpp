/**
 *      USACO 2022 - 01 - Problem 1 - Drought
 *
 */

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

ll MOD = 1000000007;

int main()
{
    int n;
    cin >> n;
    int hunger[n];

    int lowest = INT_MAX;
    int highest = 0;
    for (int i = 0; i < n; i++)
    {
        cin >> hunger[i];
        lowest = min(lowest, hunger[i]);
        highest = max(highest, hunger[i]);
    }

    ll result = 0;

    if (n % 2 == 0) {
    
        ll dp[n][highest+1];
 
        for (int i = 0; i <= hunger[0]; i++)
        {
            dp[0][i] = 1;
        }

        for (int i = 1; i < n; i++)
        {
            for (int j = 0; j <= hunger[i]; j++)
            {
                if (hunger[i-1] - j >= 0) {
                    dp[i][j] = dp[i-1][hunger[i-1]-j] % MOD;
                }
                else {
                    dp[i][j] = 0;
                }
            }

            for (int j = 1; j <= hunger[i]; j++)
            {
                dp[i][j] += dp[i][j-1];
                dp[i][j] %= MOD;
            }
        }

        result = dp[n-1][hunger[n-1]];
    }
    else {

        ll dp[n][highest+1];

        for (int k = 0; k <= lowest; k++)
        {
            for (int i = 0; i <= hunger[0]; i++)
            {
                dp[0][i] = 1;
            }

            for (int i = 1; i < n; i++)
            {
                for (int j = 0; j <= hunger[i]; j++)
                {
                    if (hunger[i-1] - j >= 0) {
                        dp[i][j] = dp[i-1][hunger[i-1]-j] % MOD;
                    }
                    else {
                        dp[i][j] = 0;
                    }
                }

                for (int j = 1; j <= hunger[i]; j++)
                {
                    dp[i][j] += dp[i][j-1];
                    dp[i][j] %= MOD;
                }
            }

            result += dp[n-1][hunger[n-1]];
            result %= MOD;

            for (int i = 0; i < n; i++)
            {
                hunger[i]--;
            }
        }
    }

    cout << result << endl;
    
    return 0;
}

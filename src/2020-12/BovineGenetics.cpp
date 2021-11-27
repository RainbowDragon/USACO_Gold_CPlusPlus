/**
 *      USACO 2020 - 12 - Problem 1 - Bovine Genetics
 *
 */

#include <bits/stdc++.h>

using namespace std;

int main()
{
    int MOD = 1000000007;

    string str;
    cin >> str;
    int n = str.length();

    unordered_map<char, int> map;
    map['A'] = 0;
    map['G'] = 1;
    map['C'] = 2;
    map['T'] = 3;
    map['?'] = 4;

    long long dp[n][4][4][4];
    memset(dp, 0, sizeof dp);

    for (int x = 0; x < 4; x++)
        for (int y = 0; y < 4; y++)
        {
            if (map[str[0]] == x || map[str[0]] == 4) {
                dp[0][x][x][y] = 1;
            }
        }

    for (int i = 1; i < n; i++)
        for (int x = 0; x < 4; x++)
            for (int y = 0; y < 4; y++)
                for (int z = 0; z < 4; z++)
                {
                    if (map[str[i]] == 4) {
                        for (int c = 0; c < 4; c++)
                        {
                            if (y == z) {
                                dp[i][c][c][x] = (dp[i][c][c][x] + dp[i-1][x][y][z]) % MOD; 
                            }

                            if (y != c) {
                                dp[i][x][c][z] = (dp[i][x][c][z] + dp[i-1][x][y][z]) % MOD;
                            }                            
                        }
                    }
                    else {
                        int c = map[str[i]];

                        if (y == z) {
                            dp[i][c][c][x] = (dp[i][c][c][x] + dp[i-1][x][y][z]) % MOD; 
                        }

                        if (y != c) {
                            dp[i][x][c][z] = (dp[i][x][c][z] + dp[i-1][x][y][z]) % MOD;
                        }
                    }
                }

    long long result = 0;
    for (int x = 0; x < 4; x++)
        for (int y = 0; y < 4; y++)
        {
            result = (result + dp[n-1][x][y][y]) % MOD;
        }

    cout << result << endl;
    
    return 0;
}
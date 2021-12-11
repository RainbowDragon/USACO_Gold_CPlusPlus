/**
 *      USACO 2021 - Open - Problem 3 - Permutation
 *
 */

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const ll MOD = 1000000007;
const int N = 41;
pair<ll, ll> points[N];
int ins[N][N][N];
ll dp[N][N][N][N];

int n;

ll area(int i, int j, int k)
{
    ll result = points[i].first*points[j].second + points[j].first*points[k].second + points[k].first*points[i].second - points[i].first*points[k].second - points[j].first*points[i].second - points[k].first*points[j].second;
    return result > 0 ? result : result*(-1);
}

bool isIn(int i, int j, int k, int l)
{
    ll result = area(i, j, k) - area(i, j, l) - area(j, k, l) - area(k, i, l);
    return result == 0;
}

void add(ll &x, ll y)
{
    x = (x + y) % MOD;
}

void trans(int p, int i, int j, int k, int x, int y, int z)
{
    if (z < x) {
        swap(x, z);
    }
    if (z < y) {
        swap(y, z);
    }

    add(dp[i][j][k][p], dp[x][y][z][p-1]);
}

int main()
{
    cin >> n;

    for (int i = 1; i <= n; i++)
    {
        ll x, y; 
        cin >> x >> y;
        points[i] = make_pair(x, y);
    }

    for (int i = 1; i <= n-2; i++)
        for (int j = i+1; j <= n-1; j++)
            for (int k = j+1; k <= n; k++)
            {
                ins[i][j][k] = 0;
                for (int l = 1; l <= n; l++)
                {
                    if (l ^ i && l ^ j && l ^ k && isIn(i, j, k, l)) {
                        ins[i][j][k]++;
                    }
                }
            }

    for (int i = 1; i <= n-2; i++)
        for (int j = i+1; j <= n-1; j++)
            for (int k = j+1; k <= n; k++)
            {
                dp[i][j][k][3] = 6;
            }

    for (int p = 4; p <= n; p++)
        for (int i = 1; i <= n-2; i++)
            for (int j = i+1; j <= n-1; j++)
                for (int k = j+1; k <= n; k++)
                {
                    if (ins[i][j][k] + 4 - p > 0) {
                        add(dp[i][j][k][p], (dp[i][j][k][p-1]*(ins[i][j][k] + 4 - p) % MOD));
                    }

                    for (int l = 1; l <= n; l++)
                    {
                        if (l ^ i && l ^ j && l ^ k && isIn(i, j, k, l)) {
                            trans(p, i, j, k, i, j, l);
                            trans(p, i, j, k, j, k, l);
                            trans(p, i, j, k, i, k, l);
                        }
                    }
                }

    ll result = 0;
    for (int i = 1; i <= n-2; i++)
        for (int j = i+1; j <= n-1; j++)
            for (int k = j+1; k <= n; k++)
            {
                add(result, dp[i][j][k][n]);
            }

    cout << result << endl;

    return 0;
}

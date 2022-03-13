/**
 *      USACO 2022 - 02 - Problem 1 - Redistributing Gifts
 *
 */

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

vector<int> graph;
vector<ll> table;
int n;

ll solve(int mask) 
{
    if (table[mask] == 0) {

        vector<int> bits;
        for (int i = 0; i < n; i++)
        {
            if (mask & (1 << i)) {
                bits.push_back(i);
            }
        }

        int count = bits.size();
        int subgraph[count];
        for (int i = 0; i < count; i++)
        {
            subgraph[i] = 0;
            for (int j = 0; j < count; j++)
            {
                if (graph[bits[i]] & (1 << bits[j])) {
                    subgraph[i] = subgraph[i] | (1 << j);
                }
            }
        }

        int total = 1 << count;
        ll dp[total];
        memset(dp, 0, sizeof dp);
        dp[0] = 1;
        for (int s = 0; s < total; s++)
        {
            int pair_num = __builtin_popcount(s);
            for (int i = 0; i < count; i++)
            {
                if (!(s & (1 << i)) && (subgraph[pair_num] & (1 << i))) {
                    dp[s | (1 << i)] += dp[s];
                }
            }
        }

        table[mask] = dp[total-1];
    }

    return table[mask];
}

int main()
{
    cin >> n;

    graph.resize(n, 0);
    table.resize((1 << n), 0);

    for (int i = 0; i < n; i++)
    {
        bool seen = false;
        for (int j = 0; j < n; j++)
        {
            int k;
            cin >> k;
            k--;
            if (!seen) {
                graph[i] |= (1 << k);
            }

            if (k == i) {
                seen = true;
            }
        }
    }

    int q;
    cin >> q;
    ll results[q];
    for (int i = 0; i < q; i++)
    {
        string breed;
        cin >> breed;
        int G = 0, H = 0;
        for (int j = 0; j < n; j++)
        {
            if (breed[j] == 'G') {
                G |= (1 << j);
            }
            else {
                H |= (1 << j);
            }
        }

        results[i] = solve(G) * solve(H);
    }
    
    for (int i = 0; i < q; i++)
    {
        cout << results[i] << endl;
    }

    return 0;
}

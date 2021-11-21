/**
 *      USACO 2020 - 02 - Problem 2 - Help Yourself
 *
 */

#include <bits/stdc++.h>

using namespace std;

int main()
{
    string FileName = "help";

    ifstream fin (FileName + ".in");
    ofstream fout (FileName + ".out");

    int MOD = 1000000007;

    int n;
    fin >> n;

    vector<int> starts(n);
    vector<int> preSum(2*n+1, 0);
    vector<long long> power2(n+1);

    for (int i = 0; i < n; i++)
    {
        int start, end;
        fin >> start >> end;
        starts[i] = start;
        preSum[end]++;
    }

    for (int i = 1; i <= 2*n; i++)
    {
        preSum[i] += preSum[i-1];
    }

    power2[0] = 1;
    for (int i = 1; i <= n; i++)
    {
        power2[i] = (power2[i-1] * 2) % MOD;
    }

    sort(starts.begin(), starts.end());

    long long result = 0;

    for (int i = 0; i < n; i++)
    {
        int x = preSum[starts[i] - 1];
        result = (result * 2) % MOD;
        result = (result + power2[x]) % MOD;
    }

    fout << result << endl;
    
    fin.close();
    fout.close();

    return 0;
}
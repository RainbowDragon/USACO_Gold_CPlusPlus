/**
 *      USACO 2020 - 02 - Problem 1 - Timeline
 *
 */

#include <bits/stdc++.h>

using namespace std;

int main()
{
    string FileName = "timeline";

    ifstream fin (FileName + ".in");
    ofstream fout (FileName + ".out");

    int n, m, c;
    fin >> n >> m >> c;

    int results[n+1];
    for (int i = 1; i <= n; i++)
    {
        fin >> results[i];
    }

    vector<pair<int, int>> edges[n+1];
    vector<int> pre(n+1, 0);
    for (int i = 0; i < c; i++)
    {
        int a, b, x;
        fin >> a >> b >> x;
        edges[a].push_back(make_pair(b, x));
        pre[b]++;
    }

    queue<int> q;
    for (int i = 1; i <= n; i++)
    {
        if (pre[i] == 0) {
            q.push(i);
        }
    }

    while (!q.empty())
    {
        int index = q.front();
        q.pop();
        for (pair<int, int> p : edges[index])
        {
            results[p.first] = max(results[p.first], results[index]+p.second);
            pre[p.first]--;
            if (pre[p.first] == 0) {
                q.push(p.first);
            }
        }
    }

    for (int i = 1; i <= n; i++)
    {
        fout << results[i] << endl;
    }

    fin.close();
    fout.close();

    return 0;
}
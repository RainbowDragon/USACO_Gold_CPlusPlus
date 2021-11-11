/**
 *      USACO 2016 - Open - Problem 2 - Closing the Farm
 *
 */

#include <bits/stdc++.h>

using namespace std;

struct DSU 
{
    vector<int> roots;
    int count;

    void init (int n) 
    {
        count = n; 
        roots = vector<int>(n);
        for (int i = 0; i < n; i++)
        {
            roots[i] = i;
        }
    }

    int getRoot (int x) 
    { 
        if (roots[x] == x) {
            return x;
        }
        else {
            return getRoot(roots[x]);
        }
    }

    void unite (int x, int y) 
    {
        x = getRoot(x);
        y = getRoot(y);
        if (x < y) {
            roots[y] = x;
            count--;
        }
        else if (x > y) {
            roots[x] = y;
            count--;
        }
    }
};

int main()
{
    string FileName = "closing";

    ifstream fin (FileName + ".in");
    ofstream fout (FileName + ".out");

    int n, m;
    fin >> n >> m;

    vector<vector<int>> paths(n);
    for (int i = 0; i < m; i++)
    {
        int s, t;
        fin >> s >> t;
        s--;
        t--;
        paths[s].push_back(t);
        paths[t].push_back(s);
    }
    
    int closeDown[n];
    bool open[n];
    for (int i = 0; i < n; i++)
    {
        int index;
        fin >> index;
        index--;
        closeDown[i] = index;
        open[i] = false;
    }

    DSU dsu;
    dsu.init(n);
    bool results[n];
    for (int i = n-1; i >= 0; i--)
    {
        open[closeDown[i]] = true;
        for (int to : paths[closeDown[i]])
        {
            if (open[to]) {
                dsu.unite(to, closeDown[i]);
            }
        }

        results[i] = (dsu.count == (i+1));
    }

    for (int i = 0; i < n; i++)
    {
        if (results[i]) {
            fout << "YES" << endl;
        }
        else {
            fout << "NO" << endl;
        }
    }

    fin.close();
    fout.close();

    return 0;
}
/**
 *      USACO 2018 - 01 - Problem 1 - MooTube
 *
 */

#include <bits/stdc++.h>

using namespace std;

struct DSU 
{
    vector<pair<int,int>> roots;

    void init(int n) 
    { 
        roots = vector<pair<int,int>>(n);
        for (int i = 0; i < n; i++)
        {
            roots[i] = {i, 1};
        }
    }

    int getRoot(int x) 
    {
        if (roots[x].first == x) {
            return x;
        }
        else {
            roots[x].first = getRoot(roots[x].first); 
            return roots[x].first;
        }
    }
	
    int getSize(int x) 
    { 
        return roots[getRoot(x)].second; 
    }
	
    bool unite(int x, int y) 
    {
        x = getRoot(x); 
        y = getRoot(y);
        
        if (x == y) {
            return false;
        }
        
        if (roots[x] > roots[y]) {
            swap(x, y);
        }

        roots[x].second += roots[y].second;
        roots[y].first = x;
        
        return true;
    }
};

int main()
{
    string FileName = "mootube";

    ifstream fin (FileName + ".in");
    ofstream fout (FileName + ".out");

    int n, q;
    fin >> n >> q;

    vector<pair<int, pair<int, int>>> edges(n - 1);
    for (int i = 0; i < n - 1; i++)
    {
        int s, t, w;
        fin >> s >> t >> w;
        s--; 
        t--;
        edges[i] = make_pair(w, make_pair(s, t));
    }

    vector<pair<int, pair<int, int>>> queries(q);
    for (int i = 0; i < q; i++)
    {
        int k, v;
        fin >> k >> v;
        v--;
        queries[i] = make_pair(k, make_pair(i, v));
    }

    sort(edges.begin(), edges.end(), greater<pair<int, pair<int, int>>>());
    sort(queries.begin(), queries.end(), greater<pair<int, pair<int, int>>>());

    DSU dsu;
    dsu.init(n);
    vector<int> results(q);
    int idx = 0;
    for (auto query: queries) 
    {
        int v = query.second.second;
        int curK = query.first;

        while (idx < (int) edges.size() && edges[idx].first >= curK) 
        {
            dsu.unite(edges[idx].second.first, edges[idx].second.second);
            idx++;
        }

        results[query.second.first] = dsu.getSize(v) - 1;
    }

    for (int i = 0; i < q; i++)
    {
        fout << results[i] << endl;
    }

    fin.close();
    fout.close();

    return 0;
}
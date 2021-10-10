/**
 *      USACO 2018 - 01 - Problem 1 - MooTube
 *
 */

#include <bits/stdc++.h>

using namespace std;

struct DSU 
{
    vector<int> e;

    void init (int n) { e = vector<int>(n, -1); }

    int get (int x) { return e[x] < 0 ? x : e[x] = get(e[x]); };

    bool sameSet (int x, int y) { return get(x) == get(y); };
	
    int size (int x) { return -e[get(x)]; }
	
    bool unite (int x, int y) 
    {
	    x = get(x), y = get(y);
	    if (x == y) return false;
	    if (e[x] > e[y]) swap(x, y);
	    e[x] += e[y];
	    e[y] = x;
		return true;
    }
};

int main ()
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

        results[query.second.first] = dsu.size(v) - 1;
    }

    for (int i = 0; i < q; i++)
    {
        fout << results[i] << endl;
    }

    fin.close();
    fout.close();

    return 0;
}
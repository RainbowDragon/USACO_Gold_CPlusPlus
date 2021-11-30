/**
 *      USACO 2016 - 12 - Problem 2 - Cow Checklist
 *
 */

#include <bits/stdc++.h>

using namespace std;

int distance(pair<int, int> p1, pair<int, int> p2)
{
    return (p1.first - p2.first)*(p1.first - p2.first) + (p1.second - p2.second)*(p1.second - p2.second);
}

int main()
{
    string FileName = "checklist";

    ifstream fin (FileName + ".in");
    ofstream fout (FileName + ".out");

    int h, g;
    fin >> h >> g;

    pair<int, int> hcows[h+1];
    for (int i = 1; i <= h; i++)
    {
        int x, y;
        fin >> x >> y;
        hcows[i] = make_pair(x, y);
    }

    pair<int, int> gcows[g+1];
    for (int j = 1; j <= g; j++)
    {
        int x, y;
        fin >> x >> y;
        gcows[j] = make_pair(x, y);
    }

    long long dpH[h+1][g+1];
    memset(dpH, 1000*1000, sizeof dpH);

    long long dpG[h+1][g+1];
    memset(dpG, 1000*1000, sizeof dpG);

    dpH[1][0] = 0;
    for (int i = 2; i <= h; i++)
    {
        dpH[i][0] = dpH[i-1][0] + distance(hcows[i-1], hcows[i]);
    }

    for (int i = 1; i <= h; i++)
        for (int j = 1; j <= g; j++)
        {
            dpH[i][j] = min(dpH[i][j], dpH[i-1][j] + distance(hcows[i-1], hcows[i]));
            dpH[i][j] = min(dpH[i][j], dpG[i-1][j] + distance(gcows[j], hcows[i]));

            dpG[i][j] = min(dpG[i][j], dpG[i][j-1] + distance(gcows[j-1], gcows[j]));
            dpG[i][j] = min(dpG[i][j], dpH[i][j-1] + distance(hcows[i], gcows[j]));
        }

    fout << dpH[h][g] << endl;

    fin.close();
    fout.close();

    return 0;
}

/**
 *      USACO 2016 - 01 - Problem 1 - Angry Cows
 *
 */

#include <bits/stdc++.h>

using namespace std;

int main()
{
    string FileName = "angry";

    ifstream fin (FileName + ".in");
    ofstream fout (FileName + ".out");

    int n;
    fin >> n;

    vector<int> points(n);
    for (int i = 0; i < n; i++)
    {
        fin >> points[i];
    }
    sort(points.begin(), points.end());
    
    int result = 0;

    fout << result << endl;

    fin.close();
    fout.close();

    return 0;
}
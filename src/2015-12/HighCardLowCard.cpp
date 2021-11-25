/**
 *      USACO 2015 - 12 - Problem 1 - High Card Low Card
 *
 */

#include <bits/stdc++.h>

using namespace std;

int main()
{
    string FileName = "cardgame";

    ifstream fin (FileName + ".in");
    ofstream fout (FileName + ".out");

    int n;
    fin >> n;
    int N = 2 * n;
    int k = n / 2;

    bool hasCard[N];
    bool firstHalf[N];
    memset(hasCard, false, sizeof hasCard);
    memset(firstHalf, false, sizeof firstHalf);

    for (int i = 0; i < n; i++) 
    {
        int value;
        fin >> value;
        value--;
        hasCard[value] = true;
        firstHalf[value] = (i < k);
    }

    int bessie[n];
    int elsie[n];

    int bi = 0;
    int e1 = 0;
    int e2 = k;
    for (int i = 0; i < N; i++)
    {
        if (hasCard[i]) {
            if (firstHalf[i]) {
                elsie[e1] = i;
                e1++;
            }
            else {
                elsie[e2] = i;
                e2++;
            }
        }
        else { 
            bessie[bi] = i;
            bi++;
        }
    }

    int result = 0;

    bi = n - 1;
    int ei = k - 1;
    while (ei >= 0) 
    {
        if (bessie[bi] > elsie[ei]) {
            bi--;
            result++;
        }
        ei--;
    }

    bi = 0;
    ei = k;
    while (ei < n) 
    {
        if (bessie[bi] < elsie[ei]) {
            bi++;
            result++;
        }
        ei++;
    }

    fout << result << endl;

    fin.close();
    fout.close();

    return 0;
}
/**
 *      USACO 2022 - 02 - Problem 2 - Cow Camp
 *
 */

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;

int T, K;
ld prob[1001], pre_prob[1001], suf_exp[1001];

ld nextExp(ld a, ld b, ld E, int k)
{
    return pow(a, k)*E + b*(1 - pow(a, k))/(1 - a);
}

int main()
{
    cin >> T >> K;
    T--;

    prob[0] = pow(0.5, T);
    pre_prob[0] = prob[0];
    for (int i = 1; i <= T; i++)
    {
        prob[i] = prob[i-1] * (T - i + 1) / i;
        pre_prob[i] = prob[i] + pre_prob[i-1];
    }

    suf_exp[T] = T * prob[T];
    for (int i = T-1; i >= 0; i--)
    {
        suf_exp[i] = suf_exp[i+1] + i * prob[i];
    }

    /* this will pass the first 9 cases.
    ld E = T * 0.5;
    for (int i = 1; i < K; i++)
    {
        int index = floor(E);
        E = E * pre_prob[index] + suf_exp[index+1];
    }
    */

    K--;
    ld E = T * 0.5;
    while (K > 0)
    {
        int index = floor(E);
        ld a = pre_prob[index];
        ld b = suf_exp[index+1];

        int low = 1;
        int high = 1;
        while (low*2 <= K && nextExp(a , b, E, low*2) < index+1)
        {
            low = low * 2;
        }
        high = low * 2;
        while (low < high)
        {
            int mid = (low + high) / 2;
            if (nextExp(a , b, E, low*2) < index+1) {
                low = mid + 1;
            }
            else {
                high = mid;
            }
        }
        low = min(low, K);
        K = K - low;
        E = nextExp(a, b, E, low);
    }

    cout << setprecision(10);
    cout << E+1 << endl;

    return 0;
}

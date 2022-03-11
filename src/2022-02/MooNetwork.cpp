/**
 *      USACO 2022 - 02 - Problem 3 - Moo Network
 *
 */

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int N;
pair<int, int> cows[100001];
vector<pair<int, ll>> edges[100001];

void addEdge(int i, int j) 
{
    ll a = cows[i].first;
    ll b = cows[i].second;
    ll c = cows[j].first;
    ll d = cows[j].second;

    ll weight = (a - c)*(a - c) + (b - d)*(b - d);
    edges[i].push_back(make_pair(j, weight));
    edges[j].push_back(make_pair(i, weight));
}

int main()
{
    cin >> N;
    
    for (int i = 0; i < N; i++)
    {
        int x, y;
        cin >> x >> y;
        cows[i] = make_pair(x, y);
    }

    sort(cows, cows + N);

    int last[11];
    memset(last, -1, sizeof last);

    for (int i = 0; i < N; i++)
    {
        if (i < N - 1) {
            addEdge(i, i+1);
        }

        for (int y = 0; y <= 10; y++)
        {
            if (last[y] != -1) {
                addEdge(i, last[y]);
            }
        }

        last[cows[i].second] = i;
    }

    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
    bool visited[N];
    memset(visited, false, sizeof visited);

    ll result = 0;
    pq.push(make_pair(0, 0));
    while (!pq.empty())
    {
        auto p = pq.top();
        pq.pop();
        if (visited[p.second]) {
            continue;
        }

        visited[p.second] = true;
        result += p.first;
        for (auto next : edges[p.second])
        {
            pq.push(make_pair(next.second, next.first));
        }
    }

    cout << result << endl;
    
    return 0;
}

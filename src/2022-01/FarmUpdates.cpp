/**
 *      USACO 2022 - 01 - Problem 2 - Farm Updates
 *
 */

#include <bits/stdc++.h>

using namespace std;

void dfs(int farm, int time, int* result, vector<int>* graph) 
{
    if (result[farm] != 0) {
        return;
    }

    result[farm] = time;
    for (int next : graph[farm])
    {
        dfs(next, time, result, graph);
    }
}

int main()
{
    int n, q;
    cin >> n >> q;

    bool isAct[n+1];
    memset(isAct, true, sizeof isAct);

    pair<char, int> queries[q+1];
    pair<int, int> edge[q+1];
    bool inUse[q+1];
    memset(inUse, true, sizeof inUse);

    int count = 1;
    for (int i = 1; i <= q; i++)
    {
        char c;
        int a;
        cin >> c >> a;
        if (c == 'A') {
            int b;
            cin >> b;
            edge[count] = make_pair(a, b);
            count++;
        }
        else if (c == 'R') {
            inUse[a] = false;
        }
        else if (c == 'D') {
            isAct[a] = false;
        }

        queries[i] = make_pair(c, a);
    }

    vector<int> graph[n+1];
    for (int i = 1; i < count; i++)
    {
        if (inUse[i]) {
            int a = edge[i].first;
            int b = edge[i].second;
            graph[a].push_back(b);
            graph[b].push_back(a);            
        }
    }

    int result[n+1];
    memset(result, 0, sizeof result);
    for (int i = 1; i <= n; i++)
    {
        if (isAct[i]) {
            dfs(i, q, result, graph);
        }
    }
    
    for (int i = q; i >= 1; i--)
    {
        if (queries[i].first == 'D') {
            dfs(queries[i].second, i-1, result, graph);
        }
        else if (queries[i].first == 'R') {
            int a = edge[queries[i].second].first;
            int b = edge[queries[i].second].second;
            graph[a].push_back(b);
            graph[b].push_back(a);
            
            if (result[a] != 0 || result[b] != 0) {
                dfs(a, i-1, result, graph);
                dfs(b, i-1, result, graph);
            }
        }
    }

    for (int i = 1; i <= n; i++)
    {
        cout << result[i] << endl;
    }

    return 0;
}

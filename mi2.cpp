#include <iostream>
#include <cstdio>
#include <queue>
#include <algorithm>
#include <cstring>
#pragma comment (linker,"/STACK:1024000000,1024000000")

using namespace std;

namespace FUCKer {

const int INF = 0x3f3f3f3f;
const int maxn = 350;
int n, m, n0, n1;
int res;

struct node {
    int id0, id1, b;
    node(int i0, int i1, int bb) {
        id0 = i0; id1 = i1; b = bb;
    }
};
vector<node> v[30];
int cnt[maxn][maxn];

struct nnode {
    int ok, a, b, id;
}num0[maxn], num1[maxn], num[maxn];

int tol, head[maxn];
struct Edge{
    int to, next, cap, flow, cost;
}edge[maxn*maxn];

int pre[maxn], dis[maxn], vis[maxn];

void addedge(int u, int v, int cap, int cost)
{
    edge[tol].to = v;  edge[tol].cap = cap; edge[tol].cost = cost; edge[tol].flow = 0;
    edge[tol].next = head[u]; head[u] = tol++;

    edge[tol].to = u;  edge[tol].cap = 0; edge[tol].cost = -cost; edge[tol].flow = 0;
    edge[tol].next = head[v]; head[v] = tol++;
}
inline void printG()
{
    for (int i=0;i<=n+1;++i)
    {
        printf("------ Point: %d ------\n",i);
        int cnt=0;
        for (int k=head[i];~k;k=edge[k].next) {
            //++cnt;
            printf("v: %d\t cap: %d\t cost: %d\n",edge[k].to,edge[k].cap,edge[k].cost);
        }
        //printf("%d\n",cnt);
    }
}

int N;
static bool spfa(int s, int t)
{
    queue<int> q;
    for(int i = 0; i < N; ++i) {
        dis[i] = INF;
        vis[i] = false;
        pre[i] = -1;
    }
    dis[s] = 0;
    vis[s] = true;
    q.push(s);
    while(!q.empty()) {
        int u = q.front();
        q.pop();
        vis[u] = false;
        for(int i = head[u]; ~i; i = edge[i].next) {
            int v = edge[i].to;
            if(edge[i].cap > edge[i].flow && dis[v] > dis[u] + edge[i].cost) {
                dis[v] = dis[u] + edge[i].cost;
                pre[v] = i;
                if(!vis[v]) {
                    vis[v] = true;
                    q.push(v);
                }
            }
        }
    }
    if(pre[t] == -1) return false;
    else return true;
}
int flow(int s, int t, int &cost)
{
    int flow = 0;
    cost = 0;
    while(spfa(s, t)) {
        int Min = INF;
        for(int i = pre[t]; ~i; i = pre[edge[i^1].to]) {
            if(Min > edge[i].cap - edge[i].flow) {
                Min = edge[i].cap - edge[i].flow;
            }
        }
        for(int i = pre[t]; ~i; i = pre[edge[i^1].to]) {
            edge[i].flow += Min;
            edge[i^1].flow -= Min;
            cost += edge[i].cost * Min;
        }
        if(cost > res) {
            return flow;
        }
        else
            res = min(res, cost); //!!!

        flow += Min;
     }
     return flow;
}
static void init()
{
    tol = 0;
    memset(head, -1, sizeof(head));
    for(int i = 0; i < 30; ++i) v[i].clear();
    memset(cnt, 0, sizeof(cnt));
}

int main()
{
    freopen("IN3.txt", "r", stdin);
    int T;
    scanf("%d", &T);
    while(T--) {
        int sum = 0;
        n0 = 1, n1 = 1;
        scanf("%d %d", &n, &m);

        init();

        int s = 0, t = n+1;
        int a0, a1, id0, id1;
        for(int i = 1; i <= n; ++i) {
            scanf("%d %d %d", &num[i].ok, &num[i].a, &num[i].b);
            int a = num[i].a, b = num[i].b;
            sum += num[i].b;

            if(num[i].ok == 0) {
                num[i].id = n0;
                num0[n0].ok = num[i].ok; num0[n0].a = a;
                num0[n0].b = b; num0[n0++].id = i;

                addedge(s, i, 1, 0);

                for(int j = 1; j < n1; ++j) {
                    a1 = num1[j].a, id1 = num1[j].id;
                    v[a+a1].push_back(node(i, id1, b+num[id1].b));
                }
            }
            else {
                num[i].id = n1;
                num1[n1].ok = num[i].ok; num1[n1].a = a;
                num1[n1].b = b; num1[n1++].id = i;

                addedge(i, t, 1, 0);

                for(int j = 1; j < n0; ++j) {
                    a0 = num0[j].a, id0 = num0[j].id;
                    v[a+a0].push_back(node(id0, i, b+num[id0].b));
                }
            }
        }

        int a, b, r, id;
        for(int i = 1; i <= m; ++i) {
            scanf("%d %d %d", &a, &b, &r);
            if(r == 0) {
                for(int j = 0; j < v[a].size(); ++j) {
                    cnt[v[a][j].id0][v[a][j].id1] = min(cnt[v[a][j].id0][v[a][j].id1], v[a][j].b-b);
                }
            }
            if(r == 1) {
                scanf("%d", &id);
                if(num[id].ok == 0) {
                    for(int j = 0; j < v[a].size(); ++j) {
                        if(v[a][j].id0 == id) {
                            cnt[v[a][j].id0][v[a][j].id1] = min(cnt[v[a][j].id0][v[a][j].id1], v[a][j].b-b);
                        }
                    }
                }
                else {
                    for(int j = 0; j < v[a].size(); ++j) {
                        if(v[a][j].id1 == id) {
                            cnt[v[a][j].id0][v[a][j].id1] = min(cnt[v[a][j].id0][v[a][j].id1], v[a][j].b-b);
                        }
                    }
                }
            }
            if(r == 2) {
                scanf("%d%d", &id0, &id1);
                if(num[id0].ok == 1) swap(id0, id1);
                cnt[id0][id1] = min(cnt[id0][id1], num[id0].b+num[id1].b-b);
            }
        }

        for(int i = 1; i < n0; ++i) {
            for(int j = 1; j < n1; ++j) {
                id0 = num0[i].id, id1 = num1[j].id;
                if(cnt[id0][id1] < 0) {
                    addedge(id0, id1, 1, cnt[id0][id1]);
                }
            }
        }

        N = n+2;
        int cost;
        res = 0;
        printG();
        flow(s, t, cost);
        printf("%d\n", sum - res);
    }
    return 0;
}

}

int main1()
{
    return FUCKer::main();
}

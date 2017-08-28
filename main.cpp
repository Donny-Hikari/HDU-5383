#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <functional>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <map>
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
#define MEM(_array,val) memset(_array,val,sizeof(_array))
#define MEM0(_array) MEM(_array,0)
#define MEMZ(_array) MEM(_array,0)
#define FORUP(_v,_b,_n) for(int _v=(_b);_v<=(_n);++_v)
#define FORDOWN(_v,_b,_n) for(int _v=(_b);_v>=(_n);--_v)
#define NXTINT(_v) scanf("%d",&(_v))
#define NXTLL(_v) scanf("%lld",&(_v))
#define TCASES() int _T;NXTINT(_T);while (_T--)

const int MAXN=310;
const int MAXM=MAXN*MAXN*2;
int N,M;

struct EDG
{
    int u,v,cap,flow,cost;
} es[MAXM];
int fst[MAXN],nxt[MAXM];
int coe;
inline void mkedg(int u,int v,int cap,int cost)
{
    es[++coe]=EDG{u,v,cap,0,cost};
    nxt[coe]=fst[u];
    fst[u]=coe;
    es[++coe]=EDG{v,u,0,0,-cost};
    nxt[coe]=fst[v];
    fst[v]=coe;
}
inline void init()
{
    coe=1; MEM0(fst);
}
inline void printG()
{
    for (int i=0;i<=N+1;++i)
    {
        printf("------ Point: %d ------\n",i);
//        int cnt=0;
        for (int k=fst[i];k;k=nxt[k]) {
            //++cnt;
            printf("v: %d\t cap: %d\t cost: %d\n",es[k].v,es[k].cap,es[k].cost);
        }
//        printf("%d\n",cnt);
    }
}

const int INF=0x7FFFFFFF;
int S,T;
int d[MAXN]; // distance
int p[MAXN]; // path edge indexes
int a[MAXN]; // max available capability
bool inq[MAXN]; // in queue
bool spfa()
{
    fill(d,d+MAXN,INF);
    MEM0(inq);

    // find current lowest cost path
    queue<int> Q;
    d[S]=0; p[S]=0; a[S]=INF;
    Q.push(S); inq[S]=1;
    while (!Q.empty())
    {
        int u=Q.front(); Q.pop();
        inq[u]=0;
        for(int k=fst[u];k;k=nxt[k])
        {
            EDG& e=es[k];
            if (e.cap>e.flow && d[e.v]>d[u]+e.cost)
            {
                d[e.v]=d[u]+e.cost;
                p[e.v]=k;
                a[e.v]=min(a[u],e.cap-e.flow);
                if (!inq[e.v]) {
                    Q.push(e.v); inq[e.v]=1;
                }
            }
        }
    }
    return d[T]!=INF;
}
int mincost(int s,int t)
{
    int flow=0,cost=0;
    S=s; T=t;
    while (spfa())
    {
        flow+=a[T];
        cost+=d[T]*a[T];
        for (int u=T;u!=s;u=es[p[u]].u) {
            es[p[u]].flow+=a[T];
            es[p[u]^1].flow-=a[T];
        }
    }
    return cost;
}

const int MAXLV=12;
struct MON
{
    int lv,atk;
    int id;
} mon0[MAXN],mon1[MAXN];
int cm0,cm1;
int refe[MAXN],reftp[MAXN];
struct COMBO
{
    int m0,m1;
    int atk;
} combo[MAXLV+1][MAXN*MAXN];
int cocbm[MAXLV+1];
inline void combine(int m0,int m1)
{
    int cblv=mon0[m0].lv+mon1[m1].lv;
    if (cblv>=MAXLV) return;
    combo[cblv][++cocbm[cblv]]=COMBO{m0,m1,mon0[m0].atk+mon1[m1].atk};
}
int G[MAXN][MAXN];
inline void cbedg(int i0,int i1,int atk)
{
    G[i0][i1]=max(G[i0][i1],atk);
}

int main()
{
#ifdef LOCAL
    freopen("IN.txt","r",stdin);
#endif

    int sum;
    TCASES()
    {
        init();
        sum=0;
        MEM0(cocbm);
        cm0=cm1=0;
        scanf("%d%d",&N,&M);
        for(int i=1;i<=N;++i) {
            int tp,lv,atk;
            scanf("%d%d%d",&tp,&lv,&atk);
            sum+=atk;
            if (tp==0)
            {
                mon0[++cm0]=MON{lv,atk,i};
                mkedg(0,i,1,0);
                refe[i]=cm0; reftp[i]=tp;
                for(int j=1;j<=cm1;++j) combine(cm0,j);
            }
            else
            {
                mon1[++cm1]=MON{lv,atk,i};
                mkedg(i,N+1,1,0);
                refe[i]=cm1; reftp[i]=tp;
                for(int j=1;j<=cm0;++j) combine(j,cm1);
            }
        }
        MEM0(G);
//        for(int i=1;i<dip;++i)
//        for(int j=dip;j<=N;++j)
//            mkedg(mon[i].id,mon[j].id,1,0);
        for(int i=1;i<=M;++i)
        {
            int lv,atk,coc,i0,i1;
            scanf("%d%d%d",&lv,&atk,&coc);
            if (coc==2) {
                scanf("%d%d",&i0,&i1);
                if (reftp[i0]==1) swap(i0,i1);
                cbedg(refe[i0],refe[i1],atk);
            } else if (coc==1) {
                scanf("%d",&i0);
                if (reftp[i0]==0) {
                    for(int j=1;j<=cocbm[lv];++j)
                        if (combo[lv][j].m0==i0)
                            cbedg(refe[i0],combo[lv][j].m1,atk);
                } else {
                    for(int j=1;j<=cocbm[lv];++j)
                        if (combo[lv][j].m1==i0)
                            cbedg(combo[lv][j].m0,refe[i0],atk);
                }
            } else {
                for(int j=1;j<=cocbm[lv];++j)
                    cbedg(combo[lv][j].m0,combo[lv][j].m1,atk);
            }
        }
        for (int i=1;i<=cm0;++i)
        for (int j=1;j<=cm1;++j)
        {
            int diff=mon0[i].atk+mon1[j].atk-G[i][j];
            if (diff<0) mkedg(mon0[i].id,mon1[j].id,1,diff);
        }
        //printG();
        printf("%d\n",sum-mincost(0,++N));
    }

    return 0;
}

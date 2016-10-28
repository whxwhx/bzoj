#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#define N 55
#define M 2505
 
using namespace std;
struct edge{
    int from,adj,next;double len;
    edge(){}
    edge(int _from,int _adj,int _next,double _len):from(_from),adj(_adj),next(_next),len(_len){}
} e[M];
int n,g[N],m;
void AddEdge(int u,int v,double w){
    e[++m]=edge(u,v,g[u],w);g[u]=m;
}
 
double in[N];
int prep[N];
int vis[N],stamp;
int bl[N],cnt;
double directed_MST(){
    double ret=0;
    e[0].adj=0;
    for (;;){
        memset(in,127,sizeof(in));
        memset(prep,0,sizeof(prep));
        for (int u=1;u<=n;++u)
            for (int i=g[u];i;i=e[i].next)
                if (e[i].len<in[e[i].adj])
                    in[e[i].adj]=e[i].len,prep[e[i].adj]=u;
        for (int i=1;i<=n;++i) if (prep[i]) ret+=in[i];
        memset(vis,0,sizeof(vis));vis[0]=stamp=1;
        memset(bl,0,sizeof(bl));cnt=0;
        for (int i=1;i<=n;++i)if (!vis[i]){
            int u=i;
            ++stamp;
            for (;!vis[u];u=prep[u]) vis[u]=stamp;
            if (vis[u]==stamp){
                ++cnt;
                for (;!bl[u];u=prep[u]) bl[u]=cnt;
            }
        }
        if (!cnt) return ret;
        for (int i=1;i<=n;++i) if (!bl[i]) bl[i]=++cnt;
        int m0=m;
        memset(g,0,sizeof(g));m=1;
        for (int i=2;i<=m0;++i)
            if (bl[e[i].from]!=bl[e[i].adj])
                AddEdge(bl[e[i].from],bl[e[i].adj],e[i].len-in[e[i].adj]);
        n=cnt;
    }
}
 
int need[N];
double mincost[N];
int main(){
    scanf("%d",&n);++n;
    memset(g,0,sizeof(g));m=1;
    int u,v,m0;double tmp;
    for (int i=1;i<n;++i){
        scanf("%lf%d",&mincost[i],&need[i]);
        if (need[i])
            AddEdge(n,i,mincost[i]);
    }
    scanf("%d",&m0);
    while (m0--){
        scanf("%d%d%lf",&u,&v,&tmp);
        if (need[u]&&need[v]&&u!=v){
            AddEdge(u,v,tmp);
            mincost[v]=min(mincost[v],tmp);
        }
    }
    double sum=0;
    for (int i=1;i<=n;++i)
        if (need[i])
            sum+=mincost[i]*(need[i]-1);
    printf("%.2lf\n",sum+directed_MST());
    return 0;
}
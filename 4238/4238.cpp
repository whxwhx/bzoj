#include <iostream>
#include <cstdio>
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
const int N = 100000 + 10, M = 200000 * 2 + 10;
int n, m, a[M], b[M];
struct edge{
    int to, pre;
}e[M];
int u[N], l = 1;
#define v e[i].to
#define reg(i,a) for(int i=u[a];i;i=e[i].pre)
void ins(int a, int b){
    e[++l] = (edge) {b, u[a]}, u[a] = l;
}
int dep[N], good_cnt = 0, bad_cnt = 0, vis[N], good[N], bad[N];
void dfs(int x, int fa){
    vis[x] = 1;good[x] = bad[x] = 0;
    reg(i,x) if (i ^ fa ^ 1){
        if (!vis[v])
            dep[v] = dep[x] + 1, dfs(v, i), good[x] += good[v], bad[x] += bad[v];
        else if (dep[v] <= dep[x]){
            if ((dep[x] ^ dep[v]) & 1){
                good_cnt++;
                good[x]++, good[v]--;
            }else{
                bad_cnt++;
                bad[x]++, bad[v]--;
            }
        }
    }
}
int t[N];
int main(){
    scanf("%d%d",&n,&m);
    rep(i,1,m) {
        scanf("%d%d",&a[i],&b[i]);
        ins(a[i],b[i]);
        if (a[i] != b[i]) ins(b[i],a[i]);
    }
    rep(i,1,n) if (!vis[i]) dep[i] = 0, dfs(i, 0), t[i] = 1; else t[i] = 0;
    int ans = 0;
    rep(i,1,n) if (!t[i] && !good[i] && bad[i] == bad_cnt) ans++;
    if (bad_cnt == 1) ans++;
    printf("%d\n",ans);
    return 0;
}
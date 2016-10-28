#include <iostream>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i = a; i <= b; i++)
using namespace std;
 
const int N = 100100;
struct edge{
    int to, pre, c, ch;
}e[N * 2];
int u[N], l = 0;
void ins(int a, int b, int c){
    e[++l] = (edge){b, u[a], c, 0}, u[a] = l;
}
#define reg(i,a) for(int i = u[a]; i; i = e[i].pre)
#define v e[i].to
#define ec e[i].c
#define ech e[i].ch
typedef long long LL;
 
struct node{
    int sum, dep, par, ch[20], dis[21], cnt;
    LL ans, a1[20];
}T[N];
 
int rt, sz[N], s[N], sum;
bool vis[N];
#define max(a,b) ((a) > (b) ? (a) : (b))
void getrt(int x, int f){
    sz[x] = 1; s[x] = 0;
    reg(i,x) if (v != f && !vis[v])
        getrt(v, x), sz[x] += sz[v], s[x] = max(s[x], sz[v]);
    s[x] = max(s[x], sum - sz[x]);
    if (s[x] < s[rt]) rt = x;
}
 
void dfs(int x, int f, int dis){
    T[x].dis[++T[x].dep] = dis;
    reg(i,x) if (v != f && !vis[v]) dfs(v, x, dis + ec);
}
 
void work(int x){
    vis[x] = 1;
    dfs(x, 0, 0);
    int cnt = 0;
 
    reg(i,x) if (!vis[v]){
        ech = 1;
 
        sum = sz[v], rt = 0, getrt(v, x);
         
        T[x].ch[cnt++] = rt;
        T[rt].par = x;
         
        work(rt);
    }
    T[x].cnt = cnt;
}
 
#define o T[cur]
#define f T[fa]
void add(int x, int d, LL ans){
    int dis = 0, fa;
    for(int cur = x; cur; cur = fa){
        fa = o.par;
 
        o.sum += d;
        o.ans += ans + 1LL * d * T[x].dis[o.dep];
 
        if (fa)
            rep(i,0,f.cnt - 1) if (f.ch[i] == cur)
                {f.a1[i] += ans + 1LL * d * T[x].dis[f.dep];break;}
    }
}
 
int S;
#define tch T[x].ch[cnt]
#define ta1 T[x].a1[cnt]
LL qry(int x){
    int cnt = 0;
    reg(i,x) if (ech){
        if (T[tch].sum * 2 > S){
            LL s1 = T[x].sum - T[tch].sum, a1 = T[x].ans - ta1 + s1 * ec;
            add(v, s1, a1);
            LL ans = qry(tch);
            add(v, -s1, -a1);
            return ans;
        }
        cnt++;
    }
    return T[x].ans;
}
 
 
int main(){
    int n, Q; scanf("%d%d",&n,&Q);
    rep(i,1,n - 1){
        int a, b, c; scanf("%d%d%d",&a,&b,&c);
        ins(a, b, c), ins(b, a, c); 
    }
     
    s[rt = 0] = sum = n, getrt(1,0);
    int root = rt;
    work(rt);
 
    rep(i,1,Q){
        int a, b; scanf("%d%d",&a,&b);
        S += b;
        add(a, b, 0);
        printf("%lld\n",qry(root));
    }
}
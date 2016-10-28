#include <iostream>
#include <cstdio>
#include <cmath>
#include <set>
#include <map>
#include <queue>
#include <bitset>
#include <vector>
#include <string>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#define Rep(i,a) for(int i = 0; i < a; i++)
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define dep(i,a,b) for(int i = a; i >= b; i--)
#define ab(a) ((a) > 0 ? (a) : -(a))
#define mp(a,b) make_pair(a,b)
#define pb(a) push_back(a)
using namespace std;
typedef long long LL;
typedef unsigned long long uLL;
const int N = 100010, M = 200010;
 
struct edge{
    int to, pre;
}e[N * 2];
int u[N];
int l = 0;
inline void ins(int a, int b){
    e[++l] = (edge){b, u[a]}, u[a] = l;
}
#define reg(i,a) for(int i = u[a]; i; i = e[i].pre)
#define v e[i].to
 
char op[M], s[10];
int a[M], b[M], fa[N], dep[N], g[N][17], pre[N], ed[N], dfs_clock = 0;
inline void dfs(int x){
    pre[x] = ++dfs_clock;
    reg(i,x) if (v != fa[x]) dep[v] = dep[x] + 1, fa[v] = x, dfs(v);
    ed[x] = dfs_clock;
}
 
int n;
void init(){
    rep(i,1,n) if (!pre[i]) fa[i] = dep[i] = 0, dfs(i); 
    rep(i,1,n) g[i][0] = fa[i];
    rep(j,1,16) rep(i,1,n) g[i][j] = g[g[i][j - 1]][j - 1];
}
int cap[N], f[N];
inline int find(int x){
    return f[x] == x ? x : f[x] = find(f[x]);
}
 
struct BIT{
    int s[N];
    inline void add(int x, int d){
        for(;x && x < N;x += (-x) & x) s[x] += d;
    }
    inline int sum(int x){
        int ans = 0;
        for (;x;x -= (-x) & x) ans += s[x];
        return ans;
    }
}sz;
 
int size(int x){
    return sz.sum(ed[x]) - sz.sum(pre[x] - 1) + 1;
}
 
int ans = 0;
#define min(a,b) ((a) < (b) ? (a) : (b))
inline void merge(int a, int b){
    if (fa[a] != b) swap(a, b);
    int rtb = find(b), ca = cap[a], cb = cap[rtb]; ans ^= ca ^ cb;
    f[a] = rtb;
    int sza = size(a);
    sz.add(pre[b], sza), sz.add(pre[fa[rtb]], -sza);
     
    int sum = size(rtb);
    a = ca, b = cb;

    dep(i,16,0) if (g[a][i] && (size(g[a][i]) << 1) < sum && dep[g[a][i]] >= dep[rtb]) a = g[a][i];
    dep(i,16,0) if (g[b][i] && (size(g[b][i]) << 1) < sum && dep[g[b][i]] >= dep[rtb]) b = g[b][i];
    if ((size(a) << 1) < sum) {if (a != rtb) a = fa[a]; else a = 0;}
    if ((size(b) << 1) < sum) {if (b != rtb) b = fa[b]; else b = 0;}
    if (dep[a] < dep[b]) swap(a,b);  
    if ((size(a) << 1) == sum && fa[a]) a = min(a,fa[a]);
    ans ^= a, cap[rtb] = a;
}
int main(){
    int m; scanf("%d%d",&n,&m);
    rep(i,1,m){
        scanf("%s",s);
        op[i] = s[0];
        if (op[i] == 'A') scanf("%d%d",&a[i],&b[i]), ins(a[i], b[i]), ins(b[i], a[i]);
        else if (op[i] == 'Q') scanf("%d",&a[i]);
    }
    rep(i,1,n) ans ^= i, cap[i] = i;
    init();
    rep(i,1,n) f[i] = i;
    rep(i,1,m) {
        if (op[i] == 'A') merge(a[i], b[i]);
        else if (op[i] == 'Q') printf("%d\n",cap[find(a[i])]);
        else if (op[i] == 'X') printf("%d\n",ans);
    }
    return 0;
}
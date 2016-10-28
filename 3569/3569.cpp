#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define dep(i,a,b) for(int i = a; i >= b; i--)
using namespace std;
const int M = 500000 + 10, N = 100010;
 
struct edge{
    int to, pre, num;
}e[M * 2];
int u[N], l = 0;
void ins(int a, int b, int num){
    e[++l] = (edge){b, u[a], num}, u[a] = l;
}
#define reg(i,a) for(int i = u[a];i; i = e[i].pre)
#define v e[i].to
#define nm e[i].num
 
typedef unsigned long long uLL;
int a[M], b[M], fa[N], pre[N], dfs_clock = 0;
uLL r[M];
uLL d[M];
 
void dfs(int x, int f){
    pre[x] = ++dfs_clock;
    reg(i,x) if (!pre[v]) fa[v] = x, dfs(v, x); else{
        if (pre[v] < pre[x] && v != f){
            while (!r[nm]) r[nm] = (uLL) rand() * (uLL) rand() * (uLL) rand();
            d[x]  ^= r[nm], d[v] ^= r[nm];
        } 
    }
}
 
void dfs2(int x){
    reg(i,x) if (fa[v] == x) dfs2(v), d[x] ^= d[v];
}
void dfs3(int x){
    reg(i,x) if (fa[v] == x) dfs3(v), r[nm] = d[v];
}
 
const int K = 16;
int c[K];
 
uLL qa[K], h[64];
bool check(int k){
    int cnt = 0;
    dep(i,63,0){
        rep(j,1,k) if (qa[j] >> i & 1){
            cnt++;
            h[i] = qa[j];
            rep(t,1,k) if (qa[t] >> i & 1) qa[t] ^= h[i];
            break;
        }
    }
    if (cnt == k) return true; else return false;
}
 
int main(){
    srand(233);
    int n, m; scanf("%d%d",&n,&m);
    rep(i,1,m){
        scanf("%d%d",&a[i],&b[i]);
        ins(a[i], b[i], i), ins(b[i], a[i], i);
    }
    dfs(1, 0);
    dfs2(1);
    dfs3(1);
    int q; scanf("%d",&q);
    int cnt = 0;
    rep(i,1,q){
        int k; scanf("%d",&k);
        rep(i,1,k) scanf("%d",&c[i]), c[i] ^= cnt;
        rep(i,1,k) qa[i] = r[c[i]];
        if (check(k)) printf("Connected\n"), cnt++; else printf("Disconnected\n");
    }
    return 0;
}
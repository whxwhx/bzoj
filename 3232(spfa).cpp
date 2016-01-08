#include <iostream>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define dep(i,a,b) for(int i = a; i >= b; i--)
using namespace std;
const int N = 55, inf = 1000 * N * N;
int a[N][N], b[N][N], c[N][N], s[N][N];
#define id(x,y) (((x) - 1) * (m + 1) + (y))
int n, m; 
struct edge{
    int to, pre;
    double c;
}e[N * N * 20];
int l = 0, u[N * N];
#define reg(i,a) for(int i = u[a]; i; i = e[i].pre)
#define v e[i].to
#define ec  e[i].c
void ins(int a, int b, double c){
    e[++l] = (edge){b, u[a], c}, u[a] = l;
}

int from[N * N], q[N * N];
double d[N * N];
bool inq[N * N];
bool check(double t){
    l = 0; rep(i,1,id(n + 1, m + 1)) u[i] = 0, d[i] = inf, inq[i] = 0, from[i] = 0;
    rep(i,1,n)
        rep(j,1,m + 1)
            ins(id(i, j), id(i + 1, j), c[i][j] * t), ins(id(i + 1, j), id(i, j), c[i][j] * t);
    rep(i,1,n + 1)
        rep(j,1,m)
            ins(id(i, j), id(i, j + 1), b[i][j] * t - s[i][j]), ins(id(i, j + 1), id(i, j), b[i][j] * t + s[i][j]);
    d[1] = 0;
    int l = 0, r = 1; q[0] = 1;
    int T = id(n + 1, m + 1);
    while (l != r){
        int x = q[l++]; if (l == T + 1) l = 0; 
        inq[x] = 0;
        reg(i,x) if (d[x] + ec < d[v]){
            d[v] = d[x] + ec;
            if (from[x] + 1 > from[v]) from[v] = from[x] + 1;
            if (from[v] >= T) return true;
            if (!inq[v]) q[r++] = v, r = (r == T + 1) ? 0 : r, inq[v] = 1;
        }
    }
    return false;
}
const double eps = 0.0001;
void solve(){
    int t = 0;
    double l = 0, r = 100 * n * m;
    while (l + eps < r){
        t++; if (t >= 100) break;
        double mid = (l + r) / 2;
        if (check(mid)) l = mid; else r = mid;
    }
    printf("%.3lf\n",(l + r) / 2);
}
int main(){
    scanf("%d%d",&n,&m);
    rep(i,1,n) rep(j,1,m) scanf("%d",&a[i][j]);
    rep(i,1,n + 1) rep(j,1,m) scanf("%d",&b[i][j]);
    rep(i,1,n) rep(j,1,m + 1) scanf("%d",&c[i][j]);
 
    rep(i,1,n) rep(j,1,m) s[i][j] = a[i][j];
    rep(j,1,m) dep(i,n - 1,1) s[i][j] += s[i + 1][j];
     
    solve();
    return 0;
}

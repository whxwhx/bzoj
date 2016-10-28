#include <iostream>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i = a; i <= b; i++)
typedef long long LL;
using namespace std;
const int N = 200010;
struct point{ int x, y; }t[N];
struct op{int t,l,r; point a;}q[N], ch[N][2];
struct edge{point to; int pre;}e[N * 30];
int u[N * 4], l = 0;
void ins(int a, point b){e[++l] = (edge){b, u[a]}, u[a] = l;}
#define v e[i].to
#define reg(i,a) for(int i = u[a]; i; i = e[i].pre)
inline bool operator < (const point &a, const point &b){ return a.x < b.x || (a.x == b.x && a.y < b.y); }
inline bool operator < (const op &a, const op &b){ return b.a < a.a; }
void add(int x, int l, int r, int a, int b, point d){
    if (a <= l && r <= b) ins(x, d);
    else {
        int mid = (l + r) >> 1, lc = x << 1, rc = (x << 1) + 1;
        if (a <= mid) add(lc, l, mid, a, b, d);
        if (b >  mid) add(rc, mid + 1, r, a, b, d);
    }
}
LL ans[N];bool vis[N];
point operator - (const point &a, const point &b) {return (point){a.x - b.x, a.y - b.y};}
inline LL cross(point a, point b){return 1LL * a.x * b.y - 1LL * a.y * b.x;}
#define max(a,b) ((a) > (b) ? (a) : (b))
void dfs(int x, int l, int r, int a, int b){
    if (a > b) return;
    int tl = 0;         
    reg(i,x) {
        while (tl && t[tl].x == v.x) tl--;
        while (tl >= 2 && cross(t[tl] - t[tl - 1], v - t[tl]) >= 0) tl--;
        t[++tl] = v;
    }
    if (tl){
        int j = 1;
        rep(i,a,b){
            while (j < tl && cross((point){q[i].a.y, -q[i].a.x}, t[j + 1] - t[j]) >= 0) j++;
            LL k = 1LL * t[j].x * q[i].a.x + 1LL * t[j].y * q[i].a.y;
            ans[q[i].l] = max(ans[q[i].l], k);
        }
    }
    if (l == r) return;
    int mid = (l + r) >> 1, lc = x << 1, rc = lc + 1, cl[2] = {0,0};
    rep(i,a,b){ int d = (q[i].l > mid); ch[++cl[d]][d] = q[i]; }
    int t0 = a - 1, t1; rep(i,1,cl[0]) q[++t0] = ch[i][0]; t1 = t0; rep(i,1,cl[1]) q[++t0] = ch[i][1];
    dfs(lc, l, mid, a, t1); dfs(rc, mid + 1, r, t1 + 1, b);
}
bool cmp(const op &a, const op &b){return cross(a.a, b.a) < 0;}
int id[N], m = 0;
inline int read(){
    int x = 0, f = 1;char c = getchar();
    while (c < '0' || c > '9') {if (c == '-') f = -1;c = getchar();}
    while (c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
    return x * f;
}
int main(){
    int n; scanf("%d",&n);
    rep(i,1,n){
        q[i].t = read(); int k;
        if (q[i].t == 1) id[++m] = i;
        if (q[i].t != 2) q[i].a.x = read(),q[i].a.y = read(), q[i].l = i, q[i].r = n;
        else k = read(), q[id[k]].r = i;
    }
    sort(q + 1, q + n + 1);
    rep(i,1,n) if (q[i].t == 1) add(1,1,n,q[i].l,q[i].r,q[i].a);
    int l = 0;
    rep(i,1,n) if (q[i].t == 3) l++, q[l] = q[i], vis[q[i].l] = 1;
    sort(q + 1, q + l + 1, cmp);
    dfs(1,1,n,1,l);
    rep(i,1,n) if (vis[i]) printf("%lld\n",ans[i]);
    return 0;
}
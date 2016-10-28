#include <iostream>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i = a; i <= b; i++)
using namespace std;
const int N = 210, M = 10010;
struct edge{
    int u, v, a, b, t;
}e[M];
bool operator < (const edge &a, const edge &b){
    return a.t < b.t;
}
struct node{
    int x, y;
};
int f[N];

int find(int x){
    return x == f[x] ? x : f[x] = find(f[x]);
}

node operator + (const node &a, const node &b){
    return (node){a.x + b.x, a.y + b.y};
}

bool operator < (const node &a, const node &b){
    return 1LL * a.x * a.y < 1LL * b.x * b.y || (1LL * a.x * a.y == 1LL * b.x * b.y && a.x < b.x);
}

int n, m; 
node ans;

node mst(){
    sort(e + 1, e + m + 1);
    rep(i,1,n) f[i] = i;
    node tmp = (node){0, 0};
    int cnt = 0;
    rep(i,1,m) {
        int fa = find(e[i].u), fb = find(e[i].v);
        if (fa != fb){
            tmp = tmp + (node){e[i].a, e[i].b};
            f[fa] = fb;
            cnt++; if (cnt == n - 1) break;
        }
    }
    return tmp;
}

void quickhull(node a, node b){
    rep(i,1,m) e[i].t = -((a.x - b.x) * e[i].b + (b.y - a.y) * e[i].a);
    node t = mst();
    if (1LL * (b.x - t.x) * (a.y - t.y) - 1LL * (a.x - t.x) * (b.y - t.y)  <= 0) return;
    if (t < ans) ans = t;
	quickhull(a, t), quickhull(t, b);
}

int main(){
    scanf("%d%d",&n,&m);
    rep(i,1,m) scanf("%d%d%d%d",&e[i].u,&e[i].v,&e[i].a,&e[i].b), e[i].u++, e[i].v++;
     
    rep(i,1,m) e[i].t = e[i].a;
    node t1 = mst();
    ans = t1;
    rep(i,1,m) e[i].t = e[i].b;
    node t2 = mst();
    if (t2 < ans) ans = t2;
    quickhull(t1, t2);
 
    printf("%d %d\n",ans.x,ans.y);
    return 0;
}
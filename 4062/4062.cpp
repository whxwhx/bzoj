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
#define max(a,b) ((a) > (b) ? (a) : (b))
#define Rep(i,a) for(int i = 0; i < (a); i++)
#define rep(i,a,b) for(int i = (a); i <= (b); i++) //(a)!
#define dep(i,a,b) for(int i = (a); i >= (b); i--)
#define ab(a) ((a) > 0 ? (a) : -(a))
#define mp(a,b) make_pair((a),(b))
#define pb(a) push_back(a)
using namespace std;
typedef long long LL;
typedef unsigned long long uLL;
  
const int N = 200010;
  
inline int rd() {
    char c = getchar();
    while (!isdigit(c)) c = getchar() ; int x = c - '0';
    while (isdigit(c = getchar())) x = x * 10 + c - '0';
    return x;
}

struct node{
    int c, x, y, num;
}d[N], d1[N], d2[N], d3[N];
int a[N], b[N];
int al, bl;
  
inline int find(int x, int al, int *a){
    int l = 1, r = al + 1;
    while (l + 1 < r){
        int mid = (l + r) >> 1;
        if (a[mid] <= x) l = mid; else r = mid;
    }
    return l;
}
  
inline bool cmp(const node &a, const node &b){
    return a.c < b.c || (a.c == b.c && a.x < b.x) || (a.c == b.c && a.x == b.x && a.y < b.y);
}
 
struct qry{
    int l, r, h;
}q[N * 3];
int ql;
 
int l[N], r[N], n, k, fa[N];
 
inline bool cmp1(const node &a, const node &b){
    return a.c < b.c || (a.c == b.c && a.y > b.y) || (a.c == b.c && a.y == b.y && a.x < b.x);
}
 
inline bool cmp2(const node &a, const node &b){
    return a.c < b.c || (a.c == b.c && a.y > b.y) || (a.c == b.c && a.y == b.y && a.x > b.x);
}
 
inline bool cmp3(const node &a, const node &b){
    return a.c < b.c || (a.c == b.c && a.x < b.x) || (a.c == b.c && a.x == b.x && a.y > b.y);
}
 
inline int find(int x){
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}
 
int lft[N], rgt[N];
void calc(int k){
    if (d[ l[k] ].x > 1) q[++ql] = (qry){1, d[ l[k] ].x - 1, bl};
    rep(i,l[k],r[k] - 1) 
        if (d[i].x + 1 <= d[i + 1].x - 1) q[++ql] = (qry){d[i].x + 1, d[i + 1].x - 1, bl};//r[k] - 1！永远不要让数组下标超出你处理的范围！
    if (d[ r[k] ].x < al) q[++ql] = (qry){d[ r[k] ].x + 1, al, bl};
 
    //find left
    rep(i,l[k],r[k]) fa[i] = i;
    fa[l[k] - 1] = l[k] - 1;
    rep(i,l[k],r[k]){
        int x = d1[i].num;
        fa[x] = x - 1;
        int t = find(x);
        if (t < l[k]) lft[x] = 1; else lft[x] = d[t].x + 1;
    }
    //find right
    rep(i,l[k],r[k]) fa[i] = i;
    fa[r[k] + 1] = r[k] + 1;
    rep(i,l[k],r[k]){
        int x = d2[i].num;
        fa[x] = x + 1;
        int t = find(x);
        if (t > r[k]) rgt[d3[x].num] = al; else rgt[d3[x].num] = d3[t].x - 1;
    }
 
    //add_into_qry
    rep(i,l[k],r[k]) if (lft[i] <= rgt[i]) q[++ql] = (qry){lft[i], rgt[i], d[i].y - 1};
}
 
inline bool cmpq(const qry &a, const qry &b){
    return a.h < b.h;
}
 
inline bool cmp4(const node &a, const node &b){
    return a.y < b.y;
}
int ans;
 
int s[N];
inline void add(int x, int d){
    for(;x <= al;x += (-x) & x) s[x] += d;
}
inline int sum(int x){
    int ans = 0;
    for(;x; x -= (-x) & x) ans += s[x];
    return ans;
}
 
void get_ans(){
    rep(i,1,al) s[i] = 0;
    sort(q + 1, q + ql + 1, cmpq);
    sort(d + 1, d + n + 1, cmp4);
    int j = 1;
    rep(i,1,ql){
        while (j <= n && d[j].y <= q[i].h) add(d[j++].x, 1);
        ans = max(ans, sum(q[i].r) - sum(q[i].l - 1));
    }
}
 
void work(){
	n = rd(), k = rd();
    al = bl = 0;
    rep(i,1,n) d[i].x = rd(), d[i].y = rd(), d[i].c = rd(), a[++al] = d[i].x, b[++bl] = d[i].y;   
    sort(a + 1, a + al + 1), sort(b + 1, b + bl + 1);
    al = unique(a + 1, a + al + 1) - a - 1;
    bl = unique(b + 1, b + bl + 1) - b - 1;
    rep(i,1,n) d[i].x = find(d[i].x, al, a), d[i].y = find(d[i].y, bl, b);
    sort(d + 1, d + n + 1, cmp);
     
    rep(i,1,k) l[i] = r[i] = 0;
    rep(i,1,n){
        if (!l[d[i].c]) l[d[i].c] = i;
        r[d[i].c] = i;
    }
 
    rep(i,1,n) d1[i] = d3[i] = d[i], d1[i].num = d3[i].num = i;
    sort(d1 + 1, d1 + n + 1, cmp1);
 
    sort(d3 + 1, d3 + n + 1, cmp3);
    rep(i,1,n) d2[i] = d3[i], d2[i].num = i;
    sort(d2 + 1, d2 + n + 1, cmp2);
 
    ans = 0;
    ql = 0;
    rep(i,1,k) calc(i);
    get_ans();
    printf("%d\n",ans);
}
int main(){
    int T; scanf("%d",&T);
    while (T--) work();
}
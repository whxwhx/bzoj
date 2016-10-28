 
#include <iostream>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i = a, _b = b; i <= _b; i++)
#define dep(i,a,b) for(int i = a, _b = b; i >= _b; i--)
using namespace std;
const int N = 100010;
int a[N], c[N], sa[N], x[N], y[N], b[N];
int n, m; 
int find(int x){
    int l = 1, r = n + 1;
    while (l + 1 < r){ int mid = (l + r) >> 1; if (b[mid] <= x) l = mid; else r = mid; }
    return l;
}
void calc(int *x, int *y){
    rep(i,1,m) c[i] = 0;
    rep(i,1,n) c[x[y[i]]]++;
    rep(i,2,m) c[i] += c[i - 1];
    dep(i,n,1) sa[c[x[y[i]]]--] = y[i];
}
 
void buildsa(int *x, int *y){
    rep(i,1,n) x[i] = a[i], y[i] = i;
    calc(x, y); 
    for(int k = 1; k <= n; k <<= 1){
        int p = 0;
        rep(i,n - k + 1, n) y[++p] = i;
        rep(i,1,n) if (sa[i] - k > 0) y[++p] = sa[i] - k;
        calc(x, y); swap(x, y);
        p = 1; x[sa[1]] = 1;
        rep(i,2,n) 
            x[sa[i]] = (y[sa[i]] == y[sa[i - 1]] && y[sa[i] + k] == y[sa[i - 1] + k]) ? p : ++p;
        m = p;
        if (m >= n) break;
    }
}
 
int rk[N], h[N], mn[N][18], bin[1 << 18];
void geth(){
    rep(i,1,n) rk[sa[i]] = i;
    int k = 0;
    rep(i,1,n){
        if (k) k--;
        if (rk[i] - 1){
            int j = sa[rk[i] - 1];
            while (a[i + k] == a[j + k]) k++;
            h[rk[i]] = k;
        }
    }
    rep(i,1,n) mn[i][0] = h[i];
    rep(j,1,17) rep(i,1,n) if (i + (1 << j) - 1 <= n) mn[i][j] = min(mn[i][j - 1], mn[i + (1 << (j - 1))][j - 1]);
    rep(j,0,16) rep(i,(1 << j), (1 << (j + 1)) - 1) bin[i] = j;
}
 
int lcp(int a, int b){
    int l = b - a; a++;
    int t = min(mn[a][bin[l]], mn[b - ( 1 << bin[l] ) + 1][bin[l]]);
    return t;
}
 
typedef long long LL;
LL ans[N];
 
int pre[N], nxt[N];
void del(int x){
    pre[nxt[x]] = pre[x];
    nxt[pre[x]] = nxt[x];
}
 
int main(){
    scanf("%d",&n); m = n;
    rep(i,1,n) scanf("%d",&a[i]), b[i] = a[i];
    rep(i,1,n/2) swap(a[i], a[n - i + 1]);
    sort(b + 1, b + n + 1);
    rep(i,1,n) a[i] = find(a[i]);
    //rep(i,1,n) cout <<a[i]<<' '; cout <<endl;
    rep(i,1,n) pre[i] = i - 1, nxt[i] = i + 1; nxt[n] = 0;
    buildsa(x, y);
    geth();
    //rep(i,1,n) cout <<sa[i]<<' '; cout <<endl;
    //rep(i,1,n) cout <<h[i]<<' '; cout <<endl;
    ///cout <<lcp(1, 5)<<endl;
    ans[1] = n - sa[1] + 1; rep(i,2,n) ans[1] += n - sa[i] + 1 - h[i];
    rep(i,1,n - 1){
        int x = rk[i];
        ans[i + 1] = ans[i]; int h = 0;
        if (pre[x]) h = max(h, lcp(pre[x], x));
        if (nxt[x]) h = max(h, lcp(x, nxt[x]));
        ans[i + 1] -= n -sa[x] + 1 - h;
        del(x);
    }
    dep(i,n,1) printf("%lld\n",ans[i]);
    return 0;
}
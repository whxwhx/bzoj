#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#define max(a,b) ((a)>(b)?(a):(b))
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
const int N = 100015, M = 350;
typedef long long LL;
LL f[M][M];
int a[N], bel[N], cnt[M][N], b[N], n, q, l, L[M], R[M], c[N];
int find(int x){
    int l = 1, r = n + 1;//[l,r)
    while (l + 1 < r){
        int mid = (l + r) >> 1;
        if (b[mid] <= x) l = mid; else r = mid;
    }
    return l;
}
int main(){
    scanf("%d%d",&n,&q);
    rep(i,1,n) scanf("%d",&a[i]), b[i] = a[i];
    sort(b + 1, b + n + 1);
    rep(i,1,n) a[i] = find(a[i]);
 
    int len = 511, m;
    rep(i,1,n) {
        bel[i] = (i - 1) / len + 1;
        if (i % len == 1) L[bel[i]] = i;
        if (i % len == 0) R[bel[i]] = i;
    }
    m = bel[n], R[m] = n;
 
 
    rep(i,1,n) cnt[bel[i]][a[i]]++;
    rep(i,2,m) rep(j,1,n) cnt[i][j] += cnt[i - 1][j];
     
    rep(i,1,m)
        rep(j,i,m){
            f[i][j] = f[i][j - 1];
            rep(k,L[j],R[j]){
                int t = a[k];
                LL t1 = (long long)(cnt[j][t] - cnt[i - 1][t]) * b[t];
                f[i][j] = max(t1, f[i][j]); 
            }
        }
 
 
    rep(i,1,q){
        int l, r; scanf("%d%d",&l,&r);
        int l1 = bel[l], r1 = bel[r];
        LL ans = 0;
        if (l1 == r1){
            rep(i,l,r) {
                int t = a[i];
                c[t]++, ans = max(1LL * c[t] * b[t], ans);
            }
            printf("%lld\n",ans);
            rep(i,l,r) c[a[i]]--;
        }else{
            r1--;
            ans = f[l1 + 1][r1];
            rep(i,l,R[l1]) {
                int t = a[i];
                c[t]++, ans = max(1LL * (c[t] + cnt[r1][t] - cnt[l1][t]) * b[t], ans);
            }
            rep(i,R[r1] + 1, r){
                int t = a[i];
                c[t]++, ans = max(1LL * (c[t] + cnt[r1][t] - cnt[l1][t]) * b[t], ans);              
            }
            printf("%lld\n",ans);
            rep(i,l,R[l1]) c[a[i]]--;
            rep(i,R[r1] + 1,r) c[a[i]]--;
        }
    }
    return 0;
}
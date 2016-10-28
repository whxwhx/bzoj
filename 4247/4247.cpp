#include <iostream>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define dep(i,a,b) for(int i=a;i>=b;i--)
using namespace std;
const int N = 2000 + 10, INF = 2000000010;
int a[N], b[N], f[N][N], q[N], Q;
int main(){
    int n; scanf("%d",&n);
    int l = 0, Q = 0;
    rep(i,1,n){
        int x, y;
        scanf("%d%d",&x,&y); if (x == 0) q[++Q] = y; else a[++l] = x, b[l] = y;
    }
    sort(q + 1, q + Q + 1);
    f[0][0] = -INF, f[0][1] = 0; rep(i,2,n) f[0][i] = -INF;
    rep(i,1,l){
        rep(j,0,n) f[i][j] = f[i - 1][j];
        rep(j,1,n)
            if (f[i - 1][j] != -INF){
                int k = j - 1 + a[i]; if (k > n) k = n;
                f[i][k] = max(f[i - 1][j] + b[i], f[i][k]);
            }
    }
    int j = Q, aj = 0, ans = 0;
    rep(i,0,n){
        if (j && i && q[j] > 0) aj += q[j], j--;
        if (f[l][i] != -INF) ans = max(ans, aj + f[l][i]);
    }
    printf("%d\n",ans);
}
#include <iostream>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define dep(i,a,b) for(int i = a; i >= b; i--)
using namespace std;
typedef unsigned int ui;
typedef __int128 LL;
const int N = 55;
ui a[N], t0[N], t1[N];
int l0, l1;
LL f[N][2];
int t[100];
void print(LL ans){
    if (ans == 0) {cout <<0<<endl;return;}
    int l = 0;
    while (ans > 0) t[++l] = ans % 10, ans /= 10;
    dep(i,l,1) cout <<t[i];
    cout <<endl;
}
int main(){
    int n; scanf("%d",&n);
    rep(i,1,n) scanf("%ud",&a[i]);
    LL ans = 0;
    dep(i,31,0){
        ui t = ui(1) << i;
        l0 = l1 = 0;
        rep(i,1,n) if (a[i] & t) t1[++l1] = a[i] ^ t; else t0[++l0] = a[i];
        int l = 0;
        rep(i,1,l1) a[++l] = t1[i];
        rep(i,1,l0) a[++l] = t0[i];
        f[n + 1][0] = 1, f[n + 1][1] = 0;
        dep(i, n, l1 + 1)
            f[i][0] = f[i + 1][0] * (a[i] + 1), 
            f[i][1] = f[i + 1][1] * (a[i] + 1);
        dep(i, l1, 1)
            f[i][0] = f[i + 1][0] * t + f[i + 1][1] * (a[i] + 1),
            f[i][1] = f[i + 1][1] * t + f[i + 1][0] * (a[i] + 1);
        LL tmp2 = 1;
        rep(i,1,l1){
            ans += f[i + 1][(i - 1) & 1] * tmp2;
            tmp2 *= (a[i] + 1);
        }
        if (l1 & 1) break; else if (i == 0) ans++;
    }
    ans--;
    print(ans);
}
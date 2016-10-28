#include <iostream>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i = a; i <= b; i++)
using namespace std;
const int N = 100010;
typedef long long LL;
int pre[N], nex[N];
LL a[N], ga[N];
typedef long long LL;
LL gcd(LL a, LL b){
    return b ? gcd(b, a % b) : a;
}
void del(int x){
    if (pre[x]) nex[pre[x]] = nex[x];
    if (nex[x]) pre[nex[x]] = pre[x];
}
#define max(a,b) ((a) > (b) ? (a) : (b))
void work(){
    int n; scanf("%d",&n);
    rep(i,1,n) scanf("%lld",&a[i]);
    LL ans = a[1];
    pre[1] = nex[1] = 0, ga[1] = a[1];
    int top = 1;
    rep(i,2,n){
        nex[top] = i, pre[i] = top, nex[i] = 0, ga[i] = a[i];
        LL g = (ga[1] = gcd(ga[1], a[i]));
        top = 1;
        ans = max(ans, i * g);
        for(int j = nex[1]; j; j = nex[j]){
            ga[j] = gcd(ga[j], a[i]);
            if (g == ga[j]) del(j); else {g = ga[j]; top = j;}
            ans = max(ans, (i - j + 1) * g);
        }
    }
    printf("%lld\n",ans);
}
int main(){
    int t; scanf("%d",&t);
    while (t--) work();
}
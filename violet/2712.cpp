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
#define Rep(i,a) for(int i = 0; i < a; i++)
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define dep(i,a,b) for(int i = a; i >= b; i--)
#define ab(a) ((a) > 0 ? (a) : -(a))
#define mp(a,b) make_pair(a,b)
#define pb(a) push_back(a)
using namespace std;
typedef long long LL;
typedef unsigned long long uLL;
int n;
LL x, y, r;
void solve(LL a, LL b, LL c, LL d){
    if ((a / b + 1) * d < c) x = a / b + 1, y = 1;
    else if (a >= b){
        LL t = a / b;
        solve(a - b * t, b, c - d * t, d);
        x += y * t;
    }else{
        if (a == 0) y = 1, x = d / c + 1;
        else solve(d, c, b, a);
        swap(x, y);
    }
}
LL gcd(LL a, LL b){
    if (a == 0) return b;
    return b ? gcd(b, a % b) : a;
}
void work(){
    r *= 10;
    LL a, b, c, d;
    a = (LL)r - 5, c = (LL)r + 5;if (a < 0) a = 0;
    b = 1; rep(i,1,n + 1) b *= 10;
    d = b;
    LL t = gcd(a,b);
    a /= t, b /= t;
    solve(a,b,c,d);
    printf("%lld\n",y < b ? y : b);
}
int main(){
    while (scanf("%d 0.%lld",&n,&r) == 2) work();
}
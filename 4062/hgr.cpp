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
using namespace std;
typedef long long LL;
typedef unsigned long long uLL;
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define per(i,a,b) for(int i=a;i>=b;i--)
#define pii pair<int , int>
#define mp make_pair
#define maxn 200007
#define maxm 4000007

inline int rd() {
    char c = getchar();
    while (!isdigit(c)) c = getchar() ; int x = c - '0';
    while (isdigit(c = getchar())) x = x * 10 + c - '0';
    return x;
}

inline void upmax(int&a , int b) { if (a < b) a = b ; }

struct Pic {
    int x , y , c;
    Pic() {}
    Pic(int x , int y , int c):x(x) , y(y) , c(c) { }
}pic[maxn];

bool cmp(const Pic a , const Pic b) {
    return (a.y < b.y) || (a.y == b.y && a.x < b.x);
}

typedef int arr[maxn];
typedef int seg[maxm];
typedef set<int>::iterator iter_set;

arr h;
int tot , n , K;

namespace BITS {
    arr sum;
    int n;

    #define lowbit(x) (x & (-x))

    void add(int x , int v) {
        for (;x <= n;x += lowbit(x))
            sum[x] += v;
    }

    int get(int x) {
        int ret = 0;
        for (;x;x -= lowbit(x))
            ret += sum[x];
        return ret;
    }

    void init(int _n) {
        memset(sum , 0 , sizeof sum);
        n = _n;
    }
}

set<int> S[maxn];

void input() {
    n = rd() , K = rd() , tot = 0;
    BITS::init(n);
    rep (i , 1 , n) {
        int x = rd() , y = rd() , c = rd();
        h[i] = x;
        pic[i] = Pic(x , y , c);
    }
    sort(h + 1 , h + 1 + n);
    tot = unique(h + 1 , h + 1 + n) - h - 1;
    rep (i , 1 , n) pic[i].x = lower_bound(h + 1 , h + 1 + tot , pic[i].x) - h;
    sort(pic + 1 , pic + 1 + n , cmp);
}

void solve() {
    int ans = 0;
    rep (i , 1 , K) S[i].clear();
    rep (i , 1 , K) S[i].insert(0) , S[i].insert(tot + 1);
    for (int i = 1 , j;i <= n;) {
        for (j = i;j <= n && pic[i].y == pic[j].y;j ++) {
            iter_set it = S[pic[j].c].lower_bound(pic[j].x);
            int r = *it , l = *(-- it);
            upmax(ans , BITS::get(r - 1) - BITS::get(l));
        }
        for (;i < j;i ++) {
            BITS::add(pic[i].x , 1);
            S[pic[i].c].insert(pic[i].x);
        }
    }
    rep (i , 1 , K) {
        int pre = 0;
        for (iter_set it = ++ S[i].begin();it != S[i].end();it ++) {
            int t = *it;
            upmax(ans , BITS::get(t - 1) - BITS::get(pre));
            pre = t;
        }
    }
    printf("%d\n" , ans);
}

int main() {
    per (T , rd() , 1) {
        input();
        solve();
    }
    return 0;
}
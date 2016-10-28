/*
    注意！！位运算和位运算之间的优先级居然是不一样的！
    (x ^ y) & 1是需要打括号的！！！

    假设S表示被控制
    控制一个点:A_ij代价
    没被选择:B_ij代价
    选择 == 被控制/四联通邻居都被控制
    还是和文理分科一样新建一个点表示被选择
    周围的点有一个没被控制(T集合)，那么这个点就在T集合
    所以这个点连向周围的点inf边
    这个点和(i,j)点之间的关系：
    1.都在S集合 ： 贡献0
    2.都在T集合 :  贡献B_i,j
    3.一个在S一个在T :贡献0
    这里关系仍然是对称的，所以我们假设：
    S连到它们都是a
    它们连到T都是b
    它们之间的边都是c
    那么
    2a = 0
    2b = B_i,j
    a + b + c = 0
    这带来的问题是c < 0

    注意由于这个点是我们新建出来的点，
    肯定满足和原来点的c是二分图
    经典的翻转源汇
    翻转之后：
    1.在相同集合:贡献0
    2.在不同集合:贡献0/B_i,j （取决于i^j&1）
    不妨假设(i^j)&1 == 1
    也就是对(i,j)而言的话在S表示被控制。。那么对(i,j)'而言的话，在T表示被选择
    如果不妨设中间边为e，然后a_1 a_2 b_1 b_2.....
    1点是(i,j)

    都在S或者T：
    a_1 + a_2 = 0
    b_1 + b_2 = 0
    1在S，2在T：
    b_1 + a_2 + e = 0
    1在T，2在S：
    a_1 + b_2 + e = B
    
    这个方程中，我们再让两个方向的e相等就比较麻烦。。我们把他们拆开，这样才比较好处理

    都在S或者T：
    a_1 + a_2 = 0
    b_1 + b_2 = 0
    1在S，2在T：
    b_1 + a_2 + e_12 = 0
    1在T，2在S：
    a_1 + b_2 + e_21= B

    这样子的话直接让e_21等于B，别的都为0就好了。。（所以才要拆开）


    但是再注意到如果要这个点翻转源汇，
    我们没法限制它
    『周围的点有一个在T集的时候，它就在S集，否则在T集』
    那个否则在T集的限制。。
    如果我们要限制两个点一定在不同集合。。其实是不好做的。。（相同直接inf双向边即可）
    如果看做二元关系，
    一定不同可以相当于不同的代价是-inf，
    也就是说中间那条e边代价是负inf
    显然最后还是只能反转源汇，然后转化为一定相同

    这里我们就再利用原网格图四联通也是二分图，把黑格反转源汇
    这样就可以限制了。。。
*/
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
#define Rep(i,a) for(int i = 0; i < (a); i++)
#define rep(i,a,b) for(int i = (a); i <= (b); i++)//(a)!
#define dep(i,a,b) for(int i = (a); i >= (b); i--)
#define ab(a) ((a) > 0 ? (a) : -(a))
#define mp(a,b) make_pair((a),(b))
#define pb(a) push_back(a)
using namespace std;
typedef long long LL;
typedef unsigned long long uLL;
const int N = 55 * 55 * 2, M = N * 7, inf = 1000000000, dx[5] = {0, 0, 0, 1, -1}, dy[5] = {0, -1, 1, 0, 0};

int S, T;
struct edge{
    int to, pre, w;
}e[M * 2];
int cur[N], u[N], l = 1;//l = 1!
#define ew e[i].w
#define v e[i].to
#define reg(i,a) for(int i = u[a]; i; i = e[i].pre)
#define ceg(i,a) for(int i = cur[a]; i; i = e[i].pre)
void ins(int a, int b, int w){
    e[++l] = (edge){b, u[a], w}, u[a] = l;
}
void insert(int a, int b, int w){//used insert to add an edge instead of using ins!
    ins(a, b, w), ins(b, a, 0);
}
int q[N], h[N];
bool bfs(){
    rep(i,S,T) h[i] = -1;
    int l = 0, r = 1; q[h[S] = 0] = S;
    while (l < r){
        int x = q[l++];
        reg(i,x) if (ew && h[v] == -1) h[v] = h[x] + 1, q[r++] = v;
    }
    return h[T] != -1;
}
int dfs(int x, int f){
    if (x == T || f == 0) return f;
    int used = 0, w;
    ceg(i,x)if (ew && h[v] == h[x] + 1){
        w = min(ew, f - used), w = dfs(v, w);
        ew -= w; if (ew) cur[x] = i;
        e[i^1].w += w;
        used += w; if (used == f) break;
    }
    if (!used) h[x] = -1;
    return used;
}
int dinic(){
    int ans = 0;
    while (bfs()){
        rep(i,S,T) cur[i] = u[i];
        ans += dfs(S, inf);
    }
    return ans;
}

#define id(i,j) ((i - 1) * m + j)
int main(){
    int n, m, ans = 0; scanf("%d%d",&n,&m);
    S = 0, T = id(n,m) * 2 + 1;
    rep(i,1,n) rep(j,1,m){
        int a; scanf("%d",&a);
        if ((i ^ j) & 1)
            insert(id(i,j), T, a);
        else 
            insert(S, id(i,j), a);
    }
    int l = id(n,m);
    rep(i,1,n) rep(j,1,m){
        l++;
        int b; scanf("%d",&b);
        ans += b;
        rep(k,1,4){
            int x = i + dx[k], y = j + dy[k];
            if (0 < x && x <= n && 0 < y && y <= m){
                if ((x ^ y) & 1)
                    insert(l, id(x,y), inf);
                else 
                    insert(id(x,y), l, inf);
            }
        }
        if ((i ^ j) & 1)
            insert(l, id(i,j), b);
        else 
            insert(id(i,j), l, b);
    }
    ans -= dinic();
    printf("%d\n",ans);
    return 0;
}
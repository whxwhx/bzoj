#include <cstdio>
#include <cstring>
#include <cmath>
#define ms(a,b) memset(a,b,sizeof(a))
#define FOR(i,j,k) for(int i=j;i<=k;++i)
const int N = 128, M = 10001;
void getmin(double &a, double b) { if (a > b) a = b; }
int u[M], v[M], id[N], vis[N], nav[N], count[N], fa[N];
double x[N], y[N], w[M], in[N], minc[N];
double edmonds(int rt, int n, int m) {
    int i, a, b, cnt;
    double ans = 0;
    while (1) {
        FOR(i,1,n) in[i] = 1e18;
        FOR(i,1,m) if (w[i] < in[v[i]] && u[i] != v[i])
            in[v[i]] = w[i], fa[v[i]] = u[i];
        FOR(i,1,n) if (i != rt && in[i] == 1e18) return -1;
        ms(id, 0); ms(vis, 0); in[rt] = 0; cnt = 0;
        FOR(i,1,n) {
            ans += in[i];
            for (b = i; vis[b] != i && !id[b] && b != rt; b = fa[b]) vis[b] = i;
            if (b != rt && !id[b]) {
                ++cnt;
                for (a = fa[b]; a != b; a = fa[a]) id[a] = cnt;
                id[b] = cnt;
            }
        }
        if (!cnt) break;
        FOR(i,1,n) if (!id[i]) id[i] = ++cnt;
        FOR(i,1,m) {
            int x = v[i];
            u[i] = id[u[i]]; v[i] = id[v[i]];
            if (u[i] != v[i]) w[i] -= in[x];
        }
        n = cnt; rt = id[rt];
    }
    return ans;
}


int main() {
    int n, i, k, a, b, m = 0, graph_node; double c;
    scanf("%d", &n);
    FOR(i,1,n) {
        scanf("%lf%d", &c, &count[i]);
        if (count[i]) ++m, v[m] = m; nav[i] = m; minc[m] = w[m] = c;
    }
    graph_node = m + 1; FOR(i,1,m) u[i] = graph_node;
    scanf("%d", &k);
    FOR(i,1,k) {
        scanf("%d%d%lf", &a, &b, &c);
        if (count[a] && count[b]) {
            u[++m] = nav[a], v[m] = nav[b];
            getmin(minc[v[m]], w[m] = c);
        }
    }
    double ans = edmonds(graph_node, graph_node, m);
    FOR(i,1,n) if(count[i] > 1) ans += (count[i] - 1) * minc[nav[i]];
    printf("%.2lf\n", ans);

    return 0;
}
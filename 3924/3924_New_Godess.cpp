#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
#define maxn 100100
typedef long long ll;
typedef pair<ll,ll> ii;
typedef pair<ll,ii> iii;
#define fi first
#define se second
#define pb push_back
struct edges{int to,next,dist;}edge[maxn*2];
int l,next[maxn];
inline void addedge(int x,int y,int z) {
    edge[++l]=(edges){y,next[x],z};next[x]=l;
    edge[++l]=(edges){x,next[y],z};next[y]=l;
}
bool done[maxn];
int s[maxn],f[maxn],root,size;

void dfs(int u,int fa){//getrt
    s[u]=1;f[u]=0;
    int v=0;
    for (int i=next[u];i;i=edge[i].next) {
        if (done[v=edge[i].to] || v==fa) continue;
        dfs(v,u);
        s[u]+=s[v];
        f[u]=max(f[u],s[v]);
    }
    f[u]=max(f[u],size-s[u]);
    if (f[u]<f[root]) root=u;
}

vector<ii> pre[maxn];

void getdist(int u,int fa,int tar,int dist) {
    pre[u].pb(ii(tar,dist));
    s[u]=1;int v=0;
    for (int i=next[u];i;i=edge[i].next) {
        if (done[v=edge[i].to]||v==fa) continue;
        getdist(v,u,tar,dist+edge[i].dist);
        s[u]+=s[v];
    }
}

vector<iii> ch[maxn];

void work(int u){
    done[u]=1;
    int v=0;
    pre[u].pb(ii(u,0));
    for (int i=next[u];i;i=edge[i].next) {
        if (done[v=edge[i].to]) continue;
        getdist(v,0,u,edge[i].dist);
        f[0]=size=s[v];
        dfs(v,root=0);
        ch[u].pb(iii(root,ii(v,edge[i].dist)));
        work(root);
    }
}

ll cnt[maxn],sum[maxn];

vector<ll> sumdist[maxn];
inline void update(int x,ll y,ll z){
    for (int i=0;i<pre[x].size();i++) {
        int u=pre[x][i].fi;
        cnt[u]+=y;sum[u]+=z+y*pre[x][i].se;
        if (i!=pre[x].size()-1) {
            int j=0;
            for (;j<ch[u].size();j++) 
                if (ch[u][j].fi==pre[x][i+1].fi) sumdist[u][j]+=z+y*pre[x][i].se;
        }
    }
}
int realroot;
vector<iii> record;
inline ll query(){
    int x=realroot;
    int mx=0;
    record.clear();
    while (x){
        mx=0;
        for (int i=1;i<ch[x].size();i++) 
            if (cnt[ch[x][mx].fi]<cnt[ch[x][i].fi]) mx=i;

        if (ch[x].size()==0||cnt[ch[x][mx].fi]*2<=cnt[x]) {
            ll ans=sum[x];
            for (int i=0;i<record.size();i++) 
                update(record[i].fi,record[i].se.fi,record[i].se.se);
            return ans;
        }
        
        int v=ch[x][mx].fi;
        record.pb(iii(ch[x][mx].se.fi,ii(-(cnt[x]-cnt[v]),
                -(sum[x]-sumdist[x][mx]+(cnt[x]-cnt[v])*ch[x][mx].se.se))));
        update(ch[x][mx].se.fi,cnt[x]-cnt[v],
                sum[x]-sumdist[x][mx]+(cnt[x]-cnt[v])*ch[x][mx].se.se);
        x=v;
    }
}
int main(){
    int n,Q;
    scanf("%d%d",&n,&Q);
    for (int i=1;i<n;i++) {
        int x,y,z;
        scanf("%d%d%d",&x,&y,&z);
        addedge(x,y,z);
    }
    f[0]=size=n;
    dfs(1,root=0);
    realroot=root;
    work(root);
    for (int i=1;i<=n;i++) sumdist[i]=vector<ll>(ch[i].size(),0);
    while (Q--) {
        int x,y;
        scanf("%d%d",&x,&y);
        update(x,y,0);
        printf("%lld\n",query());
    }
    return 0;
}
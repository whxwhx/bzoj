#include <iostream>
#include <cstdio>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;

const int N = 502;
int k, n, m, a[N][N], dx[4], dy[4];

typedef pair<int, int> node;
#define mp(a,b) make_pair(a,b)

node rbt[10];

void init(){	
	dx[0] = 0, dy[0] = -1;
	dx[1] = 1, dy[1] = 0;
	dx[2] = 0, dy[2] = 1;
	dx[3] = -1,dy[3] = 0;
	scanf("%d%d%d",&k,&m,&n);
	rep(i,1,n)
		rep(j,1,m){
			char c = getchar();
			while (c != 'x' && c != 'A' && c != '.' && c != 'C' && (c <= '0' || c > '9')) c = getchar();
			if (c == 'x')
				a[i][j] = 2;
			else if (c == 'A')
				a[i][j] = -1;
			else if (c == 'C')
				a[i][j] = 1;
			else
				a[i][j] = 0;
			if (c > '0' && c <= '9') rbt[c - '0'] = mp(i,j);
		}
	a[0][0] = a[0][m + 1] = a[n + 1][0] = a[n + 1][m + 1] = 2;
	rep(i,1,n) a[i][0] = a[i][m + 1] = 2;
	rep(i,1,m) a[0][i] = a[n + 1][i] = 2;
}


node f[N][N][4];
bool inst[N][N][4];

node dfs(int i, int j, int k){
	if (a[i][j] == 2) return mp(-1, -1);
	if (f[i][j][k] != mp(0, 0)) return f[i][j][k];
	if (inst[i][j][k]) return f[i][j][k] = mp(-1, -1);
	inst[i][j][k] = 1;
	int K = (k + a[i][j] + 4) % 4;
	int I = i + dy[K], J = j + dx[K];
	if (a[I][J] == 2) f[i][j][k] = mp(i, j);
	else f[i][j][k] = dfs(I, J, K);
	inst[i][j][k] = 0;
	return f[i][j][k];
}

struct pos{
	int l, r, i, j;
}q1[N * N], q2[N * N];
int F[10][10][N][N], l1, r1, l2, r2;

bool cmp(const pos &a, const pos &b){
	return F[a.l][a.r][a.i][a.j] < F[b.l][b.r][b.i][b.j];
}

int main(){
	init();
	rep(i,1,n) rep(j,1,m) rep(k,0,3) f[i][j][k] = mp(0, 0);
	rep(i,1,n) rep(j,1,m) rep(k,0,3) inst[i][j][k] = 0;
	rep(i,1,n) rep(j,1,m) rep(k,0,3) f[i][j][k] = dfs(i,j,k);//, cout <<i<<' '<<j<<' '<<k<<' '<<f[i][j][k].first<<' '<<f[i][j][k].second<<endl;

	rep(i,1,n) rep(j,1,m) rep(k1,1,k) rep(k2,k1,k) F[k1][k2][i][j] = -1;
	
	rep(i,1,k) 
		F[i][i][rbt[i].first][rbt[i].second] = 0;

	rep(len,0,k - 1){
		rep(l,1,k - len){
			int r = l + len;			
			rep(t, l, r - 1){
				rep(i,1,n)
					rep(j,1,m) if (F[l][t][i][j] != -1 && F[t + 1][r][i][j] != -1){
						if (F[l][r][i][j] == -1) F[l][r][i][j] = F[l][t][i][j] + F[t + 1][r][i][j];
					 	else F[l][r][i][j] = min(F[l][r][i][j], F[l][t][i][j] + F[t + 1][r][i][j]);
					}
			}

			l1 = r1 = 0;
			rep(i,1,n) rep(j,1,m) if (F[l][r][i][j] != -1) q1[r1++] = (pos){l, r, i, j};
			sort(q1, q1 + r1, cmp);

			l2 = r2 = 0;
			while (l2 != r2 || l1 != r1){
				pos x;
				if (l2 == r2) x = q1[l1++];
				else if (l1 == r1) x = q2[l2++];
				else if (cmp(q1[l1], q2[l2])) x = q1[l1++]; else x = q2[l2++];
				rep(t, 0, 3) if (f[x.i][x.j][t] != mp(-1, -1) && f[x.i][x.j][t] != mp(x.i, x.j) && f[x.i][x.j][t] != mp(0,0)){
					node T = f[x.i][x.j][t];
					if (F[l][r][T.first][T.second] == -1 || F[l][r][x.i][x.j] + 1 < F[l][r][T.first][T.second]){
						F[l][r][T.first][T.second] = F[l][r][x.i][x.j] + 1;
						q2[r2++] = (pos){l, r, T.first, T.second};
					}
				}
			}
		}
	}

	int ans = 0x7fffffff;
	rep(i,1,n)
		rep(j,1,m)
			if (F[1][k][i][j] != -1) ans = min(ans, F[1][k][i][j]);	
	if (ans == 0x7fffffff) printf("-1\n"); else printf("%d\n",ans);
}
const int N = 10010, M = 1010;
const double eps = 
namespace simplex{
	double a[N][M]; int n, m, id[N];
	void pivot(int r, int c){
		swap(id[r + n], id[c]); double f = -a[r][c];
		a[r][c] = -1.0; rep(j,0,n) a[r][i] /= f;
		rep(i,0,m) if (i != r) { double t = a[i][c]; a[i][c] = 0; rep(j,0,n) a[i][j] += t * a[r][j]; }
	}
	void solve(){
		rep(i,1,n) id[i] = i;
		while (1){
			int i = 0, j = 0; double w = -eps;
		}
	}
}
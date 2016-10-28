#include <iostream>
#include <cstdio>
#include <algorithm>
#include <set>
#define rep(i,a,b) for(int i = a; i <= b; i++)
using namespace std;
const int N = 310, M = N * N;
int a[M], b[N], n, m, cnt = 0, c[N];

multiset<int> s;
typedef multiset<int>::iterator sit;

int d[N][N];

void check(int x, int y, int z, int id){
	b[1] = x, b[2] = y, b[3] = z;
	s.clear();
	rep(i,3,m) if (i != id) s.insert(a[i]);
	rep(i,4,n){
		sit it = s.begin(); b[i] = (*it) - b[1];
		if (b[i] < b[i - 1]) return;
		rep(j,1,i - 1){
			int k = b[i] + b[j];
			sit t = s.find(k);
			if (t == s.end()) return; else s.erase(t);
		}
	}
	cnt++;
	rep(i,1,n) d[cnt][i] = b[i];
}

int main(){
	scanf("%d",&n); m = n * (n - 1) / 2;
	rep(i,1,m) scanf("%d",&a[i]); sort(a + 1, a + m + 1);
	rep(i,3,n) if ((a[i] != a[i - 1] || i == 3) && (a[1] + a[2] + a[i]) % 2 == 0){
		int x = (a[1] + a[2] + a[i]) / 2 - a[i], y = a[1] - x, z = a[2] - x;
		if (x <= y && y <= z) check(x, y, z, i);
	}
	cout <<cnt<<endl;
	rep(i,1,cnt) { rep(j,1,n) cout <<d[i][j]<<' '; cout <<endl; }
	return 0;
}
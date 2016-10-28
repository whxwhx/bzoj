#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
const int N2 = 20000 + 10, D2 = 100 + 10, N3 = 100000 + 10, D3 = 30 + 10;
int n, d, k, a2[N2][D2], a3[N3][D3], T[N3], C[D2 * D2], AC[N3], FT[N3];
#define A2(i,j) a2[i][j]//n*d
#define B2(i,j) a2[j][i]//d*n
#define A3(i,j) a3[i][j]//n*d
#define B3(i,j) a3[j][i]//d*n
void findans2(int i){
	rep(j,1,n) if (j != i){
		int sum = 0;
		rep(k,1,d) sum ^= A2(i,k) & B2(k,j);
		if (sum == 0){
			if (i > j) swap(i,j);
			printf("%d %d\n",i, j);
			return;
		}
	}
}
void findans3(int i){
	rep(j,1,n) if (i != j){
		int sum = 0;
		rep(k,1,d) sum += A3(i,k) * B3(k,j);
		sum %= 3;
		if (sum == 0){
			if (i > j) swap(i,j);
			printf("%d %d\n",i,j);
			return;
		}
	}
}
int id[D3][D3];
typedef pair<int, int> node;
node pos[D3 * D3];
#define mp(a,b) make_pair(a,b)
#define x first
#define y second 
#define A(i,j) (A3(i, pos[j].x) * A3(i, pos[j].y)) 
#define B(i,j) (B3(pos[i].x, j) * B3(pos[i].y, j))

bool check2(){
	//rep(i,1,n) T[i] = rand() & 1;//n*1
	//calc B * T = C //d*1
	rep(i,1,d){
		C[i] = 0;
		rep(j,1,n) C[i] ^= B2(i,j) & T[j];
	}
	//calc A * C = AC //n*1
	rep(i,1,n){
		AC[i] = 0;
		rep(j,1,d) AC[i] ^= A2(i,j) & C[j];
	}
	//calc F * T = FT //n*1
	int sum = 0;
	rep(i,1,n) sum ^= T[i];
	rep(i,1,n){
		int ag = 0;
		rep(j,1,d) ag ^= A2(i,j) & B2(j,i);
		FT[i] = (sum + (2 - T[i]) + ag * T[i]) & 1;
	}
	//cmp
	rep(i,1,n) 
		printf("%d %d\n",FT[i],AC[i]);
	return true;
}
bool check3(){
	//calc AC  //in fact (AB_{i}{j} ^ 2) * T
	rep(i,1,d * d){
		C[i] = 0;
		rep(j,1,n)
			C[i] += B(i,j) * T[j];
		C[i] %= 3;
	}
	rep(i,1,n){
		AC[i] = 0;
		rep(j,1,d * d)
			AC[i] += A(i,j) * C[j];
		AC[i] %= 3;
	}
	//calc FT
	int sum = 0;
	rep(i,1,n) sum += T[i];
	sum %= 3;
	rep(i,1,n){
		int ag = 0;
		rep(j,1,d) ag += A3(i,j) * B3(j,i);
		ag %= 3;
		ag = ag * ag % 3;
		FT[i] = (sum + (3 - T[i]) + ag * T[i]) % 3;
	}
	//cmp
	rep(i,1,n) 
		printf("%d %d\n",FT[i],AC[i]);
	return true;
}
void work2(){
	rep(i,1,n) rep(j,1,d) scanf("%d",&a2[i][j]), a2[i][j] = a2[i][j] & 1;
	check2();
}

void init(){
	int l = 0;
	rep(i,1,d) rep(j,1,d) id[i][j] = ++l, pos[l] = mp(i,j);
}
void work3(){
	rep(i,1,n) rep(j,1,d) scanf("%d",&a3[i][j]), a3[i][j] = a3[i][j] % 3;
	init();check3();
}
int main(){
	scanf("%d%d%d",&n,&d,&k);
	rep(i,1,n) scanf("%d",&T[i]);
	if (k == 2)  work2(); else work3();
}
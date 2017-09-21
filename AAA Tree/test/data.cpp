#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<ctime>
#define rep(i, l, r) for(int i = l; i <= r; ++i)
using namespace std; 
const int MAXN = 50;
int main(){
	freopen("a.in","w",stdout);
	srand(time(NULL));
	int n = 1000, m = 5000;
	//n为点数，m为操作数
	printf("%d %d\n", n, m);
	rep(i, 2, n)
		printf("%d %d\n", i, rand() % (i - 1) + 1);
	rep(i, 1, n)
		printf("%d\n", rand() % MAXN);
	rep(i, 1, m){
		int opt = rand() % 7 + 1;
		if(opt == 1){
			printf("1 %d %d %d\n", rand() % n + 1,  rand() % n + 1, rand() % MAXN);
		}
		else if(opt == 2){
			printf("2 %d %d\n", rand() % n + 1, rand() % n + 1);
		}
		else if(opt == 3){
			printf("3 %d\n", rand() % n + 1);
		}
		else if(opt == 4){
			printf("4 %d\n", rand() % n + 1);
		}
		else if(opt == 5)
		{
			printf("5 %d %d\n", rand() % n + 1,rand() % MAXN);
		}
		else if(opt == 6)
		{
			printf("6 %d %d %d\n", rand() % n + 1,  rand() % n + 1, rand() % MAXN);
		}
		else if(opt == 7)
		{
			printf("7 %d %d\n", rand() % n + 1, rand() % MAXN);
		}
	}
	return 0;
}

#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<ctime>
#define rep(i, l, r) for(int i = l; i <= r; ++i)
using namespace std; 
const int MAXN = 200;
int main(){
	freopen("sone1.in","w",stdout);
	srand(time(NULL));
	int n = 1000, m = 5000;
	//n为点数，m为操作数
	printf("%d %d\n", n, m);
	rep(i, 2, n)
		printf("%d %d\n", i, rand() % (i - 1) + 1);
	rep(i, 1, n)
		printf("%d\n", rand() % MAXN);
	printf("%d\n",rand() % n + 1);
	rep(i, 1, m){
		int opt = rand() % 12;
		if(opt == 0){
			printf("0 %d %d\n",rand() % n + 1, rand() % MAXN);	
		}
		else if(opt == 1){
			printf("1 %d\n", rand() % n + 1);
		}
		else if(opt == 2){
			printf("2 %d %d %d\n", rand() % n + 1, rand() % n + 1, rand() % MAXN);
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
			printf("7 %d %d\n", rand() % n + 1, rand() % n + 1);
		}
		else if(opt == 8)
		{
			printf("8 %d %d\n", rand() % n + 1, rand() % n + 1);
		}
		else if(opt == 9)
		{
			printf("9 %d %d\n", rand() % n + 1, rand() % n + 1);
		}else if(opt == 10)
		{
			printf("10 %d %d\n", rand() % n + 1, rand() % n + 1);
		}else if(opt == 11)
		{
			printf("11 %d\n", rand() % n + 1);
		}
	}
	return 0;
}

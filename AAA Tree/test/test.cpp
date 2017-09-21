#include<iostream>
#include<cstdio>
#include<algorithm>
#include "AAA_tree.hpp"
struct T
{
	int x;
	T():x(0){}
	T(int x):x(x){}
};
T operator +(const T &a, const T &b)
{
	return T(a.x + b.x);
}
T operator &(const T &a, const T &b)
{
	return T(a.x + b.x);
}
T operator *(const int &a, const T &b)
{
	return T(a * b.x);
}
int main()
{
	freopen("a.in","r",stdin);
	freopen("test.out","w",stdout);
	int n, m, x, y,root;
	scanf("%d%d", &n,&m);
	sjtu::AAA_tree<T> tree(n);
	for (int i = 1; i < n; i ++)
	{
		scanf("%d %d", &x, &y);
		tree.link(x, y);
		//printf("link(%d %d)\n", x, y);
	}
	tree.make_root(1);
	for(int i=1;i<=n;i++)
	{
		int x;
		scanf("%d",&x);
		tree.cover_path(i,i,T(x));
	}
	for(int i=1;i<=m;i++)
	{
		int type,u,v,x;
		scanf("%d",&type);
		if(type == 1)
		{
			scanf("%d%d%d",&u,&v,&x);
			tree.cover_path(u,v,T(x));
		}
		if(type == 2)
		{
			scanf("%d%d",&u,&v);
			T ans = tree.ask_path(u,v);
			printf("%d\n",ans.x);
		}
		if(type == 3)
		{
			scanf("%d",&u);
			T ans = tree.ask_subtree(u);
			printf("%d\n",ans.x);
		}
		if(type == 4)
		{
			scanf("%d",&u);
			tree.make_root(u);
		}
		if(type == 5)
		{
			scanf("%d%d",&u,&x);
			tree.cover_subtree(u,x);
		}
		if(type == 6)
		{
			scanf("%d%d%d",&u,&v,&x);
			tree.add_path(u,v,T(x));
		}
		if(type == 7)
		{
			scanf("%d%d",&u,&x);
			tree.add_subtree(u,T(x));
		}
	}
	return 0;
}

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <cmath>
#include <algorithm>
#define next nxt
using namespace std;

const int maxn = 5e5;

int e[maxn], next[maxn], g[maxn];
int tot = 1;
int w[maxn];
int idy, ans = 0;
int n, m, sum = 0;
int f[maxn], stk[maxn];
int top = 0;

bool vis[maxn];
int q[maxn];
void add(int u, int v)
{
	e[tot] = v; next[tot] = g[u]; g[u] = tot ++;
	e[tot] = u; next[tot] = g[v]; g[v] = tot ++;
}

void dfs(int x, int fa, int sum)
{
	if (x == idy) ans = sum;
	for (int i = g[x]; i; i = next[i])
	{
		if (e[i] == fa) continue;
		dfs(e[i], x, sum + w[e[i]]);
	}
}

void change(int x, int fa, int c)
{
	stk[++ top] = x;
	if (x == idy)
	{
		for (int i = 1; i <= top; i ++)
			w[stk[i]] += c;
		return ;
	}
	for (int i = g[x]; i; i = next[i])
	{
		if (e[i] == fa) continue;
		change(e[i], x, c);
	}
	-- top;
}


void change2(int x, int fa, int c)
{
	stk[++ top] = x;
	if (x == idy)
	{
		for (int i = 1; i <= top; i ++)
			w[stk[i]] = c;
		return ;
	}
	for (int i = g[x]; i; i = next[i])
	{
		if (e[i] == fa) continue;
		change2(e[i], x, c);
	}
	-- top;
}

void bfs(int st)
{
	int h = 0, t = 1;
	for (int i = 1; i <= n; i ++) vis[i] = false;
	q[t] = st; vis[st] = true; f[st] = 0;
	while (h < t)
	{
		int k = q[++ h];
		for (int i = g[k]; i; i = next[i])
		{
			if (vis[e[i]]) continue;
			vis[e[i]] = true;
			f[e[i]] = k;
			q[++ t] = e[i];
		}
	}
}

void dfs(int x, int fa)
{
	sum += w[x];
	for (int i = g[x]; i; i = next[i])
	{
		if (e[i] == fa) continue;
		dfs(e[i], x);
	}
}

void dfs2(int x, int fa)
{
	w[x] = idy;
	for (int i = g[x]; i; i = next[i])
	{
		if (e[i] == fa) continue;
		dfs2(e[i], x);
	}
}
void dfs3(int x, int fa)
{
	w[x] += idy;
	for (int i = g[x]; i; i = next[i])
	{
		if (e[i] == fa) continue;
		dfs3(e[i], x);
	}
}
int main( )
{
	int x, y, type, z;
	freopen("a.in", "r", stdin);
	freopen("ans.out", "w", stdout);
	scanf("%d %d", &n, &m);
	for (int i = 1; i < n; i ++)
	{
		scanf("%d %d", &x, &y);
		add(x, y);
	}
	for (int i = 1; i <= n; i ++) scanf("%d", &w[i]);
	bfs(1);
	for (int i = 1; i <= m; i ++)
	{
		scanf("%d", &type);
		if (type == 1)
		{
			scanf("%d %d %d", &x, &y, &z);
			idy = y; top = 0;
			change2(x, 0, z);
		}
		else if (type == 2)
		{
			scanf("%d %d", &x, &y);
			idy = y;
			dfs(x, 0, w[x]);
			printf("%d\n", ans);
		}
		else if (type == 3)
		{
			scanf("%d", &x);
			sum = 0;
			dfs(x, f[x]);
			printf("%d\n", sum);
		}
		else if (type == 4)
		{
			scanf("%d", &x);
			bfs(x);
		}
		else if (type == 5)
		{
			scanf("%d %d", &x, &y);
			idy = y;
			dfs2(x, f[x]);
		}
		else if (type == 6)
		{
			scanf("%d %d %d", &x, &y, &z);
			idy = y; top = 0;
			change(x, 0, z);
		}
		else if (type == 7)
		{
			scanf("%d %d", &x, &y);
			idy = y;
			dfs3(x, f[x]);
		}
	}
	return 0;
}

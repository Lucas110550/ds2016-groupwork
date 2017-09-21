#include<iostream>
#include<cstdio>
#include<algorithm>
#include<set>
#include<queue>
#include<cstring>
#include "strict_fib_heap.hpp"
#include "priority_queue.hpp"
typedef long long LL;
const int MOD = 1e9+7;
std::set<int> ss;
int get_rand()
{
	int tmp = (LL)rand() * (LL)rand() % MOD;
	while (ss.find(tmp) != ss.end()) tmp = (LL)rand() * (LL)rand() % MOD;
	return tmp;
}
class T{
public:
	int data;
	T(int x):data(x){}	
};
struct cmp{
	bool operator ()(const T &a,const T &b)const{return a.data < b.data;} 	
};
void test_advance()
{
	printf("test_advence           : ");
	sjtu::strict_fib_heap<T,cmp> q;
	sjtu::priority_queue<T,cmp> standed;
	int num = 10000;
	ss.clear();
	for(int i=1;i<=num;i++)
	{
		int tmp = get_rand();
		ss.insert(tmp);
		q.push(T(tmp));
		standed.push(T(tmp));
		T t(q.top());
		if(t.data!=(standed.top()).data) puts("ERROR");
		if(i % 10 == 0)
		{
			if(q.size()!=standed.size()) puts("ERROR");
			if(q.empty()!=standed.empty()) puts("ERROR");
			ss.erase(t.data);
			q.pop();
			standed.pop();
		}
	}
	while (!q.empty())
	{
		T t(q.top());
		if(t.data!=(standed.top()).data) puts("ERROR");
		ss.erase(t.data);
		q.pop();
		standed.pop();
	}
	puts("ACCEPT!");
}
void test_int()
{
	printf("test_int               : ");
	sjtu::strict_fib_heap<int> q;
	std::priority_queue<int> standed;
	int num = 10000;
	ss.clear();
	for(int i=1;i<=num;i++)
	{
		int tmp = get_rand();
		ss.insert(tmp);
		q.push(tmp);
		standed.push(tmp);
		int t=q.top();
		if(t!=standed.top()) puts("ERROR");
		if(i % 10 == 0)
		{
			if(q.size()!=standed.size()) puts("ERROR");
			if(q.empty()!=standed.empty()) puts("ERROR");
			ss.erase(t);
			q.pop();
			standed.pop();
		}
	}
	while (!q.empty())
	{
		int t=q.top();
		if(t!=standed.top()) puts("ERROR");
		ss.erase(t);
		q.pop();
		standed.pop();
	}
	puts("ACCEPT!");
}
void test_merge()
{
	printf("test_merge             : ");
	ss.clear();
	sjtu::strict_fib_heap<int> q,p;
	std::priority_queue<int> standed;
	int num = 3000;
	for(int i=1;i<=num;i++)
	{
		int tmp = get_rand();
		ss.insert(tmp);
		q.push(tmp);
		standed.push(tmp);
	}
	for(int i=1;i<=num;i++)
	{
		int tmp = get_rand();
		ss.insert(tmp);
		p.push(tmp);
		standed.push(tmp);
	}
	q.merge(p);
	while (!q.empty())
	{
		int t=q.top();
		if(t!=standed.top()) puts("ERROR");
		ss.erase(t);
		q.pop();
		standed.pop();
	}
	puts("ACCEPT!");
}
void test_copy_construction()
{
	printf("test_copy_construction : ");
	sjtu::strict_fib_heap<int> q;
	ss.clear();
	std::priority_queue<int> standed;
	int num = 4000;
	for(int i=1;i<=num;i++)
	{
		int tmp = get_rand();
		ss.insert(tmp);
		q.push(tmp);
		standed.push(tmp);
	}
	sjtu::strict_fib_heap<int> p(q);
	for(int i=1;i<=num;i++)
	{
		int tmp = get_rand();
		ss.insert(tmp);
		p.push(tmp);
		standed.push(tmp);
		int t = p.top();
		if(t!=standed.top()) puts("ERROR");
		if(i % 10 == 0)
		{
			if(p.size()!=standed.size()) puts("ERROR");
			if(p.empty()!=standed.empty()) puts("ERROR");
			ss.erase(t);
			p.pop();
			standed.pop();
		}
	}
	while (!p.empty())
	{
		int t = p.top();
		if(t!=standed.top()) puts("ERROR");
		ss.erase(t);
		p.pop();
		standed.pop();
	}
	puts("ACCEPT!");
}
void test_evaluation()
{
	printf("test_evaluation        : ");
	sjtu::strict_fib_heap<int> q;
	ss.clear();
	std::priority_queue<int> standed;
	int num = 4000;
	for(int i=1;i<=num;i++)
	{
		int tmp = get_rand();
		ss.insert(tmp);
		q.push(tmp);
		standed.push(tmp);
	}
	sjtu::strict_fib_heap<int> p;
	p.push(1);
	p.push(100000000);
	p=q;
	p=p=p=p=p;
	for(int i=1;i<=num;i++)
	{
		int tmp = get_rand();
		ss.insert(tmp);
		p.push(tmp);
		standed.push(tmp);
		int t = p.top();
		if(t!=standed.top()) puts("ERROR");
		if(i % 10 == 0)
		{
			if(p.size()!=standed.size()) puts("ERROR");
			if(p.empty()!=standed.empty()) puts("ERROR");
			ss.erase(t);
			p.pop();
			standed.pop();
		}
	}
	while (!p.empty())
	{
		int t = p.top();
		if(t!=standed.top()) puts("ERROR");
		ss.erase(t);
		p.pop();
		standed.pop();
	}
	puts("ACCEPT!");
}
void test_throw()
{
	printf("test_throw             : ");
	int num = 4000;
	sjtu::strict_fib_heap<int> q;
	ss.clear();
	for(int i=1;i<=num;i++)
	{
		int tmp = get_rand();
		ss.insert(tmp);
		q.push(tmp);
	}
	for(int i=1;i<=num;i++)
	{
		q.pop();
	}
	bool flag = 0;
	try{
		q.pop();	
	}
	catch(sjtu::container_is_empty) {flag = 1;}
	catch(...){flag = 0;};
	if (!flag) 
	{
		puts("ERROR!");
		return;	
	}
	
	flag = 0;
	try{
		cout<<q.top();	
	}
	catch(sjtu::container_is_empty) {flag = 1;}
	catch(...){flag = 0;};
	if (!flag) 
	{
		puts("ERROR!");
		return;	
	}
	puts("ACCEPT!");
}
int main()
{
	test_int();
	test_advance();
	test_merge();
	test_copy_construction();
	test_evaluation();
	test_throw();
}

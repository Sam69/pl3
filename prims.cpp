#include<iostream>
#include<limits.h>
#include<queue>
#include<algorithm>
//#include<bits/stdc++.h>
#include<omp.h>
#define INF INT_MAX
using namespace std;

int main()
{
	cout<<"Enter no of Vertices: ";
	int n,e;
	cin>>n;
	int adj_mat[n][n];
	int v[n];
	vector<int> vis;
#pragma omp parallel num_threads(n)
//	for(int i=0;i<n;i++)
	{
		int i=omp_get_thread_num();
		v[i]=0;
		for(int j=0;j<n;j++)
		{
				adj_mat[i][j]=INF;
		}
	}
	cout<<"Enter no of edges: ";
	cin>>e;
	cout<<"Enter 3 integers in order (vertex a vertex b distance): \n";
	for(int i=0;i<e;i++)
	{
		int x,y,z;
		cin>>x>>y>>z;
		adj_mat[x][y]=z;
		adj_mat[y][x]=z;
	}
	vis.push_back(0);
	v[0]=1;
	int sum=0;
	while(vis.size()<abs(n))
	{
		int k,l,min=INF;
		for(unsigned int i=0;i<vis.size();i++)
		{
#pragma omp parallel num_threads(n)
//			for(int j=0;j<n;j++)
			{
				int j=omp_get_thread_num();
				if(adj_mat[vis[i]][j]<min && v[j]!=1)
				{
					min=adj_mat[vis[i]][j];
					l=vis[i];
					k=j;
				}
			}
		}
		cout<<l<<"----"<<k<<"\t"<<min<<"\n";
		vis.push_back(k);
		v[k]=1;
		sum+=min;
	}
	cout<<"MST Cost="<<sum<<"\n";
	return 0;
}

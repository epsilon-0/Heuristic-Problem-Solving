#include<iostream>
#include<algorithm>
#include<cmath>
#include<vector>
#include<cstdio>
#include<iomanip>
#include<cassert>

using namespace std;

const int MAXV=1005;

// UNION FIND DATA STRUCTURE

int rnk[MAXV],parent[MAXV],treecnt[MAXV];

int init(){
  for(int i=0;i<MAXV;i++){
    rnk[i]=0;parent[i]=i,treecnt[i]=1;
  }
  return 0;
}

int find(int node){
  int ancestor=node;
  int child=node;
  int temp=node;
  while(parent[ancestor]!=ancestor){
    ancestor=parent[ancestor];
  }
  while(parent[child]!=ancestor){
    temp=parent[child];
    parent[node]=ancestor;
    child=temp;
  }
  return ancestor;
}

int funion(int x,int y){
  int fx=find(x);
  int fy=find(y);
  if(fx!=fy){
    if(rnk[fy]>rnk[fx]){
      swap(fx,fy);
    }
    if(rnk[fx]==rnk[fy]){
      rnk[fx]++;
    }
    parent[fy]=fx;
  }
  return 0;
}

// UNION FIND FINISH

int id[MAXV];

double coord[MAXV][2];

double dist[MAXV][MAXV];

bool ttree[MAXV][MAXV]={false};
bool intour[MAXV]={false};

double mdistance(int i,int j){
  return sqrt(pow(coord[i][0]-coord[j][0],2)+pow(coord[i][1]-coord[j][1],2));
}

bool edge_comp (pair<int,int> e1, pair<int,int> e2){
  return (dist[e1.first][e1.second]<dist[e2.first][e2.second]);
}

vector<pair<int,int> > edges;
vector<int> tour(0);

void dfs(int vert,int n){
  tour.push_back(vert);
  intour[vert]=true;
  for(int i=0;i<n;i++){
    if(ttree[vert][i] && !intour[i]){
      dfs(i,n);
    }
  }
}

int main(){

  int d;double x,y;
  int n=0;
  while(scanf("%d %lf %lf",&d,&x,&y)!=EOF){
    id[n]=d;
    coord.push_back(make_pair(x,y);
    n++;
  }
  for(int i=0;i<n;i++){
    for(int j=0;j<n;j++){
      dist[i][j]=mdistance(i,j);
      dist[j][i]=dist[i][j];
      edges.push_back(make_pair(i,j));
    }
  }

  sort(edges.begin(),edges.end(),edge_comp);
  init();

  int xx,yy;
  double length=0;
  for(int i=0;i<edges.size();i++){
    xx=edges[i].first;yy=edges[i].second;
    if(find(xx)!=find(yy)){
      ttree[xx][yy]=true;
      ttree[yy][xx]=true;
      funion(xx,yy);
      length+=dist[xx][yy];
    }
  }

  dfs(0,n);

  for(int i=0; i<n;i++){
    cout<<id[tour[i]]<<endl;
  }
}

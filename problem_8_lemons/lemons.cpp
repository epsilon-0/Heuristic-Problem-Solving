#include <iostream>
#include <cstdio>
#include <vector>
#include "edmondskarp.h"
#include "fastflow.h"
#include <numeric>
#include <cassert>

using namespace std;

typedef double TYPE;

const TYPE MULT = 1;

vector<vector<int> > assets(0);
vector<int> degrees;
int N,M,D,n[2],m[2],d[2];

vector<vector<int> > network;
vector<vector<double> > capacities;

int get_input(){
  scanf("%d %d %d\n",&N,&M,&D);
  scanf("%d-%d %d-%d %d-%d",n+0,n+1,m+0,m+1,d+0,d+1);
  int val;
  assets.resize(N);
  for(int i = 0; i < N; i++){
    for(int j = 0; j < M; j++){
      scanf("%d", &val);
      assets[i].push_back(val);
    }
  }
  for(int i = 0; i < N; i++){
    degrees.push_back(accumulate(assets[i].begin(), assets[i].end(), 0));
  }
  for(int i = 0; i < M; i++){
    degrees.push_back(D);
  }
  return 42;
}


int make_network(){
  network.clear();network.resize(2+M+N);
  capacities.clear();capacities.resize(2+M+N,vector<double>(2+M+N,0));
  for(int i = 0; i < N+M; i++){
    network[0].push_back(i+1);
    capacities[0][i+1] = M*D;
  }
  for(int i = 0; i < N; i++){
    for(int j = 0; j < M; j++){
      if(assets[i][j]){
	network[i+1].push_back(j+1);
	capacities[i+1][j+1] = 1;
	network[j+1].push_back(i+1);
	capacities[j+1][i+1] = 1;
      }
    }
    network[i+1].push_back(N+M+1);
  }
  return 42;
}

int make_capacities(double g){
  for(int i = 1; i < N+M+1; i++){
    capacities[i][N+M+1] = M*D + 2*g - (network[i].size()-1);
  }
  return 42;
}

vector<bool> get_subgraph(){
  TYPE l=0, u=(TYPE)M*D*MULT, g;
  vector<bool> subg, S;
  int cnt;
  while(u-l>1){
    g = (u+l)/2;
    // make network with g
    Dinitz dnt(1,N+M+2,N+M+2);
    for(int i = 2; i<= N+M+1; i++){
      dnt.add(1,i,(TYPE)M*D*MULT);
      dnt.add(i,1,0);

      dnt.add(i,N+M+2,(TYPE)(M*D - degrees[i-2])*MULT + 2*g);
      dnt.add(N+M+2,i,0);
    }

    for( int i = 0; i < N; i++){
      for( int j = 0; j < M; j++){
	if(assets[i][j]){
	  dnt.add(i+2,N+j+2,MULT);
	  dnt.add(N+j+2,i+2,MULT);
	}
      }
    }
    cout << "----------------------------------" << endl;
    // get mincut
    dnt.dinitz();
    S = dnt.getMinCut();
    assert(S[1]);
    cnt = 0;
    for( int i = 1;  i <= N+M+2; i++){
      if(S[i]){
	cnt++;
      }
    }
    cout << cnt << endl;
    if(cnt==1){
      u=g;
    }
    else{
      cout << "wtf now" << endl;
      l=g;
      subg = S;
    }
  }
  subg.pop_back();
  subg.erase(subg.begin()+0);
  subg.erase(subg.begin()+0);
  return subg;
}

int main(){
  get_input();
  vector<bool> densest = get_subgraph();
  int cnt = 0;
  cout << "over here now" << endl;
  cout << densest.size() << endl;
  for(int i = 0; i < densest.size(); i++){
    if(densest[i]){
      cout << i << endl;
      cnt++;
    }
  }
  cout << "here" << endl;
  cout << cnt << " " << densest.size() << endl;
}

#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <string>
#include <cmath>
#include <queue>
#include <set>
#include <cassert>

using namespace std;

#define REP(i,a,b) for(int i = int(a); i < int (b); i++)
#define mset(cont, val) memset(cont, val, sizeof(cont))
#define mcpy(cont, orig) memcpy(cont, orig, sizeof(cont))
#define edge pair<int, int>
#define MAXV 1001

int num_vert = 0;  // stores number of vertices in our graph

int id[MAXV] = {0};  // maps the ids to nice formats

double coord[MAXV][2] = {0};  // store coordinates of the points

int curr_tour[MAXV] = {0}, opt_tour[MAXV] = {0}; // we store the tours here

bool broken[MAXV][MAXV] = {false}, joined[MAXV][MAXV] = {false};

double dist[MAXV][MAXV] = {0}; // we store the distances between vertices in this matrix

// UNION FIND DATA STRUCTURE

// MST ALGORITHM

bool ttree[MAXV][MAXV]={false};
bool intour[MAXV]={false};

bool edge_comp(edge e1, edge e2){
  return (dist[e1.first][e1.second]<dist[e2.first][e2.second]);
}

vector<edge> edges;

vector<int> mst_tour;

void make_mst_tour(int vert){
  mst_tour.push_back(vert);
  intour[vert]=true;
  for(int i=0;i<num_vert;i++){
    if(ttree[vert][i] && !intour[i]){
      make_mst_tour(i);
    }
  }
}

// MST FINISH

int rnk[MAXV],parent[MAXV],treecnt[MAXV];

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

int init(){

  REP(i, 0, num_vert){
    REP(j, 0, num_vert){
      dist[i][j] = sqrt( pow(coord[i][0] - coord[j][0], 2) + pow(coord[i][1] - coord[j][i], 2) );
      dist[j][i] = dist[i][j];
      edges.push_back(make_pair(i,j));
    }
  }
  
  sort(edges.begin(), edges.end(), edge_comp);

  for(int i=0;i<MAXV;i++){
    rnk[i]=0;parent[i]=i,treecnt[i]=1;
  }

  int xx, yy;
  for(int i = 0; i < edges.size(); i++){
    xx = edges[i].first; yy = edges[i].second;
    if(find(xx) != find(yy)){
      ttree[xx][yy] = true;
      ttree[yy][xx] = true;
      funion(xx, yy);
    }
  }

  make_mst_tour(0);

  REP(i, 0, num_vert){
    opt_tour[mst_tour[i]] = mst_tour[ (i+1) % num_vert ];
  }

  mcpy(curr_tour, opt_tour);

  return 1;
}


// at the end tour[start] remains unchanged
// need to handle that
int tour_reverse(int start,int endd, int tour[] ){   // reverse the direction of the tour in the segment starting from start ending at endd
  if(start==endd){
    return 0; // we will not reverse the whole permutation
  }
  int curr = tour[start], next = tour[tour[start]], temp;
  while(curr!=endd){
    temp = tour[next];
    tour[next] = curr;
    curr = next;
    next = temp;
  }
  return 1;
}

bool is_tour(int tour[]){
  int cnt = 1, start = tour[0];
  while(start != 0){
    start = tour[start];
    cnt++;
  }
  if(cnt == num_vert){
    return true;
  }
  return false;
}

// we need to check if the chosen edges satisfy 4 c,d,e
bool satisfies4cde(edge yi, edge xi, double gain ){
  bool ans = true;

  // we should check that they are not the same edge
  if((yi.first == xi.first && yi.second == xi.second) ||
     (yi.second == xi.first && yi.first == xi.second)){
      ans=false;
     }

  // c states that yi should not have been previously broken and 
  if(broken[yi.first][yi.second] || broken[yi.second][yi.first] ||
     joined[xi.first][xi.second] || joined[xi.second][xi.first]){ // xi should not have been previously joined
    ans=false;
  }

  // d states that the total gain after removing xi and joining yi should be positive
  if(gain + dist[xi.first][xi.second] - dist[yi.first][yi.second] <= 0){
    ans=false;
  }

  // e indicates that the choice of yi should allow some xi+1 to be broken such that condition a is satisfied
  int temp_tour[MAXV];
  mcpy(temp_tour, curr_tour);
  
  edge xi_p;  // this is xi+1 which is the edge which is pointing to the start of 
  xi_p.first = yi.second;
  REP(i,0,num_vert){
    if(temp_tour[i] == xi.first){
      xi_p.second = i;
      break;
    }
  }
  
  if(joined[xi_p.first][xi_p.second]){  // this cannot be an already joined edge
    ans==false;
  }
  
  // change temp_tour check that it still remains a tour

  // 

  return ans;
}

int optimize(int vert){   // we will try to find sequential move which are optimum locally
  double g_star = 0, gi_star = 0, gi = 0, g = 0;  // g_star has the max gain so far
  edge xi, yi, xi_p;  // xi is the current edge that we are going to break, yi is the edge that we join and xi_p is the next edge which we get by choosing yi
  xi.first = vert; xi.second = curr_tour[vert];
  int ti, ti1, curr_vert = vert, next_vert, poss_vert;
  mset(joined, false);
  mset(broken, false);

  while(true){   // we only break if some conditions are unsatisfied
    // xi is already chosen at the start of the loop
    cout<<"in while\n";
    // we have to choose yi such that it starts at the end point of xi
    yi.first=xi.second;
    REP(i, 0, num_vert){
      yi.second = i;

      // now for this yi we need to check if it satisfies 4 c, d, e
      if(!satisfies4cde(xi, yi, g)){
        yi.second = -1;
        continue;
      }
      break;
    }
    cout<<"got yi "<<yi.first<<" "<<yi.second<<endl;
    cout<<"got xi "<<xi.first<<" "<<xi.second<<endl;
    // we aren't able to find any yi satisfying the conditions
    if(yi.second==-1){
      break;
    }

    // we will calculate the gain we have if we terminate at this point
    gi_star = dist[xi.first][xi.second] - dist[xi.first][vert];   // and increase g_star if needed and store the OPTIMAL tour as of yet
    cout<<"g*="<<g_star<<" g="<<g<<" gi="<<gi<<endl;
    if(g_star < g + gi_star){
      g_star = g + gi_star;
      mcpy(opt_tour,curr_tour);
      opt_tour[vert] = xi.second;
      assert(is_tour(opt_tour));
    }

    // when we are out of that loop we are guaranteed to find a yi which is compatible with the xi
    // hence we have chosen xi, yi
    broken[xi.first][xi.second] = true;   // we add them to the broken and joined sets respectively,
    broken[xi.second][xi.first] = true;

    joined[yi.first][yi.second] = true;
    joined[yi.second][yi.first] = true;

    // because yi is chosen xi+1 is fixed, we need to find it
    xi_p.first = yi.second;
    REP(i,0,num_vert){
      if(curr_tour[i] == xi.first){
        xi_p.second = i;
        break;
      }
    }
    cout<<"found xi_p "<<xi_p.first<<" "<<xi_p.second;

    // we calculate the gain when we add yi and remove xi
    gi = dist[xi.first][xi.second] - dist[yi.first][yi.second];

    // we join yi and reverse the corresponding part of the list
    cout<<"starting reverse\n";
    REP(i, 0, num_vert) cout<<curr_tour[i]<<" ";
    cout<<endl;

    tour_reverse(xi_p.second, curr_tour[xi.second], curr_tour);
    cout<<"reversed\n";

    curr_tour[yi.first] = yi.second;

    xi = xi_p;

  }
}

double tour_length(int tour[]){
  double lgt = 0;
  REP(i, 0, num_vert){
    lgt += dist[i][tour[i]];
  }
}

int main(){
  num_vert=0;

  int ids; double x, y;

  while(scanf("%d %lf %lf", &ids, &x, &y)!=EOF){
    id[num_vert] = ids;
    coord[num_vert][0] = x;
    coord[num_vert][1] = y;
    num_vert++;
  }

  init();

  optimize(0);

}

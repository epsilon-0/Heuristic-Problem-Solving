#include<iostream>
#include<vector>
#include<algorithm>

#include "knapsack.h"

using namespace std;

int TYPE;

vector< int > value, weight;
int capacity;
vector< int > knapsacks;
vector< vector< int > > gain;

int get_input(){
  int sz, index, val, wt, knaps;
  cin >> TYPE;
  if ( TYPE == 1 ){
    cin >> sz;
    cin >> capacity;
    value.resize(sz); weight.resize(sz);
    for ( int i = 0; i < sz; i++ ){
      cin >> index >> val >> wt;
      index--;
      value[index] = val;
      weight[index] = wt;
    }
  }
  else if ( TYPE == 2 ){
    cin >> sz >> knaps;
    for ( int i = 0; i < knaps; i++ ){
      cin >> capacity;
      knapsacks.push_back(capacity);
    }
    value.resize(sz); weight.resize(sz);
    for ( int i = 0; i < sz; i++ ){
      cin >> index >> val >> wt;
      index--;
      value[index] = val;
      weight[index] = wt;
    }
  }
  else if ( TYPE == 3 ){
    cin >> sz;
    cin >> capacity;
    for ( int i = 0; i < sz; i++ ){
      cin >> wt;
      weight.push_back(wt);
    }
    gain.resize(sz);
    for ( int i = 0; i < sz; i++ ){
      gain[i].resize(sz);
    }
    for ( int i = 0; i < sz; i++ ){
      cin >> val;
      gain[i][i] = val;
      value.push_back( val );
    }
    for ( int i = 0; i < sz - 1; i++ ){
      for ( int j = i+1; j < sz; j++ ){
	cin >> val;
	gain[i][j] = val;
	gain[j][i] = val;
      }
    }
  }
}

int main(){
  get_input();
  Knapsack nt(value, weight, capacity, true);
  vector< int > answer = nt.getWitness();
  int sum = 0;
  for ( int i = 0; i < answer.size(); i++ ){
    sum += value[answer[i]];
  }
  cout << sum << endl;
}

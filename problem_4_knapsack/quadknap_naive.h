#ifndef QUADKNAP_
#define QUADKNAP_

#include<vector>
#include<numeric>

using namespace std;

class Quadknap{
 private:
  vector< int > weight;
  int capacity;
  vector< vector< int > > gain;
  vector< vector< int > > F;
  vector< vector< vector< int > > > S;
  vector< int > answer;
  int solution;
  
 public:
  
  Quadknap( vector< int > weight, vector< vector< int > > gain, int capacity ){
    this->weight = weight;
    this->gain = gain;
    this->capacity = capacity;
    
    F.resize(weight.size());
    for ( int i = 0; i < weight.size(); i++ ){
      F[i].resize(capacity + 1, 0);
    }

    S.resize(weight.size());
    for ( int i = 0; i < S.size(); i++ ){
      S[i].resize(capacity + 1);
    }

    solve();

  }

  void solve(){
    int beta = 0;
    for ( int k = 0; k < weight.size(); k++ ){
      for ( int r = 0; r <= capacity - weight[k]; r++ ){
	if ( k > 0 && F[k-1][r] > F[k][r] ){
	  F[k][r] = F[k-1][r];
	  S[k][r] = S[k-1][r];
	}
	if ( k > 0 ){
	  beta = F[k-1][r] + gain[k][k];
	  for ( int i = 0; i < S[k-1][r].size(); i++ ){
	    beta += gain[i][k];
	  }
	}
	else {
	  beta = gain[k][k];
	}
	if ( beta > F[k][r+weight[k]] ){
	  F[k][r+weight[k]] = beta;
	  if ( k > 0 ){
	    S[k][r+weight[k]] = S[k-1][r];
	  }
	  S[k][r+weight[k]].push_back(k);
	}
      }
    }
    int mx = -1;
    int r_b;
    for ( int i = 0; i < capacity + 1; i++ ){
      if ( F[weight.size()-1][i] > mx ){
	r_b = i;
	mx = F[weight.size()-1][i];
      }
    }
    solution = F[weight.size()-1][r_b];
    answer = S[weight.size()-1][r_b];
  }
  
  vector< int > getWitness(){
    return answer;
  }
  
  int getSolution(){
    return solution;
  }
  
};


#endif

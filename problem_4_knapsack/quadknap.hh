#ifndef QUADKNAP_
#define QUADKNAP_

class Quadknap{
 private:
  vector< int > weight;
  vector< vector< int > > gain;
  vector< int > answer;
  int solution;
  int capacity;
  vector< int > F;
  vector< vector< int > > B;

 public:
  Quadknap( vector< int > weight, vector< vector< int > > gain, int capacity ){
    this->weight = weight;
    this->gain = gain;
    this->capacity = capacity;
    
    F.clear();
    F.resize(capacity + 1, 0);

    B.resize(capacity + 1);
    for ( int i = 0; i< capacity + 1; i++ ){
      B[i].resize(weight.size(), 0);
    }

    solve();
  }

  void solve(){
    int beta = 0;
    for ( int k = 0; k < weight.size(); k++ ){
      for ( int r = capacity; r >=weight[k]; r-- ){
	// calculate beta
	beta = F[r-weight[k]] + gain[k][k];
	for ( int i = 0; i < k; i++ ){
	  beta += gain[i][k] * B[r-weight[k]][i];
	}
	if ( beta > F[r] ){
	  F[r] = beta;
	  B[r][k] = 1;
	}
      }
    }
    int r_b;
    solution = -1;
    for ( int i = 0; i < capacity + 1; i++ ){
      if ( F[i] > solution ){
	solution = F[i];
	r_b = i;
      }
    }
    int pos = weight.size()-1;
    int cap = r_b;
    while ( pos >= 0 ){
      if ( B[cap][pos] == 1 ){
	cap -= weight[pos];
	answer.push_back(pos);
      }
      pos--;
    }

  }

  vector< int > getWitness(){
    return answer;
  }

  int getSolution(){
    return solution;
  }

};

#endif

#include<iostream>
#include<cstdio>
#include<vector>
#include<cmath>
#include<algorithm>
#include<sstream>
#include<string>
#include<cstring>
#include<set>

#include "rand_lib.h"

using namespace std;

vector < vector < int > > clauses;                        // we store the clauses in this 
vector < int > assignment, best_assignment;               // the current assignment for the variables
int num_clauses, num_var;                                 // the total number of clauses and variable
set < int > false_clauses;                                // the currently false clauses because we are going to randomly select through them
vector < vector < int > > parent_clause;                  // for each veriable stores the clauses in which it appears
int pos = 0, neg = 0;


int get_input();
int print_input();
int climb ( int cl );                    // flip a literal of a given clause which maximizes the total number of true clauses
void flip_rand_ver ( int cl );           // flips a random literal of the given clause // needed to get out of local minima and have a global search
int walksat ( int mf, float pr );        // the main algorithm

int main(){
   
  srand(time(NULL));

  get_input();   // get the damn input
  //  print_input();

  int init = (pos > neg) ? 1 : -1;

  //set a random initial assignment to the variables
  for ( int i = 0; i < num_var + 1; i++ ){
    assignment[i] = init;
  }

  int curr_best = walksat(400000, 0.1);

  /*
  int curr;
  
  for ( int i = 0; i < 20 && isit != 1; i++ ){
    for ( int j = 0; j < num_var; j++){
      if ( f_rand() < 0.45 ){
	assignment[j] = -1;
      }
      else{
	assignment[j] = 1;
      }
    }

    curr = walksat(200000, 0.1);

    if ( curr_best < curr ){
      curr_best = curr;
      best_assignment = assignment;
    }
  }
  */

  for ( int i = 1; i <= num_var; i++ ){
    cout << best_assignment[i] * i << " ";
  }
  cout << endl;

  return 0;
}

int get_input(){
  string st, pt, qt;
  while( 1 ){
    getline(cin, st);
    if(st[0] != 'c'){
      break;
    }
  }
  stringstream ss( st );

  ss >> pt >> qt >> num_var >> num_clauses;

  int tmp;
  
  clauses.resize( num_clauses );
  assignment.resize( num_var + 1);
  parent_clause.resize( num_var + 1);

  for ( int i = 0; i < num_clauses; i++ ){
    for ( int j = 0; j < 3; j++ ){
      cin >> tmp;
      clauses[i].push_back(tmp);
      parent_clause[ abs(tmp) ].push_back( i );
      if ( tmp > 0 ){
	pos++;
      }
      else{
	neg++;
      }
    }
    cin>>tmp;
  }
  
  return 1;
}

int print_input(){
  cout << "Number of variables = "<< num_var << endl;
  cout << "Number of clauses   = "<< num_clauses << endl;
  for ( int i = 0; i < clauses.size(); i++){
    cout << clauses[i][0] << " " << clauses[i][1] << " " << clauses[i][2] << "\n";
  }
  return 1;
}

int climb ( int cl ){
  int result;
  int best_lit = -1;
  int curr_true;
  int now_true;
  int par_cl;
  int curr_var;
  int curr_best;

  for ( int i = 0; i < 3; i++ ){

    curr_var = abs(clauses[cl][i]);

    curr_true = 0;
    for ( int j = 0; j < parent_clause[curr_var].size(); j++ ){
      par_cl = parent_clause[curr_var][j];
      for ( int k = 0; k < 3; k++ ){
	if ( clauses[par_cl][k] * assignment[ abs(clauses[par_cl][k]) ] > 0 ){
	  curr_true++;
	  break;
	}
      }
    }
    
    now_true = 0;
    assignment[curr_var] *= -1;
    for ( int j = 0; j < parent_clause[curr_var].size(); j++ ){
      par_cl = parent_clause[curr_var][j];
      for ( int k = 0; k < 3; k++ ){
	if ( clauses[par_cl][k] * assignment[ abs(clauses[par_cl][k]) ] > 0 ){
	  now_true++;
	  break;
	}
      }
    }
    assignment[curr_var] *= -1;

    result = now_true - curr_true;

    if( i == 0 ) curr_best = result;

    if ( result >= curr_best && result > 0 ){
      curr_best = result;
      best_lit = curr_var;
    }

  }

  bool issat = false;
  
  if ( best_lit != -1 ){

    assignment[best_lit] *= -1;

    for ( int i = 0; i < parent_clause[best_lit].size(); i++){
      par_cl = parent_clause[best_lit][i];
      issat = false;
      for ( int j = 0; j < 3; j++ ){
	if( clauses[par_cl][j] * assignment[ abs(clauses[par_cl][j]) ] > 0 ){
	  issat = true;
	  break;
	}
      }
      if( !issat ){
	false_clauses.insert( par_cl );
      }
      else{
	if ( false_clauses.count( par_cl ) > 0 ){
	  false_clauses.erase( par_cl );
	}
      } 
    } 
  }
}

int flip_rand_lit ( int cl ){
  int best_lit = abs( clauses[cl][i_rand(3)] );

  assignment[best_lit] *= -1;
  
  int par_cl;
  bool issat;
 
  for ( int i = 0; i < parent_clause[best_lit].size(); i++){
    par_cl = parent_clause[best_lit][i];
    issat = false;
    for ( int j = 0; j < 3; j++ ){
      if( clauses[par_cl][j] * assignment[ abs(clauses[par_cl][j]) ] > 0 ){
	issat = true;
      }
    }
    if( !issat ){
      false_clauses.insert( par_cl );
    }
    else{
      if ( false_clauses.count( par_cl ) > 0 ){
	false_clauses.erase( par_cl );
      }
    } 
  }
}

int walksat ( int mf, float pr ){

  int fclause, index;
  set<int>::iterator itr;

  false_clauses.clear();

  bool issat;

  for ( int i = 0; i < num_clauses; i++ ){
    issat = false;
    for ( int j = 0; j < 3; j++ ){
      if ( clauses[i][j] * assignment[abs( clauses[i][j] )] > 0 ){
	issat = true;
      }
    }
    if ( !issat ){
      false_clauses.insert( i );
    }
  }

  int curr_unsat = false_clauses.size();
  best_assignment = assignment;

  for ( int i = 0; i < mf; i++ ){

    if ( false_clauses.size() == 0 ) return 0;

    itr = false_clauses.begin();
    
    index = i_rand( false_clauses.size() - 1 );

    advance(itr, index);

    fclause = *itr;

    if ( f_rand() < pr ){
      flip_rand_lit( fclause );
    }
    else{
      climb( fclause );
    }
    
    if ( curr_unsat > false_clauses.size() ){
      best_assignment = assignment;
      curr_unsat = false_clauses.size();
    }
    
  }
  return curr_unsat;
}

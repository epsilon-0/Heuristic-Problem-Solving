#include<iostream>
#include<cstdio>
#include<vector>
#include<cmath>
#include<algorithm>
#include<sstream>
#include<string>
#include<cstring>

#include "rand_lib.h"

using namespace std;

vector < vector < int > > clauses;       // we store the clauses in this 
vector < int > assignment;               // the current assignment for the variables
int num_clauses, num_var;                // the total number of clauses and variable
vector < int > true_clause;              // the current assignment of a clause
vector < int > false_clauses;            // the currently false clauses because we are going to randomly select through them

int get_input();
int print_input();
int test_model();                        // returns the number of satisfied clauses in the current assignment
float pos_vs_neg ( int var );            // returns the ratio of pos/neg or neg/pos literalsfor given variable
void climb ( int cl, int true_clauses ); // flip the literal of a given clause which maximizes the total number of true clauses
void flip_rand_ver ( int cl );           // flips a random literal of the given clause // needed to get out of local minima and have a global search
int walksat ( int mf, float pr );        // the main algorithm

int main(){

  srand(time(NULL));

  get_input();   // get the damn input
  //print_input();

  //set all the clauses to be currently false
  for ( int i = 0; i < num_clauses; i++ ){
    true_clause.push_back( -1 );
  }

  //set a random initial assignment to the variables
  for ( int i = 0; i < num_var + 1; i++ ){
    assignment[i] = 1;
  }
  
  int isit = walksat(200000, 0.1);
  
  int curr_best = test_model(), curr;
  vector < int > best_assignment = assignment;
  /*
  for ( int i = 0; i < 10 && isit != 1; i++ ){
    for ( int j = 0; j < num_var; j++){
      if ( f_rand() < 0.45 ){
	assignment[i] = -1;
      }
      else{
	assignment[i] = 1;
      }
    }

    isit = walksat(200000, 0.1);
    curr = test_model();
    if ( curr_best < curr ){
      curr_best = curr;
      best_assignment = assignment;
    }
  }
  */
  for ( int i = 1; i <= num_var; i++ ){
    cout<<best_assignment[i] * i<<" ";
  }
  cout<<endl;

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

  for ( int i = 0; i < num_clauses; i++ ){
    for ( int j = 0; j < 3; j++ ){
      cin >> tmp;
      clauses[i].push_back(tmp);
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

int test_model(){
  for ( int i = 0; i < num_clauses; i++ ){
    true_clause[i] = -1;
  }
  false_clauses.clear();
  for ( int i = 0; i < num_clauses; i++ ){
    for ( int j = 0; j < 3; j++ ){
      if ( clauses[i][j] * assignment[abs( clauses[i][j] )] > 0 ){
	true_clause[i] = 1;
      }
    }
    if ( true_clause[i] != 1 ){
      false_clauses.push_back( i );
    }
  }
  return num_clauses - false_clauses.size();
}

void climb ( int cl, int true_clauses ){
  int result;
  int best_lit = -1;
  for ( int i = 0; i < 3; i++ ){
    assignment[ abs(clauses[cl][i]) ] *= -1;
    result = test_model();
    assignment[ abs(clauses[cl][i]) ] *= -1;
    if ( result > true_clauses ){
      best_lit = abs(clauses[cl][i]);
      true_clauses = result;
    }
  }
  if ( best_lit != -1 ){
    assignment[best_lit] *= -1;
    test_model();
  }
}

void flip_rand_lit ( int cl ){
  int best_lit = abs( clauses[cl][i_rand(3)] );
  assignment[best_lit] *= -1;
  test_model();
}

int walksat ( int mf, float pr ){
  int true_clauses;
  int fclause;
  for ( int i = 0; i < mf; i++ ){
    true_clauses = test_model();
    if ( true_clauses == num_clauses ) return 1;
    fclause = false_clauses[ i_rand( false_clauses.size() )];
    if ( f_rand() < pr ){
      flip_rand_lit( fclause );
    }
    else{
      climb( fclause, true_clauses );
    }
  }
  return 0;
}

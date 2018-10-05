#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include "rand_lib.hh"

using namespace std;

vector<vector<int>> clauses; // we store the clauses in this
vector<int> assignment,
    best_assignment;      // the current assignment for the variables
int num_clauses, num_var; // the total number of clauses and variable
set<int> false_clauses;   // the currently false clauses because we are going to
                          // randomly select through them
vector<vector<int>>
    parent_clause;   // for each veriable stores the clauses in which it appears
vector<int> pos_cnt; // for each variable the count of pos - neg
int TYPE = 0;

int get_input();
int print_input();
bool issat(int cl); // checks if a given clause is currently satisfied by the
                    // assignment
int climb(int cl); // flip a literal of a given clause which maximizes the total
                   // number of true clauses
void flip_rand_ver(
    int cl); // flips a random literal of the given clause // needed to get out
             // of local minima and have a global search
int walksat(int mf, float pr); // the main algorithm which returns the number of
                               // unsatisfied clauses after it has terminated

int main() {

  srand(time(NULL));

  get_input(); // get the damn input
  //  print_input();
  //  cout << TYPE << endl;

  // set a random initial assignment to the variables
  for (int i = 0; i < num_var + 1; i++) {
    if (pos_cnt[i]) {
      assignment[i] = 1;
    } else {
      assignment[i] = -1;
    }
  }

  // get current number of unsatisfied clauses
  int curr_best = walksat(400000, 0.1);

  // print the assignment
  for (int i = 1; i <= num_var; i++) {
    cout << best_assignment[i] * i << " ";
  }
  cout << endl;

  return 0;
}

int get_input() {
  string st, pt, qt;
  while (1) {
    getline(cin, st);
    if (st == "Exactly-1") {
      TYPE = 1;
    } else if (st == "Exactly-2") {
      TYPE = 2;
    } else if (st[0] != 'c') {
      break;
    }
  }
  stringstream ss(st);

  ss >> pt >> qt >> num_var >> num_clauses;

  int tmp;

  clauses.resize(num_clauses);
  assignment.resize(num_var + 1);
  parent_clause.resize(num_var + 1);
  pos_cnt.resize(num_var + 1);

  for (int i = 0; i < num_clauses; i++) {
    for (int j = 0; j < 3; j++) {
      cin >> tmp;
      clauses[i].push_back(tmp);
      parent_clause[abs(tmp)].push_back(i);
      if (tmp > 0) {
        pos_cnt[tmp]++;
      } else {
        pos_cnt[-1 * tmp]--;
      }
    }
    cin >> tmp;
  }

  return 1;
}

int print_input() {
  cout << "Number of variables = " << num_var << endl;
  cout << "Number of clauses   = " << num_clauses << endl;
  cout << "== Printing the clauses ==\n";
  for (int i = 0; i < clauses.size(); i++) {
    cout << clauses[i][0] << " " << clauses[i][1] << " " << clauses[i][2]
         << "\n";
  }
  return 1;
}

// for checking unsatisfiability in normal case
bool issat0(int cl) {
  for (int i = 0; i < 3; i++) {
    if (clauses[cl][i] * assignment[abs(clauses[cl][i])] > 0) {
      return true;
    }
  }
  return false;
}

// unsat in Exactly-1
bool issat1(int cl) {
  int ssat = 0;
  for (int i = 0; i < 3; i++) {
    if (clauses[cl][i] * assignment[abs(clauses[cl][i])] > 0) {
      ssat++;
    }
  }
  if (ssat == 1) {
    return true;
  }
  return false;
}

// unsat in Exactly-2
bool issat2(int cl) {
  int ssat = 0;
  for (int i = 0; i < 3; i++) {
    if (clauses[cl][i] * assignment[abs(clauses[cl][i])] > 0) {
      ssat++;
    }
  }
  if (ssat == 2) {
    return true;
  }
  return false;
}

// overall satisfiability checker
bool issat(int cl) {
  if (TYPE == 0) {
    return issat0(cl);
  } else if (TYPE == 1) {
    return issat1(cl);
  } else if (TYPE == 2) {
    return issat2(cl);
  }
}

// given a clause we need to flip a variable which maximizes number of clauses
// which get satisfied
int climb(int cl) {
  int result;
  int best_lit = -1;
  int curr_true;
  int now_true;
  int par_cl;
  int curr_var;
  int curr_best;

  for (int i = 0; i < 3; i++) {

    curr_var = abs(clauses[cl][i]);

    curr_true = 0;
    for (int j = 0; j < parent_clause[curr_var].size(); j++) {
      if (issat(parent_clause[curr_var][j])) {
        curr_true++;
      }
    }

    now_true = 0;
    assignment[curr_var] *= -1;
    for (int j = 0; j < parent_clause[curr_var].size(); j++) {
      if (issat(parent_clause[curr_var][j])) {
        now_true++;
      }
    }
    assignment[curr_var] *= -1;

    result = now_true - curr_true;

    if (i == 0)
      curr_best = result;

    if (result >= curr_best && result > 0) {
      curr_best = result;
      best_lit = curr_var;
    }
  }

  if (best_lit != -1) {

    assignment[best_lit] *= -1;

    for (int i = 0; i < parent_clause[best_lit].size(); i++) {
      par_cl = parent_clause[best_lit][i];

      if (!issat(par_cl)) {
        false_clauses.insert(par_cl);
      } else {
        if (false_clauses.count(par_cl) > 0) {
          false_clauses.erase(par_cl);
        }
      }
    }
  }
}

// flip a random literal in the clause
int flip_rand_lit(int cl) {
  int best_lit = abs(clauses[cl][i_rand(3)]);

  assignment[best_lit] *= -1;

  int par_cl;

  for (int i = 0; i < parent_clause[best_lit].size(); i++) {
    par_cl = parent_clause[best_lit][i];

    if (!issat(par_cl)) {
      false_clauses.insert(par_cl);
    } else {
      if (false_clauses.count(par_cl) > 0) {
        false_clauses.erase(par_cl);
      }
    }
  }
}

int walksat(int mf, float pr) {

  int fclause, index;
  set<int>::iterator itr;

  false_clauses.clear();

  for (int i = 0; i < num_clauses; i++) {
    if (!issat(i)) {
      false_clauses.insert(i);
    }
  }

  int curr_unsat = false_clauses.size();
  best_assignment = assignment;

  for (int i = 0; i < mf; i++) {

    if (false_clauses.size() == 0)
      return 0;

    itr = false_clauses.begin();

    index = i_rand(false_clauses.size() - 1);

    advance(itr, index);

    fclause = *itr;

    if (f_rand() < pr) {
      flip_rand_lit(fclause);
    } else {
      climb(fclause);
    }

    if (curr_unsat > false_clauses.size()) {
      best_assignment = assignment;
      curr_unsat = false_clauses.size();
    }
  }
  return curr_unsat;
}

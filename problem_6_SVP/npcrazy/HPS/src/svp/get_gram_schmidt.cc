#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include <NTL/LLL.h>

NTL_CLIENT

using namespace std;

int main(int argc, char** argv) {
  string which = argv[1];
  ifstream infile(argv[2]);
  int numVectors, numDimensions;
  string line;
  getline(infile, line);
  istringstream str(line);
  str >> numVectors >> numDimensions;
  cout << "V: " << numVectors << " D: " << numDimensions << "\n"; 
  mat_ZZ B;
  B.SetDims(numVectors, numDimensions);
  long i = 0;
  while (getline(infile, line)) {
    istringstream stream(line);
    long j = 0;
    long entry;
    while (stream >> entry) {
      ZZ item(entry);
      B.put(i, j++, item);
    }
    i++;
  }
  mat_RR mu;
  vec_RR Bstar_square;
  ComputeGS(B, mu, Bstar_square);
  ofstream outfile;
  outfile.open (argv[3]);
  if (which == "mu") {
    for (int i = 0; i < mu.NumRows(); ++i) {
      for (int j = 0; j < mu.NumCols(); ++j) {
	outfile << mu.get(i, j) << " ";
      }
      outfile << "\n";
    }
  } else if (which == "bstar") {
    for (int i = 0; i < Bstar_square.length(); ++i) {
      outfile << Bstar_square.get(i) << " ";      
    }
    outfile << "\n";
  }
  outfile.close();
  cout << B;
  return 0;
}

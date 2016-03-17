#include <fstream>
#include <iostream>
#include <sstream>
#include <string>


#include <NTL/LLL.h>
#include <NTL/mat_RR.h>

NTL_CLIENT

using namespace std;

int main(int argc, char** argv) {
  ifstream infile(argv[1]);
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
  // Get Basis with BKZ
  G_BKZ_FP(B, 0.99, 20);
  ofstream myfile;
  myfile.open (argv[2]);
  for (int i = 0; i < numVectors; ++i) {
    for (int j = 0; j < numDimensions; ++j) {
      myfile << B.get(i, j) << " ";
    }
    myfile << "\n";
  }
  myfile.close();
  cout << B;
  return 0;
}

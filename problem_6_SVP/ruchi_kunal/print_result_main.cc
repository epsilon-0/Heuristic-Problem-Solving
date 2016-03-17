#include <unistd.h>
#include <getopt.h>
#include <stdio.h>
#include <iostream>
#include <fstream>

#include <NTL/LLL.h>
#include "gsieve.h"
#include "math.h"


int main(int argc, char *argv[])
{
	mat_ZZ A;
  	ifstream input_file(argv[1]);
  	if (input_file.is_open()) {
   	 input_file >> A;
   	 input_file.close();
  	} else {
   	 cout << "can't open matrix file" << endl;
  	}

  	vec_ZZ B;
  	ifstream in1(argv[2]);
  	if(in1.is_open())
  	{
  		in1 >> B;
  		in1.close();
  	}
    else
    {
      cout << "can't open tempmat" << endl;
    }

  	vec_ZZ X;
  	//cout << "A=" << A << endl;
  	//cout << "B=" << B << endl;
  	long int l = LatticeSolve(X, A, B);
  	if(l)
  	{
  		//cout << X << endl;
      for(int k=0;k<X.length();k++)
        cout<<X[k]<<endl;
  	}
  	else
  	{
  		cout << "Something wrong :(" << endl;
  	}

  	return 0;
}
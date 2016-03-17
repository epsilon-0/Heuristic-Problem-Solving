#include <unistd.h>
#include <getopt.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

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

    int number = atoi(argv[2]);

  	vec_ZZ B[100];

    for(int i=0;i<number;i++)
    {
      std::string line;
      std::string suffix = std::to_string(i);
      line = "tempmat_" + suffix;
      
      ifstream in1(line);
      if(in1.is_open())
      {
        in1 >> B[i];

        in1.close();
      }
      else
      {
        cout << "CANNOT OPEN FILE " << line << endl;
      }
    }
    cout << "vectors: " << endl;
    for(int i=0;i<number;i++)
    {
      cout << B[i] << endl;
    }



    ////get the output
  	/*vec_ZZ X;
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
  	}*/

  	return 0;
}
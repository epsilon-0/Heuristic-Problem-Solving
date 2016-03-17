#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <cmath>

using namespace std;    
int n,d;
std::vector<std::vector<int> > matrix;
std::vector<int> b;

int main(int atgc,char* argv[])
{
  ifstream ifile,ifile2;
  ifile.open(argv[1]);
  if(ifile.is_open())
  {
    string line;
    
    
    char *temp;
    getline(ifile,line);
    temp = new char[line.size()+1];
    strcpy(temp,line.c_str());
    char *pch;
    pch = strtok(temp," ");
    n = atoi(pch);
    cout << "n = " << n << "\n";
    pch = strtok(NULL," \n");
    d = atoi(pch);
    delete [] temp;
    temp = NULL;

    for(int i=0;i<n;i++)
    {
      vector<int> tmpv;
      getline(ifile,line);
      temp = new char[line.size()+1];
      strcpy(temp,line.c_str());
      pch = strtok(temp," ");
      //n = atoi(pch);
      for(int j=0;j<d;j++)
      {
        tmpv.push_back(atoi(pch));
        pch = strtok(NULL," \n");
      }
      delete [] temp;
      temp = NULL;
      matrix.push_back(tmpv);
    }
   }
   else
   {
    cout << "CAN NOT OPEN THE INPUT FILE" << endl;
   }

   ifile2.open(argv[2]);
   if(ifile2.is_open())
   {
    string line;
    char *temp;char *pch;
    getline(ifile2,line);
    line = line.substr(1);
    cout << "line1 = " << line << endl;
    line = line.substr(0,line.size()-1);
    cout << "line2 = " << line << endl;
    temp = new char[line.size()+1];
    strcpy(temp,line.c_str());
    pch = strtok(temp," ");
    b.push_back(atoi(pch));
    while(1)
    {
        pch = strtok(NULL," \n");
        if(pch == NULL)
            break;
        b.push_back(atoi(pch));
    }
   }
   else
   {
    cout << "CAN NOT OPEN THE VECTOR FILE" << endl;
   }

   cout << "A = " << endl;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            cout << matrix[i][j] << " ";
        }
        cout << "\n";
    }

    cout << "\nB = " << endl;
    for(int i=0;i<n;i++)
    {
        cout << b[i] << " ";
    }
    cout << "\n";
  
//////inverse starts here
    

int i,count,j;
double ratio,temp;

/* Read in matrix and b */
//scanf("%d",&n);
printf("The matrix is %d by %d\n",n,n);
/*printf("Matrix:\n");
for(i=0;i<n;i++){
        for(j=0;j<n;j++){
                //scanf("%lf ",&matrix[i][j]);
                // for Hilbert matrix 
                matrix[i][j] = 1. / (i+j+1);
        }
        scanf("%lf ",&b[i]);
        scanf("\n");
        b[i] = 1.;
}
for(i=0;i<n;i++){
        for(j=0;j<n;j++){
                printf("%lf ",matrix[i][j]);
        }
        printf("\n");
}
printf("Right Hand Side:\n");
for(i=0;i<n;i++){
        printf("%lf ",b[i]);
}
printf("\n");
// Gaussian elimination */
for(i=0;i<(n-1);i++){
        for(j=(i+1);j<n;j++){
                ratio = matrix[j][i] / matrix[i][i];
                for(count=i;count<n;count++) {
                        matrix[j][count] -= (ratio * matrix[i][count]);
                }
                b[j] -= (ratio * b[i]);
        }
}
for (i=0;i<=n-1;i++){
        for(j=0;j<n;j++){
                printf("%d ",matrix[i][j]);
        }
        printf("\n");
}
/* Back substitution */
double x[n];
x[n-1] = b[n-1] / matrix[n-1][n-1];
for(i=(n-2);i>=0;i--){
        temp = b[i];
        for(j=(i+1);j<n;j++){
                temp -= (matrix[i][j] * x[j]);
        }
        x[i] = temp / matrix[i][i];
}
double q=2.88;
int p = static_cast<int>(q);
cout << "p=" << p << endl;
printf("Answer:\n");
for(i=0;i<n;i++){

        //printf("%lf\n",x[i]);
    if(x[i] >= 0)
    {
        double p1 = x[i] + 0.5;
        int p2 = floor(p1);
        cout << p2 << endl;
    }
    else
    {
        double p1 = x[i] - 0.5;
        int p2 = ceil(p1);
        cout << p2 << endl;
    }
}



  /*for(int i=0;i<n;i++)
  {
    for(int j=i+1;)

    X[i] = 1 / A[i][i] * (B[i] - sum);
  }*/

  
   return 0;
}
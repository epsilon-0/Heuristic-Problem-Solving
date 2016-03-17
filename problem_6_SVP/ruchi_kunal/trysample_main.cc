//#include <NTL/ZZ.h>

//#include "sampler"

/*struct ListPoint {
  vec_int64 v;
  int64 norm;
};*/
//#include "gsieve.h"
#include <unistd.h>
#include <getopt.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
  #include <cstring>
#include <cstdlib>

#include <NTL/ZZ.h>
#include <NTL/vec_ZZ.h>
#include <NTL/vec_RR.h>
#include <NTL/mat_ZZ.h>
#include <NTL/mat_RR.h>
#include "sampler.h"
#include "math.h"

NTL_CLIENT

mat_ZZ B1;
KleinSampler ks;
int n;
int d;
time_t start;
double dist(std::vector<int> t)
{
  double result=0.0;
  for(int i=0;i<t.size();i++)
  {
    result+=(t[i]*t[i]);
  }
  result=sqrt(result);
  return result;
}

std::vector<int> SampleGauss()
{
  ListPoint *l=ks.Sample();
      //cout<<l->v[0];
      std::vector<int> t;
      for(int i=0;i<d;i++)
          t.push_back(l->v[i]);
    //  for(int i=0;i<d;i++)
      //  cout<<t[i]<<" ";
      //cout<<"\n";

      return t;


}

std::vector<int> reduce(std::vector<int> p1, std::vector<int> p2)
{
  int p1p2=0;
  int p2p2=0;
  for(int i=0;i<p1.size();i++)
  {
    p1p2+=p1[i]*p2[i];
    p2p2+=p2[i]*p2[i];
  }
  //cout<<"LOOK"<<p1p2<<" "<<p2p2<<endl;
  if(abs(2*p1p2)>p2p2)
  {
    float divby=p1p2/p2p2;
    int finald;
    if(divby>0)
      finald=floor(divby+0.5);
    else
      finald=ceil(divby-0.5);
    for(int i=0;i<p1.size();i++)
    {
      p1[i]=p1[i]-finald*p2[i];
    }

  }
return p1;
}

void GaussReduce(std::vector<int> &p, std::vector<std::vector<int> > &L, std::stack<std::vector<int> > &S)
{
  bool reduceflag=true;
  //cout<<"inside gauss reduce"<<endl;
  while(reduceflag==true)
  {
    reduceflag=false;
    std::vector<std::vector<int> >::iterator it;
    for(it=L.begin();it!=L.end();it++)
    {
      std::vector<int> v1=reduce(p,(*it));
      if(v1!=p)
      {
        reduceflag=true;
        p=v1;
      }
    }
  }

  std::vector<std::vector<int> >::iterator it=L.begin();
  while(it!=L.end())
  {
    std::vector<int> l1=reduce((*it),p);
    if(l1!=(*it))
    {
      //cout<<"erasing value"<<endl;
      it=L.erase(it);
      S.push(l1);
    }
    else
      it++;
  }

   
}

void GaussSeive(std::vector<std::vector<int> >& B)
{
 
  //std::normal_distribution<double> distribution(n1,n2);
  std::vector<std::vector<int> > L;
  std::stack<std::vector<int> > S;
  std::vector<int> minvec;
  int min=999999;
  //std::vector<int> temp;
 // for(int i=0;i<d;i++)
   // temp.push_back(0);
  //L.push_back(temp);
  int k=0;
  time_t curr=time(NULL);
  while(curr-start<110)
  {
    //cout<<"curr-start"<<curr-start<<endl;
    std::vector<int> vnew;
    if(!S.empty())
    {
      vnew=S.top();
      S.pop();
    }
    else
    {
      vnew=SampleGauss();
    }
    
    std::vector<int> n1;
    GaussReduce(vnew,L,S);
   
    std::vector<int>::iterator it;
  	if(dist(vnew)==0)
  	{
    	k++;
    	//cout<<"increased k to"<<k<<endl;
  	}
    else
    {
      L.push_back(vnew);
      //cout<<"added to L"<<endl;
    }
    curr=time(NULL);
  
 
  
 
  }
   for(int i=0;i<L.size();i++)
  {
   
  	if(dist(L[i])<min)
  	{
  		min=dist(L[i]);
  		minvec=L[i];
  	}
}
    //cout<<"Distance="<<min<<endl;
	int vectsmallind=0;
    long vectdist=dist(B[0]);
    for(int w=1;w<n;w++)
    {
    	if(dist(B[w])<vectdist)
    	{
    		vectdist=dist(B[w]);
    		vectsmallind=w;
    	}

      
    }
   

 if(min<vectdist)
 {
    cout << "[";
    for(int j=0;j<minvec.size();j++)
   {
   	if(j!=minvec.size()-1)
      cout << minvec[j] << " ";
  	else
  		cout << minvec[j];
    }
    cout << "]";
 }
 else
 {
 	cout << "[";
    for(int j=0;j<B[vectsmallind].size();j++)
   {
   	if(j!=B[vectsmallind].size()-1)
      cout << B[vectsmallind][j] << " ";
  	else
  		cout << B[vectsmallind][j];
    }
    cout << "]";

 }
  


}



int main(int argc, char *argv[])
{
  start=time(NULL);
  ifstream input_file(argv[2]);
  if (input_file.is_open()) {
    input_file >> B1;
    input_file.close();
  } else {
    cin >> B1;
  }
  ks.Init(B1);

  ifstream ifile;
  ifile.open(argv[1]);
  if(ifile.is_open())
  {
    string line;
    
    std::vector<std::vector<int> > B;
    char *temp;
    getline(ifile,line);
    temp = new char[line.size()+1];
    strcpy(temp,line.c_str());
    char *pch;
    pch = strtok(temp," ");
    n = atoi(pch);
    pch = strtok(NULL," \n");
    d = atoi(pch);
    delete [] temp;
    temp = NULL;

    //while(getline(ifile,line))
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
      B.push_back(tmpv);
    }
   
   GaussSeive(B);


  }
  else
  {
    cout << "Cannot open input file" << endl;
  }
  return 0;
}





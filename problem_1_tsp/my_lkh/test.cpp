//#include<random>
#include<iostream>
#include<cstdlib>
#include<ctime>

using namespace std;

int main(){
  srand((int)time(NULL));
  for(int i=0;i<20;i++){
  cout<<rand() % 100<<endl;
  }
}

#ifndef _TM_CIRCUIT_H_
#define _TM_CIRCUIT_H_
#include <vector>
#include "../aig/aigCircuit.h"

using namespace std;

class TmGate : public vector<AigIndex>    //for fanin data
{
private:
   unsigned  _truth;   //Here truth must be in 4-var
public:
   bool      isPi() const { return empty() && _truth == 0xAAAA; }
   unsigned  getTruth() const { return _truth; }
   
   TmGate() {;}
   TmGate( const vector<AigIndex> &fanins, unsigned truth )
      : vector<AigIndex> ( fanins ), _truth( truth ) {;}
};

class TmCircuit : public vector<TmGate>  //for gates
{
public:
   AigIndex getPi( unsigned index ) const { return _piList[index]; }
   AigIndex getPo( unsigned index ) const { return _poList[index]; }
   unsigned getPiNum() const { return _piList.size(); }
   unsigned getPoNum() const { return _poList.size(); }
   void addGate( const vector<AigIndex> &fanins, unsigned truth );
   void addPi();
   void addPo( AigIndex po );
   
   void mapFrom( const AigCircuit &cir );
private:
   vector<AigIndex> _piList;
   vector<AigIndex> _poList;
};

#endif

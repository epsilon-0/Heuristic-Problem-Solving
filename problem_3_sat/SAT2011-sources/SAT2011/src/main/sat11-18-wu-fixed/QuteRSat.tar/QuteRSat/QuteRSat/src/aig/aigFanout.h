#ifndef _AIG_FANOUT_H_
#define _AIG_FANOUT_H_
#include "../aig/aigCircuit.h"

class AigFanout : public vector< vector<unsigned> >
{
public:
   void setFanout( const AigCircuit &cir );
};

class AigFanoutNum : public vector<unsigned>
{
public:
   void setFanoutNum( const AigCircuit &cir );
};

#endif

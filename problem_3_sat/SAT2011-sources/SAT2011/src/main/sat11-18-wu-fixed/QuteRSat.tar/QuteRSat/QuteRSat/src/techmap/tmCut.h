#ifndef _TM_CUT_H_
#define _TM_CUT_H_
#include "../aig/aigCircuit.h"

struct TmCut
{
   unsigned char _size;
   unsigned _signature;
   unsigned _truth;
   unsigned _nodes[4];
  
   bool operator == ( const TmCut &cut2 ) const;
   void setSignature();
};

class TmCutManager
{
public:
   TmCutManager( const AigCircuit &cir );
   ~TmCutManager();
   void setCuts();
   void setCut( unsigned index );
   const vector<TmCut> &getCuts( unsigned cutSizeDec1, unsigned index ) const { return _cuts[cutSizeDec1][index]; }
private:
   const AigCircuit &_cir;
   vector<TmCut> *_cuts[5];
   
   bool setNewCut( TmCut &newCut, const TmCut &cut1, const TmCut &cut2, bool sign1, bool sign2 );
   void addNewCut( TmCut &newCut, vector<TmCut> &cuts );
};

#endif

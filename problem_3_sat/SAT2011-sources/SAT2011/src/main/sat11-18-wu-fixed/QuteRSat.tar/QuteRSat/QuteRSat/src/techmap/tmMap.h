#ifndef _TM_MAP_H_
#define _TM_MAP_H_
#include "../aig/aigFanout.h"
#include "../truth/truthCnf.h"
#include "../techmap/tmCut.h"
#include "../techmap/tmCircuit.h"
#include "../util/utilMark.h"

struct TmChoice
{
  double        _cost;
  unsigned      _cutSize : 24;
  unsigned      _cutIndex : 8; 
};

class TmMap
{
protected:
   const AigCircuit   &_cir;
   const TruthToCnf   &_truthToCnf;
   AigFanoutNum        _fanoutNum;
   TmCutManager        _tmCutMan;
   vector<TmChoice>    _choices;
   vector<AigIndex>    _links, _fanins;
   vector<unsigned>    _gstack, _refs;
   UtilMark            _marks;
   vector<AigIndex>   *_bigAndFanins;
   
   inline double getCost( unsigned truth, unsigned varNum ) const;
   inline double getCost( const TmCut &cut ) const;
   inline double getAndCost() const;
   void setBigAnd( unsigned index );
   void collectBigAnd();
   void setChoices();
   void markChoices();
   void optimizeChoices();
   void decRef( unsigned index );
public:
   bool _collectBigAnd;
   
   TmMap( const AigCircuit &cir, const TruthToCnf &toCnf  );
   ~TmMap();
   void mapTo( TmCircuit &cir );
};

#endif


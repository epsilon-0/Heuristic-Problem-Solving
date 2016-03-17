#ifndef _TM_SAT_
#define _TM_SAT_
#include "../util/utilMark.h"
#include "../truth/truthCnf.h"
#include "tmCircuit.h"

class Solver;

class TmSat
{
public:
   TmSat( const TmCircuit &cir, const TruthToCnf &toCnf, unsigned seed = 0 )
      : _seed( seed ), _cir( cir ), _truthToCnf( toCnf ) {; }
   int solve();
   int  solveDirect();
   const vector<unsigned> &getPiSolution() { return _piSolution; }
   unsigned _seed;
protected:
   struct GateClause { 
      unsigned _gateIndex;
      unsigned _clauseIndex;
      
      GateClause( unsigned gi = 0, unsigned ci = 0 ) 
         : _gateIndex( gi ), _clauseIndex( ci ) {;}
   };
   
   const TmCircuit  &_cir;
   const TruthToCnf &_truthToCnf;
   bool                  _sat;
   unsigned              _addNum;
   vector<unsigned>      _simData;
   vector<unsigned>      _simReasons;
   vector<unsigned>      _clauseTrans;
   vector<unsigned>      _varLinks;
   vector<unsigned>      _refModel;
   vector<unsigned>      _piSolution;
   vector<unsigned char> _polarity;
   vector<GateClause>    _addClauses;
   vector<unsigned>      _addXorClauses;

   vector<AigIndex>      _assumeConstGate;
   
   void init();
   void simulation( const vector<unsigned> &pattern );
   void setPolarity();
   void reportSim();
   void addRemain();
   void addClauses( Solver &s );
   void addXorClauses( Solver &s );
   void coverBinaryClauses();
   void setPiSolution( Solver &s );
   static unsigned isXorGate( unsigned truth );
   static unsigned isXnorGate( unsigned truth );

   void findConstRelation( Solver &s );
};

#endif


#ifndef _CNF_TO_AIG_
#define _CNF_TO_AIG_
#include <stdint.h>
#include <limits.h>
#include <vector>
#include <dense_hash_set>
#include "../aig/aigHash.h"
#include "../aig/aigLevel.h"
#include "../util/utilMark.h"

struct Clause
{
   unsigned _size      : 30;
   bool     _extracted : 1;
   bool     _covered   : 1;
   uint32_t _literals[0];
   
   inline bool operator == ( const Clause &b ) const;
   static inline Clause *newClause( unsigned litNum );
};
   
struct ClauseEqual
{
   inline bool operator() ( Clause * const &a, Clause * const &b ) const;
};
   
struct ClauseHashFunc
{
   inline size_t operator() ( Clause * const &cls ) const;
};

struct TwoLiteral
{
   union
   {
      uint64_t _data;
      uint32_t _literals[2];
   };
   std::vector<Clause*> _clauses;
};

struct TwoLiteralEqual
{
   inline bool operator() ( TwoLiteral * const &a, TwoLiteral * const &b ) const;
};

struct TwoLiteralHashFunc
{
   inline size_t operator() ( TwoLiteral * const &a ) const;
};

struct Gate
{
   enum GateType
   {
      INV = 0,
      AND,
      XOR,
      ITE,
   };
   unsigned _size     : 30;
   unsigned _covered  : 1;
   unsigned _backedge : 1;
   GateType _type;
   uint32_t _lhs;
   uint32_t *_relateVar;
   Clause   *_clauses[0];
   static inline Gate *newGate( unsigned clauseNum );
};

struct Variable
{
   bool  _defined  : 1;
   bool  _input    : 1;
   bool  _leaf     : 1;
   bool  _root     : 1;
   bool  _used     : 1;
   bool  _covered  : 1;
   bool  _unit     : 1;
   bool  _polarity : 1;
   uint32_t      _mark;
   uint32_t      _idx;
   Gate* _gate;
   
   Variable();
};

class CnfToAig
{
protected:
   bool      _unsat;
   double    _coverRate;
   uint32_t  _globalMark;
   unsigned  _varNum, _invNum, _andNum, _andLength, _xorNum, _xorLength, _iteNum;
   unsigned  _breakNum;
   Variable *_variables;
   Clause   *_tempClause;
   TwoLiteral _tempTwoLiteral;
   vector<Clause*>  _clauses, _tempClauses; 
   vector<uint32_t> _literals, _units, _stack;
   vector<Gate*> _directGates, _undirectGates;
   google::dense_hash_set<Clause*, ClauseHashFunc, ClauseEqual> *_binaryClauseHash, *_clauseHash;
   google::dense_hash_set<TwoLiteral*, TwoLiteralHashFunc, TwoLiteralEqual> *_twoLiteralHash;
   AigHash     _aigHash;
   UtilMark    _marks;
   AigCircuit &_circuit;
   vector<unsigned char>  _cirConsts;
   vector<AigIndex>       _fanins;
   vector<AigIndex>      &_links;
   
   static vector<Gate*> *_watchLists;
   static AigLevel      *_aigLevels;

   void initHash();
   void freeHash();
   void freeGate();
   void extractGate();
   void extractInv();
   void extractAnd();
   void extractXor();
   void extractIte();
   Clause *findTenaryClause( uint32_t a, uint32_t b, uint32_t c );
   bool findIte( uint32_t lhsLit, uint32_t condLit, uint32_t thenLit );
   void setDirection();
   void breakCycle();
   void breakCycleDfs( unsigned root );
   void makeUnDirectGateToDirect();
   void coverGate();
   void coverGateDfs( unsigned root );
   void buildPi( unsigned root );
   void buildGate( unsigned root );
   AigIndex buildAndGate();
   AigIndex buildXorGate();
   AigIndex pushPi();
   AigIndex pushNode( AigIndex a, AigIndex b );
   void buildClauses();
   void buildClause( const Clause *cls );
   void setPo();
   
   static bool sortVar( uint32_t a, uint32_t b );
   static bool sortLevel( AigIndex a, AigIndex b );
public:
   
   CnfToAig( unsigned varNum, AigCircuit &cir, vector<AigIndex> &links );
   ~CnfToAig();
   bool isUnSat() const;
   double getCoverRate() const { return _coverRate; }
   void addClause( const std::vector<uint32_t> &cls );
   void insertTwoLiteralHash( uint32_t l0, uint32_t l1, Clause *cls );
   void run();
   bool verify( const vector<unsigned>& varValue ) const;
};

#endif


#include <cassert>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <string>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <fstream>
#include "cnfToAig.h"

#define RotateLeft32(x,n) (( x << n ) | ( x >> (32-n) ))

using namespace std;
using namespace google;

vector<Gate*> *CnfToAig::_watchLists = NULL;
AigLevel *CnfToAig::_aigLevels = NULL;

/*static inline uint32_t fmix32( uint32_t h )
{
   h ^= h >> 16;
   h *= 0x85ebca6b; 
   h ^= h >> 13;
   h *= 0xc2b2ae35;
   h ^= h >> 16;
   return h;
}

static inline void bmix32( uint32_t & h1, uint32_t & k1, uint32_t & c1, uint32_t & c2 )
{
   k1 *= c1;
   k1 = RotateLeft32(k1,11);
   k1 *= c2;
   h1 ^= k1;
   h1 = h1*3+0x52dce729;
   c1 = c1*5+0x7b7d159c;
   c2 = c2*5+0x6bce6396;
}

static uint32_t MurmurHash3_32( const uint32_t * data, unsigned length, uint32_t seed )
{
   uint32_t h1 = ( 0x971e137b ^ seed );
   uint32_t c1 = 0x95543787, c2 = 0x2ad7eb25;
   // body
   const uint32_t * const pend = data + length;
   for( const uint32_t * ptr = data; ptr != pend; ++ptr )
   {
      uint32_t k1 = *ptr;
      bmix32(h1,k1,c1,c2);
   }
   // tail
   uint32_t k1 = 0;
   bmix32(h1,k1,c1,c2);
   // finalization
   h1 ^= length;
   h1 = fmix32(h1);
   return h1;
}*/

static inline uint32_t countOnes( uint32_t word )
{
    word = (word & 0x55555555) + ((word>>1) & 0x55555555);
    word = (word & 0x33333333) + ((word>>2) & 0x33333333);
    word = (word & 0x0F0F0F0F) + ((word>>4) & 0x0F0F0F0F);
    word = (word & 0x00FF00FF) + ((word>>8) & 0x00FF00FF);
    return (word & 0x0000FFFF) + (word>>16);
}

static const unsigned primes[10] = {
  2000000011,
  2000000033,
  2000000063,
  2000000087,
  2000000089,
  2000000099,
  2000000137,
  2000000141,
  2000000143,
  2000000153,
};
   
Variable::Variable()
{
   memset( this, 0, sizeof(Variable) );
}

bool
Clause::operator == ( const Clause &b ) const
{
   if( _size != b._size ) return false;
   const uint32_t *lit = _literals, *blit = b._literals;
   const uint32_t * const litend = lit + _size;
   for( ; lit != litend; ++lit, ++blit )
      if( *lit != *blit ) return false;
   return true;
}

Clause *
Clause::newClause( unsigned litNum )
{
   Clause *cls = reinterpret_cast<Clause*>( malloc( sizeof( Clause ) + litNum  * sizeof( uint32_t ) ) );
   memset( cls, 0, sizeof(Clause) );
   cls->_size = litNum;
   return cls;
}

Gate *
Gate::newGate( unsigned clauseNum )
{
   Gate *g = reinterpret_cast<Gate*>( malloc( sizeof( Gate ) + clauseNum  * sizeof( Clause  * ) ) );
   memset( g, 0, sizeof(Gate) );
   g->_size = clauseNum;
   return g;
}

bool 
ClauseEqual::operator () ( Clause * const &a, Clause * const &b ) const
{
   return ( a == b ) || ( a && b && *a == *b );
}

size_t
ClauseHashFunc::operator () ( Clause * const &cls ) const
{
   //return MurmurHash3_32( cls->_literals, cls->_size, 13 );
   unsigned i = 0, res = 0;
   uint32_t *lit;
   const uint32_t *lend = cls->_literals + cls->_size;
   
   for( lit = cls->_literals; lit != lend; ++lit )
   {
      res += unsigned(*lit) * primes [i++];
      if(i > 9) i = 0;
   }
   return res;
}


bool 
TwoLiteralEqual::operator () ( TwoLiteral * const &a, TwoLiteral * const &b ) const
{
   return ( a == b ) || ( a && b && a->_data == b->_data );
}

size_t
TwoLiteralHashFunc::operator () ( TwoLiteral * const &a ) const
{
   //return MurmurHash3_32( cls->_literals, cls->_size, 13 );
   return unsigned(a->_literals[0]) * primes [0] + unsigned(a->_literals[1]) * primes [1];
}


CnfToAig::CnfToAig( unsigned varNum, AigCircuit &cir, vector<AigIndex> &links )
   : _unsat( false ), _globalMark(0), _varNum( varNum ), _invNum( 0 ),
     _andNum( 0 ), _andLength( 0 ), _xorNum( 0 ), _xorLength( 0 ), _iteNum( 0 ),
     _breakNum( 0 ), _binaryClauseHash( NULL ), _circuit( cir ), _links( links )
{
   _variables = new Variable[ varNum ];
   _tempClause = Clause::newClause( 16 );
   _tempClauses.reserve( 128 );
   initHash();
}

CnfToAig::~CnfToAig()
{
   delete [] _variables;
   free( _tempClause );
   for( vector<Clause*>::const_iterator cvi = _clauses.begin();
        cvi != _clauses.end(); ++cvi )
      free( *cvi );
}

void
CnfToAig::initHash()
{
   _binaryClauseHash = new google::dense_hash_set<Clause*, ClauseHashFunc, ClauseEqual>;
   _clauseHash = new google::dense_hash_set<Clause*, ClauseHashFunc, ClauseEqual>;
   _twoLiteralHash = new google::dense_hash_set<TwoLiteral*, TwoLiteralHashFunc, TwoLiteralEqual>;
   _clauseHash->set_empty_key( NULL );
   _binaryClauseHash->set_empty_key( NULL );
   _twoLiteralHash->set_empty_key( NULL );
}

void
CnfToAig::freeHash()
{
   if( _binaryClauseHash == NULL ) return;
   delete _binaryClauseHash;
   delete _clauseHash;
   for( google::dense_hash_set<TwoLiteral*,TwoLiteralHashFunc,TwoLiteralEqual>::iterator iter = _twoLiteralHash->begin();
         iter != _twoLiteralHash->end(); ++iter ) 
      delete *iter;
   delete _twoLiteralHash;
   _binaryClauseHash = NULL;
}

void
CnfToAig::freeGate()
{
   vector<Gate*>::const_iterator vi;
   for( vi = _directGates.begin(); vi != _directGates.end(); ++vi )
      free( *vi );
   for( vi = _undirectGates.begin(); vi != _undirectGates.end(); ++vi )
      free( *vi );
   _directGates.clear();
   _undirectGates.clear();
}

bool
CnfToAig::isUnSat() const
{
   return _unsat;
}

void
CnfToAig::addClause( const vector<uint32_t> &cls )
{
   _literals = cls;
   if( _literals.size() > 1 )
   {
      sort( _literals.begin(), _literals.end() );
      vector<uint32_t>::iterator preLit = _literals.begin();
      for( vector<uint32_t>::const_iterator lit = _literals.begin() + 1;
           lit != _literals.end(); ++lit )
         if( *lit == *preLit );
         else  if( *lit == ( (*preLit) ^ 1 ) )
         {
            _unsat = true;
            return;
         }
         else *(++preLit) = *lit;
      ++preLit;
      _literals.resize( preLit - _literals.begin() );
   }
   if( _literals.empty() )
   {
      _unsat = true;
      return;
   }
   const uint32_t lit0 = _literals[0];
   if( _literals.size() == 1 )
   {
      Variable &var = _variables[lit0>>1];
      if( var._unit )
      {
         if( var._polarity != ( lit0 & 1 ) )
            _unsat = true;
         return;
      }
      var._used = true;
      var._unit = true;
      var._polarity = lit0 & 1;
      _units.push_back( lit0 );
      return;
   }
   for( vector<uint32_t>::const_iterator lit = _literals.begin();
        lit != _literals.end(); ++lit )
   {
      assert( (*lit>>1) < _varNum );
      _variables[*lit>>1]._used = true;
   }
   const uint32_t lit1 = _literals[1];
   Clause *newcls = Clause::newClause( _literals.size() );
   memcpy( newcls->_literals, &_literals[0], _literals.size() * sizeof(uint32_t) );
   if( _literals.size() == 2 )
   {
      if( !_binaryClauseHash->insert( newcls ).second ) free( newcls );
      else _clauses.push_back( newcls );
      return;
   }
   if( !_clauseHash->insert( newcls ).second )
   {
      free( newcls );
      return;
   }
   _clauses.push_back( newcls );
   if( _literals.size() != 3 ) return;
   const uint32_t lit2 = _literals[2];
   insertTwoLiteralHash( lit0, lit1, newcls );
   insertTwoLiteralHash( lit0, lit2, newcls );
   insertTwoLiteralHash( lit1, lit2, newcls );
}

void
CnfToAig::insertTwoLiteralHash( uint32_t l0, uint32_t l1, Clause *cls )
{
   TwoLiteral *newData = new TwoLiteral;
   newData->_literals[0] = l0;
   newData->_literals[1] = l1; 
   TwoLiteral *curData = *(_twoLiteralHash->insert( newData ).first);
   curData->_clauses.push_back( cls );
   if( curData != newData ) delete newData;
}

void
CnfToAig::extractInv()
{
   dense_hash_set<Clause*, ClauseHashFunc, ClauseEqual>::const_iterator hi1, hi2;
   
   _tempClause->_size = 2;
   for( dense_hash_set<Clause*, ClauseHashFunc, ClauseEqual>::const_iterator hi1 = _binaryClauseHash->begin();
        hi1 != _binaryClauseHash->end(); ++hi1 )
   {
      assert( (*hi1)->_size == 2 );
      if( (*hi1)->_extracted ) continue;
      _tempClause->_literals[0] = (*hi1)->_literals[0] ^ 1;
      _tempClause->_literals[1] = (*hi1)->_literals[1] ^ 1;
      hi2 = _binaryClauseHash->find( _tempClause );
      if( hi2 == _binaryClauseHash->end() ) continue;
      Gate *invGate = Gate::newGate( 2 );
      (*hi1)->_extracted = true;
      (*hi2)->_extracted = true;
      invGate->_clauses[0] = *hi1;
      invGate->_clauses[1] = *hi2;
      invGate->_type = Gate::INV;
      ++_invNum;
      _undirectGates.push_back( invGate );
   }
}

void
CnfToAig::extractAnd()
{
   const uint32_t *lit, *otherLit;
   dense_hash_set<Clause*, ClauseHashFunc, ClauseEqual>::const_iterator hi, hi2;
   
   _tempClause->_size = 2;
   for( hi = _clauseHash->begin(); hi != _clauseHash->end(); ++hi )
   {
      Clause * const cls = *hi;
      assert( cls->_size > 2 );
      const uint32_t *lend = cls->_literals + cls->_size;
      for( lit = cls->_literals; lit != lend; ++lit )
      {
         const uint32_t invLit = (*lit) ^ 1;
         _tempClause->_literals[1] = invLit;
         _tempClauses.resize( 1 );
         for( otherLit = cls->_literals; *otherLit != *lit; ++otherLit )
         {
            _tempClause->_literals[0] = *otherLit ^ 1;
            if( ( hi2 = _binaryClauseHash->find( _tempClause ) )  == _binaryClauseHash->end() ) break;
            _tempClauses.push_back( *hi2 );
         }
         assert( otherLit < lend );
         if( *otherLit != *lit ) continue;
         ++otherLit;
         _tempClause->_literals[0] = invLit;
         for( ; otherLit != lend; ++otherLit )
         {
            _tempClause->_literals[1] = *otherLit ^ 1;
            if( ( hi2 = _binaryClauseHash->find( _tempClause ) ) == _binaryClauseHash->end() ) break;
            _tempClauses.push_back( *hi2 );
         }
         if( otherLit != lend ) continue;
         _tempClauses[0] = cls;
         ++_andNum;
         _andLength += cls->_size;
         Gate *andGate = Gate::newGate( _tempClauses.size() );
         memcpy( andGate->_clauses, &_tempClauses[0], _tempClauses.size()*sizeof(Clause*) );
         for( vector<Clause*>::const_iterator cvi = _tempClauses.begin();
              cvi != _tempClauses.end(); ++cvi )
              (*cvi)->_extracted = true;
         andGate->_lhs = *lit;
         andGate->_type = Gate::AND;
         _variables[(*lit)>>1]._gate = andGate;
         _directGates.push_back( andGate );
      }
   }
}

void
CnfToAig::extractXor()
{
   unsigned signs;
   uint32_t *lit;
   dense_hash_set<Clause*, ClauseHashFunc, ClauseEqual>::const_iterator hi2;
   
   for( dense_hash_set<Clause*, ClauseHashFunc, ClauseEqual>::const_iterator hi = _clauseHash->begin();
        hi != _clauseHash->end(); ++hi )
   {
      Clause * const cls = *hi;
      if( cls->_size > 16 ) continue;
      const uint32_t *lend = cls->_literals + cls->_size;
      for( lit = cls->_literals + 1; lit != lend; ++lit )
         if( (*lit) & 1 ) break;
      if( lit != lend ) continue;  // focus on the bottom clause of XOR
      _tempClauses.clear();
      _tempClause->_size = cls->_size;
      const unsigned clauseNum = 1 << cls->_size;
      for( signs = 3; signs < clauseNum; ++signs )
      {
         if( countOnes(signs) & 1 ) continue;
         memcpy( _tempClause->_literals, cls->_literals, cls->_size*sizeof(uint32_t) );
         lit = _tempClause->_literals;
         for( unsigned sign = signs; sign != 0; sign >>= 1, ++lit )
         {
            assert( lit < _tempClause->_literals + _tempClause->_size );
            if( ( sign & 1 ) ) *lit = (*lit) ^ 1;
         }
         if( ( hi2 = _clauseHash->find( _tempClause ) ) == _clauseHash->end() )
            break;
         _tempClauses.push_back( *hi2 );
      }
      if( signs != clauseNum ) continue;
      _tempClauses.push_back( cls );
      ++_xorNum;
      _xorLength += cls->_size;
      Gate *xorGate = Gate::newGate( _tempClauses.size() );
      memcpy( xorGate->_clauses, &_tempClauses[0], _tempClauses.size()*sizeof(Clause*) );
      xorGate->_type = Gate::XOR;
      for( vector<Clause*>::const_iterator cvi = _tempClauses.begin();
           cvi != _tempClauses.end(); ++cvi )
           (*cvi)->_extracted = true;
      _undirectGates.push_back( xorGate );
   }
}

Clause *
CnfToAig::findTenaryClause( uint32_t a, uint32_t b, uint32_t c )
{
   _tempClause->_size = 3;
   _tempClause->_literals[0] = a;
   if( a < b )
   {
      if( c < a )
      { 
         _tempClause->_literals[0] = c;
         c = a;
      }
   }
   else if( b < c )
   {
      _tempClause->_literals[0] = b;
      b = a;
   }
   else
   { 
      _tempClause->_literals[0] = c;
      c = a;
   }
   _tempClause->_literals[1] = b;
   if( c < b )
   {
      _tempClause->_literals[1] = c;  
      c = b;
   }
   _tempClause->_literals[2] = c;
   dense_hash_set<Clause*, ClauseHashFunc, ClauseEqual>::const_iterator hi = _clauseHash->find( _tempClause );
   if( hi == _clauseHash->end() ) return NULL;
   return *hi;
}

bool
CnfToAig::findIte( uint32_t lhsLit, uint32_t condLit, uint32_t thenLit )
{
   Clause *cls = findTenaryClause( lhsLit^1, condLit, thenLit^1 );
   if( cls == NULL ) return false;
   _tempClauses.resize( 1 );
   _tempClauses.push_back( cls );
   condLit = condLit ^ 1;
   uint32_t lit0 = lhsLit, lit1 = condLit;
   if( lit0 > lit1 ) lit0 = condLit, lit1 = lhsLit;
   _tempTwoLiteral._literals[0] = lit0;
   _tempTwoLiteral._literals[1] = lit1;
   dense_hash_set<TwoLiteral*, TwoLiteralHashFunc, TwoLiteralEqual>::const_iterator hi = _twoLiteralHash->find( &_tempTwoLiteral );
   if( hi == _twoLiteralHash->end() ) return false;
   uint32_t elseLit;
   for( vector<Clause*>::const_iterator cvi = (*hi)->_clauses.begin(); cvi != (*hi)->_clauses.end(); ++cvi )
   {
      elseLit = (*cvi)->_literals[0];
      if( elseLit == lit0 )
      {
         elseLit = (*cvi)->_literals[1];
         if( elseLit == lit1 )
            elseLit = (*cvi)->_literals[2];
      }
      if( elseLit == thenLit );  // can reduce to INV ?
      if( elseLit == (thenLit ^ 1) ) continue;   //XOR
      cls = findTenaryClause( lhsLit^1, condLit, elseLit^1 );
      if( cls == NULL ) continue;
      _tempClauses.push_back( (*cvi) );
      _tempClauses.push_back( cls );
      return true;
   }
   return false;
}

void
CnfToAig::extractIte()
{
   unsigned i, j, k, lhsLit, condLit, thenLit;
   for( dense_hash_set<Clause*, ClauseHashFunc, ClauseEqual>::const_iterator hi = _clauseHash->begin();
        hi != _clauseHash->end(); ++hi )
   {
      Clause *cls = *hi;
      if( cls->_size != 3 ) continue;
      for( i = 0; i < 3; ++i )
      {
         lhsLit = cls->_literals[i];
         if( lhsLit & 1 ) continue;
         for( j = 0; j < 3; ++j )
         {
            condLit = cls->_literals[j];
            if( j == i || ( condLit & 1 ) ) continue;
            thenLit = 0;
            for( k = 0; k < 3; ++k )
               if( k != i && k != j )
               {
                  thenLit = cls->_literals[k];
                  break;
               }
            assert( thenLit );
            if( !findIte( lhsLit, condLit, thenLit ) ) continue;
            _tempClauses[0] = cls;
            assert( _tempClauses.size() == 4 );
            ++_iteNum;
            Gate *iteGate = Gate::newGate( _tempClauses.size() );
            memcpy( iteGate->_clauses, &_tempClauses[0], _tempClauses.size()*sizeof(Clause*) );
            for( vector<Clause*>::const_iterator cvi = _tempClauses.begin();
                 cvi != _tempClauses.end(); ++cvi )
               (*cvi)->_extracted = true;
            iteGate->_lhs = lhsLit;
            iteGate->_type = Gate::ITE;
            _variables[lhsLit>>1]._gate = iteGate;
            _directGates.push_back( iteGate );
            //break;
         }
         //if( j != 3 ) break;
      }
   }
}

void
CnfToAig::extractGate()
{
   cout << "c Find Units : " << setw(10) << _units.size() << endl;
   extractInv();
   cout << "c Find Invs  : " << setw(10) << _invNum << endl;
   extractAnd();
   cout << "c Find Ands  : " << setw(10) << _andNum << " AvgFaninNum: " << ( _andLength - _andNum ) / (double)_andNum << endl;
   extractXor();
   cout << "c Find Xors  : " << setw(10) << _xorNum << " AvgFaninNum: " << ( _xorLength - _xorNum ) / (double)_xorNum << endl;
   extractIte();
   cout << "c Find Ite   : " << setw(10) << _iteNum << endl;
}

void
CnfToAig::setDirection()
{
   const Variable * const vend = _variables + _varNum;
   Variable * varPtr = _variables + 1;
   
   
   for( ; varPtr != vend; ++varPtr )
   {
      if( varPtr->_gate == NULL ) continue;
      varPtr->_defined = true;
      varPtr->_root = true;
   }
   for( vector<Gate*>::const_iterator vi = _directGates.begin();
        vi != _directGates.end(); ++vi )
   {
      const uint32_t lhsVar = (*vi)->_lhs >> 1;
      const Clause * const cls = (*vi)->_clauses[0];
      assert( _variables[lhsVar]._defined );
      const uint32_t * const lend = cls->_literals + cls->_size;
      for( const uint32_t *lit = cls->_literals; lit != lend; ++lit )
      {
         const uint32_t var = (*lit) >> 1;
         if( var == lhsVar ) continue;
         _variables[var]._root = false;
      }
      if( (*vi)->_type != Gate::ITE ) continue;
      const Clause * const cls1 = (*vi)->_clauses[2];
      const uint32_t * const lend1 = cls1->_literals + cls1->_size;
      for( const uint32_t *lit = cls1->_literals; lit != lend1; ++lit )
      {
         const uint32_t var = (*lit) >> 1;
         if( var == lhsVar ) continue;
         _variables[var]._root = false;
      }
   }
   
   makeUnDirectGateToDirect();
   
   for( vector<Gate*>::const_iterator vi = _undirectGates.begin();
        vi != _undirectGates.end(); ++vi )
   {
      const unsigned var = (*vi)->_lhs;
      if( var == 0 ) continue;
      if( !_variables[var]._defined ) continue;
      _variables[var]._root = true;
   }
   for( vector<Gate*>::const_iterator vi = _undirectGates.begin();
        vi != _undirectGates.end(); ++vi )
   {
      const unsigned lhsVar = (*vi)->_lhs;
      if( lhsVar == 0 ) continue;
      const Clause * const cls = (*vi)->_clauses[0];
      const uint32_t * const lend = cls->_literals + cls->_size;
      for( const uint32_t *lit = cls->_literals; lit != lend; ++lit )
      {
         const unsigned var = (*lit) >> 1;
         if( var == lhsVar )
         {
            (*vi)->_lhs = *lit;  //important to reset lhs
            continue;
         }
         _variables[var]._root = false;
      }
      assert( lhsVar == ( (*vi)->_lhs >> 1 ) );
   }
   breakCycle();
}

void
CnfToAig::breakCycle()
{
   assert( _stack.empty() );
   unsigned rootNum = 0, uncoverNum = 0, coverNum = 0, undefNum = 0;
   for( unsigned root = _varNum - 1; root > 0; --root )
   //for( unsigned root = 1; root < _varNum; ++root )
   {
      Variable &rootVar = _variables[root];
      assert( rootVar._mark == 0 || rootVar._mark == 2147483648 );
      //if( !rootVar._defined || rootVar._mark || !rootVar._root ) continue;
      if( !rootVar._defined || rootVar._mark ) continue;
      breakCycleDfs( root );
      if( rootVar._root ) ++rootNum;
   }
   for( unsigned root = _varNum - 1; root > 0; --root )
   {
      Variable &rootVar = _variables[root];
      assert( rootVar._mark == 0 || rootVar._mark == 2147483648 );
      if( !rootVar._defined ) { ++undefNum; continue; }
      if( rootVar._mark ) { ++coverNum; continue; }
      //breakCycleDfs( root );
      ++uncoverNum;
   }
   for( unsigned root = 1; root < _varNum; ++root )
      _variables[root]._mark = 0;
   cout << "c Break Cycle : " << _breakNum << endl;
   cout << "c Total Root : " << rootNum << " Undef Var: " << undefNum << endl;
}

void
CnfToAig::breakCycleDfs( unsigned root )
{
   /*_stack.push_back( root );
   _variables[root]._mark = 1;
   
   while( !_stack.empty() )
   {
      root = _stack.back();
      _stack.pop_back();
      Variable &rootVar = _variables[root];
      if( rootVar._mark == 3 ) continue;  // already traveled
      assert( rootVar._defined );
      if( rootVar._mark == 2 ) //travel back and pop
      {
         rootVar._mark = 3;
         continue;
      }
      assert( rootVar._mark == 1 );
      assert( rootVar._gate != NULL );
      cycle = false;
      const Clause * const cls =  rootVar._gate->_clauses[0];
      const uint32_t * const lend = cls->_literals + cls->_size;
      const unsigned orgSize = _stack.size();
      _stack.push_back( root );
      for( const uint32_t *lit = cls->_literals; lit != lend; ++lit )
      {
         const uint32_t var = (*lit) >> 1;
         Variable &inputVar = _variables[var];
         if( inputVar._mark == 2 )
         {
            cycle = true;
            break;
         }
         if( inputVar._mark || !inputVar._defined ) continue;
         inputVar._mark = 1;
         _stack.push_back( var );
      }
      if( !cycle && rootVar._gate->_type == Gate::ITE )
      {
         const Clause * const cls1 = rootVar._gate->_clauses[2];
         const uint32_t * const lend1 = cls1->_literals + cls1->_size;
         for( const uint32_t *lit = cls1->_literals; lit != lend1; ++lit )
         {
            const uint32_t var = (*lit) >> 1;
            Variable &inputVar = _variables[var];
            if( inputVar._mark == 2 )
            {
               cycle = true;
               break;
            }
            if( inputVar._mark || !inputVar._defined ) continue;
            inputVar._mark = 1;
            _stack.push_back( var );
         }
      }
      if( !cycle )
      {
         rootVar._mark = 2;
         continue;
      }
      // break cycle and recover
      ++_breakNum;
      rootVar._defined = false;
      for( vector<uint32_t>::const_iterator cvi = _stack.begin() + orgSize;
           cvi != _stack.end(); ++cvi )
         _variables[*cvi]._mark = 0;
      _stack.resize( orgSize );
   }*/

   unsigned cycleVar;
   
   assert( _stack.empty() );
   const Clause * cls;
   unsigned lit;
   _stack.push_back( root );
   _variables[root]._idx = 0;
   assert( _variables[root]._mark == 0 );
   while( true )
   {
      Variable &rootVar = _variables[root];
      assert( rootVar._defined );
      assert( rootVar._gate != NULL );
      assert( _stack.back() == root );
      lit = 0;
      cls = rootVar._gate->_clauses[0];
      if( rootVar._mark < cls->_size )
         lit = cls->_literals[rootVar._mark];
      else if( rootVar._gate->_type == Gate::ITE )
      {
         const unsigned index = rootVar._mark - cls->_size;
         cls = rootVar._gate->_clauses[2];
         if( index < cls->_size )
            lit = cls->_literals[index];
      }
      if( lit == 0 ) //travel back and pop
      {
         rootVar._mark = 2147483648;
         _stack.pop_back();
         if( _stack.empty() ) break;
         root = _stack.back();
         continue;
      }
      if( rootVar._mark == 0 )
      {
         cycleVar = 0;
         const Clause * const cls =  rootVar._gate->_clauses[0];
         const uint32_t * const lend = cls->_literals + cls->_size;
         for( const uint32_t *plit = cls->_literals; plit != lend; ++plit )
         {
            const unsigned var = (*plit) >> 1;
            Variable &inputVar = _variables[var];
            if( inputVar._mark == 0 || inputVar._mark == 2147483648 ) continue;
            assert( inputVar._defined );
            if( cycleVar != 0 && inputVar._idx < _variables[cycleVar]._idx ) continue;
            cycleVar = var;
         }
         if( rootVar._gate->_type == Gate::ITE )
         {
            const Clause * const cls1 = rootVar._gate->_clauses[2];
            const uint32_t * const lend1 = cls1->_literals + cls1->_size;
            for( const uint32_t *plit = cls1->_literals; plit != lend1; ++plit )
            {
               const unsigned var = (*plit) >> 1;
               Variable &inputVar = _variables[var];
               if( inputVar._mark == 0 || inputVar._mark == 2147483648 ) continue;
               assert( inputVar._defined );
               if( cycleVar != 0 && inputVar._idx < _variables[cycleVar]._idx ) continue;
               cycleVar = var;
            }
         }
         if( cycleVar )
         {
            Variable &cVar = _variables[cycleVar];
            cVar._defined = false;
            ++_breakNum;
            assert( cVar._idx < _stack.size() );
            for( unsigned i = cVar._idx; i < _stack.size(); ++i )
               _variables[ _stack[i] ]._mark = 0;
            _stack.resize( cVar._idx );
            if( _stack.empty() ) break;
            root = _stack.back();
            continue;
         }
      }
      ++rootVar._mark;
      const unsigned var = lit >> 1;
      if( var == root ) continue;
      const Variable &litVar = _variables[var];
      if( !litVar._defined || litVar._mark == 2147483648 ) continue;
      assert( litVar._mark == 0 );
      root = var;
      _variables[root]._idx = _stack.size();
      _stack.push_back( root );
   }
/*
   for( unsigned root = 0; root < _varNum; ++root )
   {
      Variable &rootVar = _variables[root];
      assert( rootVar._mark == 0 || rootVar._mark == 2147483648 );
   }*/
}

bool
CnfToAig::sortVar( uint32_t a, uint32_t b )
{
   if( _watchLists[a].size() == _watchLists[b].size() )
      return a < b;
   return  _watchLists[a].size() < _watchLists[b].size();
}

void
CnfToAig::makeUnDirectGateToDirect()
{
   /*bool change = true;
   uint32_t lhs = 0;
   unsigned definedCount, round, num = 0;
   vector<Gate*> gates = _undirectGates;
   vector<Gate*>::iterator vi;
   vector<Gate*>::const_iterator cvi;
   
   for( round = 0; round < 100000 && change; ++round )
   {
      change = false;
      cvi = vi = gates.begin();
      for( ; cvi != gates.end(); ++cvi )
      {
         if( (*cvi)->_lhs ) continue;
         definedCount = 0;
         const Clause * const cls = (*cvi)->_clauses[0];
         const uint32_t * const lend = cls->_literals + cls->_size;
         for( const uint32_t *lit = cls->_literals; lit != lend; ++lit )
         {
            const uint32_t var = (*lit) >> 1;
            if( _variables[var]._defined ) ++definedCount;
            else lhs = var;
         }
         if( definedCount == cls->_size ) continue;
         if( definedCount + 1 != cls->_size )
         {
            *vi = *cvi;
            ++vi;
            continue;
         }
         assert( lhs != 0 );
         for( const uint32_t *lit = cls->_literals; lit != lend; ++lit )
         {
            const uint32_t var = (*lit) >> 1;
            if( var == lhs ) continue;
            _variables[var]._input = true;
         }
         _variables[lhs]._defined = true;
         _variables[lhs]._gate = *cvi;
         (*cvi)->_lhs = lhs;
         ++num;
         change = true;
      }
      gates.resize( vi - gates.begin() );
   }
   cout << "UnDirect to Direct: " << num << " Round: " << round << endl;*/
   uint32_t lhs = 0;
   unsigned i, definedCount, undefinedNum = 0;
   uint32_t *varPtr, *varPtr0, *varPtr1;
   vector<uint32_t> undefinedVars;
   vector<uint32_t>::iterator uintvi;
   _watchLists = new vector<Gate*> [_varNum];
   
   assert( _stack.empty() );
   //initial
   for( vector<Gate*>::const_iterator cvi = _undirectGates.begin();
        cvi != _undirectGates.end(); ++cvi )
   {
      //const uint32_t lhsVar = (*cvi)->_lhs >> 1;
      const Clause * const cls = (*cvi)->_clauses[0];
      const uint32_t * const lend = cls->_literals + cls->_size;
      definedCount = 0;
      for( const uint32_t *lit = cls->_literals; lit != lend; ++lit )
      {
         const uint32_t var = (*lit) >> 1;
         if( _variables[var]._defined ) ++definedCount;
         else lhs = var;
      }
      if( definedCount == cls->_size ) continue;
      if( definedCount + 1 == cls->_size )  //set Gate Direction
      {
         _variables[lhs]._defined = true;
         _variables[lhs]._gate = *cvi;
         (*cvi)->_lhs = lhs;
         _stack.push_back( lhs );
         continue;
      }
      varPtr0 = varPtr = (uint32_t*)malloc( sizeof( uint32_t ) * cls->_size );
      (*cvi)->_relateVar = varPtr;
      for( const uint32_t *lit = cls->_literals; lit != lend; ++lit, ++varPtr )
      {
         *varPtr = (*lit) >> 1;
         if( _variables[*varPtr]._defined || _variables[*varPtr]._mark ) continue;
         _variables[*varPtr]._mark = 1;
         undefinedVars.push_back( *varPtr );
      }
      const uint32_t * const vend = varPtr0 + cls->_size;
      for( varPtr = varPtr0; varPtr != vend; ++varPtr )
         if( !_variables[*varPtr]._defined )
         {
            swap( *varPtr0, *varPtr );
            ++varPtr0;
            if( varPtr0 == (*cvi)->_relateVar + 2 ) break;
         }
      assert( varPtr != vend );  
      _watchLists[(*cvi)->_relateVar[0]].push_back( *cvi );
      _watchLists[(*cvi)->_relateVar[1]].push_back( *cvi );
   }
   uintvi = undefinedVars.begin();
   for( vector<uint32_t>::const_iterator cvi = uintvi; cvi != undefinedVars.end(); ++cvi )
   {
      _variables[*cvi]._mark = 0;
      if( _variables[*cvi]._defined ) continue;
      *uintvi = *cvi;
      ++uintvi;
   }
   undefinedVars.resize( uintvi - undefinedVars.begin() );
   cout << "c UnDirect variable: " << undefinedVars.size() << endl;
   make_heap( undefinedVars.begin(), undefinedVars.end(), sortVar );
   //propagate undirect->direct
   unsigned directGateNum = 0;
   i = 0;
   while( true )
   {
      for( ; i < _stack.size(); ++i )
      {
         const uint32_t var = _stack[i];
         const vector<Gate*> &watchList = _watchLists[var];
      
         assert( _variables[var]._defined );
         for( vector<Gate*>::const_iterator cvi = watchList.begin();
              cvi != watchList.end(); ++cvi )
         {
            if( (*cvi)->_lhs ) continue;
            varPtr0 = (*cvi)->_relateVar;
            varPtr1 = varPtr0 + 1;
            varPtr = varPtr0 + 2;
            const uint32_t * const vend = varPtr0 + (*cvi)->_clauses[0]->_size;
            if( *varPtr0 != var ) ++varPtr0, --varPtr1;
            for( ; varPtr != vend; ++varPtr )
               if( !_variables[*varPtr]._defined )
               {
                  _watchLists[*varPtr].push_back( *cvi );
                  swap( *varPtr0, *varPtr );
                  break;
               }
            if( varPtr != vend ) continue;
            lhs = *varPtr1;
            if( _variables[lhs]._defined ) continue;
            _variables[lhs]._defined = true;
            _variables[lhs]._gate = *cvi;
            (*cvi)->_lhs = lhs;
            _stack.push_back( lhs );
         }
      }
      lhs = 0;
      while( !undefinedVars.empty() )
      {
         const unsigned var = undefinedVars.front();
         pop_heap( undefinedVars.begin(), undefinedVars.end(), sortVar );
         undefinedVars.pop_back();
         if( _variables[var]._defined ) continue;
         if( _watchLists[var].empty() ) break;
         lhs = var;
         break;
      }
      /*uintvi = undefinedVars.begin();
      for( vector<uint32_t>::const_iterator cvi = uintvi; cvi != undefinedVars.end(); ++cvi )
      {
         if( _variables[*cvi]._defined ) continue;
         *uintvi = *cvi;
         ++uintvi;
         if( _watchLists[*cvi].empty() ) continue;
         if( !lhs || _watchLists[lhs].size() < _watchLists[*cvi].size() )
            lhs = *cvi;
      }
      undefinedVars.resize( uintvi - undefinedVars.begin() );*/
      if( !lhs ) break;
      assert( !_watchLists[lhs].empty() );
      ++directGateNum;
      _variables[lhs]._defined = true;
      _variables[lhs]._gate = _watchLists[lhs][0];
      _variables[lhs]._gate->_lhs = lhs;
      _stack.push_back( lhs );
      uint32_t otherVar =  _variables[lhs]._gate->_relateVar[0];
      if( otherVar == lhs )
         otherVar = _variables[lhs]._gate->_relateVar[1];
      assert( otherVar != lhs );
      vector<Gate*> &watchList = _watchLists[otherVar];
      vector<Gate*>::iterator vi = watchList.begin();
      for( vector<Gate*>::const_iterator cvi = vi; cvi != watchList.end(); ++cvi )
         if( !(*cvi)->_lhs )
         {
            *vi = *cvi;
            ++vi;
         }
      watchList.resize( vi - watchList.begin() );
   }
   //release
   for( vector<Gate*>::const_iterator cvi = _undirectGates.begin();
        cvi != _undirectGates.end(); ++cvi )
   {
      if( (*cvi)->_relateVar != NULL )
      {
         varPtr = (*cvi)->_relateVar;
         const uint32_t * const vend = varPtr + (*cvi)->_clauses[0]->_size;
         for( ; varPtr != vend; ++varPtr )
            if( !_variables[*varPtr]._defined ) break;
         if( varPtr != vend ) ++undefinedNum;
         free( (*cvi)->_relateVar );
      }
      (*cvi)->_relateVar = NULL;
   }
    cout << "c UnDirect to Direct Gate: " << _stack.size()  << endl;
    cout << "c Forced Direct Gate: " << directGateNum << " Unuse unDirect Gate: " << undefinedNum << endl;
   _stack.clear();
   delete [] _watchLists;
}

void
CnfToAig::coverGate()
{
   _andNum = 0; _invNum = 0; _xorNum = 0; _iteNum = 0;
   for( unsigned root = 1; root < _varNum; ++root )
   {
      Variable &rootVar = _variables[root];
      if( !rootVar._defined || rootVar._mark ) continue;
      coverGateDfs( root );
   }
   for( vector<uint32_t>::const_iterator cvi = _units.begin(); cvi != _units.end(); ++cvi )
      _variables[*cvi>>1]._covered = true;
   unsigned rootNum = 0, leafNum = 0,
            coverBinaryNum = 0, uncoverBinaryNum = 0,
            coverClsNum = 0, uncoverClsNum = 0,
            coverVarNum = 0, uncoverVarNum = 0, unusedVarNum = 0;
   for( unsigned root = 1; root < _varNum; ++root )
   {
      Variable &rootVar = _variables[root];
      if( rootVar._mark == 2147483647 )
      {
         assert( rootVar._defined );
         rootVar._root = true;
         ++rootNum;
      }
      else rootVar._root = false;
      if( rootVar._covered && !rootVar._defined )
         ++leafNum;
      rootVar._mark  = 0;
      if( !rootVar._used ) ++unusedVarNum;
      else if( rootVar._covered ) ++coverVarNum;
      else ++uncoverVarNum;
   }
   //vector<Clause*>::iterator vi = _clauses.begin();
   for( vector<Clause*>::const_iterator cvi = _clauses.begin(); cvi != _clauses.end(); ++cvi )
   {
      const Clause &cls = *(*cvi);
      if( cls._covered )
      {
         if( cls._size == 2 )
            ++coverBinaryNum;
         else ++coverClsNum;
         //(*vi++) = *cvi;
      }
      else if( cls._size == 2 ) ++uncoverBinaryNum;
      else ++uncoverClsNum;
   }
   //_clauses.resize( vi - _clauses.begin() );
   _coverRate = 100*static_cast<double>( coverClsNum + coverBinaryNum + _units.size() ) / 
           ( coverClsNum + coverBinaryNum + _units.size() + uncoverClsNum + uncoverBinaryNum );
   cout << "c After covering, Total Root: " << rootNum << " Leaf: " << leafNum << endl
        << "c Variable( cover/uncovered/unused ): " << coverVarNum << " " << uncoverVarNum << " " << unusedVarNum << endl
        << "c Unit Clauses: " << _units.size() << endl
        << "c Binary Clauses( cover/uncovered ): " << coverBinaryNum << " " << uncoverBinaryNum << endl
        << "c Clauses( cover/uncovered ): " << coverClsNum << " " << uncoverClsNum << endl
        << "c Total Clauses( cover/uncovered ): " << coverClsNum + coverBinaryNum + _units.size() 
        << " " << uncoverClsNum + uncoverBinaryNum << " " << _coverRate << "%" << endl
        << "c Covered Ands: " << _andNum << " Invs: " << _invNum << " Xors: " << _xorNum << " Ites: " << _iteNum << endl;
}

void
CnfToAig::coverGateDfs( unsigned root )
{
   /*bool cycle;
   Clause *cls;
   
   assert( _stack.empty() );
   _stack.push_back( root );
   _variables[root]._mark = 1;
   while( !_stack.empty() )
   {
      root = _stack.back();
      _stack.pop_back();
      Variable &rootVar = _variables[root];
      assert( rootVar._mark <= 3 );
      if( rootVar._mark == 3 ) continue;  // already traveled
      assert( rootVar._defined );
      if( rootVar._mark == 2 ) //travel back and pop
      {
         rootVar._mark = 3;
         buildGate( root ); 
         continue;
      }
      assert( rootVar._mark == 1 );
      assert( rootVar._gate != NULL );
      cycle = false;
      cls =  rootVar._gate->_clauses[0];
      const uint32_t * const lend = cls->_literals + cls->_size;
      _stack.push_back( root );
      for( const uint32_t *lit = cls->_literals; lit != lend; ++lit )
      {
         const uint32_t var = (*lit) >> 1;
         Variable &inputVar = _variables[var];
         inputVar._covered = true;
         if( inputVar._mark == 2 )
         {
            cycle = true;
            break;
         }
         if( inputVar._mark == 4 ) inputVar._mark = 3;
         if( !inputVar._defined )
         {
            if( _links[var]._data == UINT_MAX )
               buildGate( var );
            continue;
         }
         if( inputVar._mark ) continue;
         _stack.push_back( var );
         inputVar._mark = 1;
      }
      assert( !cycle );
      if( rootVar._gate->_type == Gate::ITE )
      {
         const Clause * const cls1 = rootVar._gate->_clauses[2];
         const uint32_t * const lend1 = cls1->_literals + cls1->_size;
         for( const uint32_t *lit = cls1->_literals; lit != lend1; ++lit )
         {
            const uint32_t var = (*lit) >> 1;
            Variable &inputVar = _variables[var];
            inputVar._covered = true;
            if( inputVar._mark == 2 )
            {
               cycle = true;
               break;
            }
            if( inputVar._mark == 4 ) inputVar._mark = 3;
            if( !inputVar._defined )
            {
               if( _links[var]._data == UINT_MAX )
                  buildGate( var );
               continue;
            }
            if( inputVar._mark ) continue;
            _stack.push_back( var );
            inputVar._mark = 1;
         }
      }
      assert( !cycle );
      rootVar._mark = 2;
      //set clause covered
      Clause ** const clsend = rootVar._gate->_clauses + rootVar._gate->_size;
      if( rootVar._gate->_type == Gate::AND ) ++_andNum;
      else if( rootVar._gate->_type == Gate::INV ) ++_invNum;
      else if( rootVar._gate->_type == Gate::XOR ) ++_xorNum;
      else if( rootVar._gate->_type == Gate::ITE ) ++_iteNum;
      for( Clause **pcls = rootVar._gate->_clauses; pcls != clsend; ++pcls )
         (*pcls)->_covered = true;
   }
   _variables[root]._mark = 4;
*/
#ifndef NDEBUG
   const unsigned orgRoot = root;
#endif
   unsigned cycleVar, lit; 
   assert( _stack.empty() );
   const Clause * cls;
   _stack.push_back( root );
   _variables[root]._covered = true;
   assert( _variables[root]._mark == 0 );
   while( true )
   {
      Variable &rootVar = _variables[root];
      assert( rootVar._defined );
      assert( rootVar._gate != NULL );
      lit = 0;
      cls = rootVar._gate->_clauses[0];
      if( rootVar._mark < cls->_size )
         lit = cls->_literals[rootVar._mark];
      else if( rootVar._gate->_type == Gate::ITE )
      {
         const unsigned index = rootVar._mark - cls->_size;
         cls = rootVar._gate->_clauses[2];
         if( index < cls->_size )
            lit = cls->_literals[index];
      }
      if( lit == 0 ) //travel back and pop
      {
         buildGate( root ); 
         rootVar._mark = 2147483648;
         Clause ** const clsend = rootVar._gate->_clauses + rootVar._gate->_size;
         if( rootVar._gate->_type == Gate::AND ) ++_andNum;
         else if( rootVar._gate->_type == Gate::INV ) ++_invNum;
         else if( rootVar._gate->_type == Gate::XOR ) ++_xorNum;
         else if( rootVar._gate->_type == Gate::ITE ) ++_iteNum;
         for( Clause **pcls = rootVar._gate->_clauses; pcls != clsend; ++pcls )
            (*pcls)->_covered = true;
         _stack.pop_back();
         if( _stack.empty() ) break;
         root = _stack.back();
         continue;
      }
      if( rootVar._mark == 0 )
      {
         cycleVar = 0;
         const Clause * const cls =  rootVar._gate->_clauses[0];
         const uint32_t * const lend = cls->_literals + cls->_size;
         for( const uint32_t *plit = cls->_literals; plit != lend; ++plit )
         {
            const unsigned var = (*plit) >> 1;
            Variable &inputVar = _variables[var];
            inputVar._covered = true;
            if( inputVar._mark == 2147483647 ) inputVar._mark = 2147483648;  
            if( inputVar._mark == 0 || inputVar._mark == 2147483648 ) continue;
            cycleVar = var;
            break;
         }
         assert( cycleVar == 0 );
         if( rootVar._gate->_type == Gate::ITE )
         {
            const Clause * const cls1 = rootVar._gate->_clauses[2];
            const uint32_t * const lend1 = cls1->_literals + cls1->_size;
            for( const uint32_t *plit = cls1->_literals; plit != lend1; ++plit )
            {
               const unsigned var = (*plit) >> 1;
               Variable &inputVar = _variables[var];
               inputVar._covered = true;
               if( inputVar._mark == 2147483647 ) inputVar._mark = 2147483648;  
               if( inputVar._mark == 0 || inputVar._mark == 2147483648 ) continue;
               cycleVar = var;
               break;
            }
         }
         assert( cycleVar == 0 );
      }
      ++rootVar._mark;
      const unsigned var = lit >> 1;
      if( var == root ) continue;
      const Variable &litVar = _variables[var];
      if( !litVar._defined )
      {
         if( _links[var]._data == UINT_MAX )
            buildPi( var );
         continue;
      }
      if( litVar._mark == 2147483648 ) continue;
      root = var;
      _stack.push_back( root );
   }
   assert( orgRoot == root );
   _variables[root]._mark = 2147483647;
}

void
CnfToAig::buildPi( unsigned root )
{
   assert( _links[root]._data == UINT_MAX );
   const Variable &rootVar = _variables[root];
   assert( !rootVar._defined );
   if( rootVar._unit )
   {
      if( _variables[root]._polarity == 1 )
         _links[root]._data = 0;
      else _links[root]._data = 1;
   }
   else
   {
      _links[root] = _circuit.pushPi();
      _cirConsts.push_back( 0 );
      _aigLevels->updateLevel( _circuit, _links[root]._index );
   }
}

void
CnfToAig::buildGate( unsigned root )
{
   assert( _links[root]._data == UINT_MAX );
   const Variable &rootVar = _variables[root];
   assert( rootVar._defined && rootVar._gate != NULL );
   Clause *cls = rootVar._gate->_clauses[0];
   if( rootVar._gate->_type == Gate::INV )
   {
      assert( cls->_size == 2 );
      unsigned ivar = cls->_literals[0] >> 1;
      if( root == ivar ) ivar = cls->_literals[1] >> 1;
      assert( _links[ivar]._data != UINT_MAX );
      _links[root] = _links[ivar];
      _links[root]._sign ^= 1 ^ ( cls->_literals[0] & 1 ) ^ ( cls->_literals[1] & 1 );
   }
   if( rootVar._gate->_type == Gate::AND )
   {
      _fanins.clear();
      _marks.clearMark();
      _marks.resize( 2*_circuit.size(), 0 );
      //collect fanins
      assert( root == ( rootVar._gate->_lhs >> 1 ) );
      const unsigned inv = ( rootVar._gate->_lhs & 1 );
      const uint32_t * const lend = cls->_literals + cls->_size;
      const uint32_t *lit;
      for( lit = cls->_literals; lit != lend; ++lit )
      {
         const uint32_t var = (*lit) >> 1;
         if( var == root ) continue;
         assert( _links[var]._data != UINT_MAX );
         if( _variables[var]._unit )
         {
            if( _variables[var]._polarity == ( *lit & 1 ) )
            {
               _links[root]._data = inv;
               break;
            }
            continue;
         }
         AigIndex fanin = _links[var];
         fanin._sign ^= ( ( (*lit) & 1 ) ^ 1 );
         if( _marks.isMark( fanin._data^1 ) )
         {
            _links[root]._data = inv;
            break;
         }
         if( _marks.isMark( fanin._data ) ) continue;
         _marks.setMark( fanin._data );
         _fanins.push_back( fanin );
      }
      if( lit == lend ) 
      {
         _links[root] = buildAndGate();
         _links[root]._sign ^= inv;
      }
   }
   if( rootVar._gate->_type == Gate::XOR )
   {
      _fanins.clear();
      //collect fanins
      assert( root == ( rootVar._gate->_lhs >> 1 ) );
      unsigned inv = ( rootVar._gate->_lhs & 1 ) ^ 1;
      const uint32_t * const lend = cls->_literals + cls->_size;
      const uint32_t *lit;
      for( lit = cls->_literals; lit != lend; ++lit )
      {
         const uint32_t var = (*lit) >> 1;
         if( var == root )
         {
            assert( rootVar._gate->_lhs == *lit );
            continue;
         }
         assert( _links[var]._data != UINT_MAX );
         if( _variables[var]._unit )
         {
            if( _variables[var]._polarity == ( *lit & 1 ) )
               inv ^= 1;
            continue;
         }
         AigIndex fanin = _links[var];
         fanin._sign ^= ( (*lit) & 1 );
         _fanins.push_back( fanin );
      }
      // clean XOR fanins
      if( !_fanins.empty() )
      {
         sort( _fanins.begin(), _fanins.end() );
         vector<AigIndex>::iterator vi = _fanins.begin();
         for( vector<AigIndex>::const_iterator cvi = _fanins.begin() + 1; cvi != _fanins.end(); ++cvi )
            if( vi->_data == 0 )
               *vi = *cvi;
            else if( vi->_data == 1 )
               *vi = ~(*cvi);
            else if( *vi == *cvi )
               vi->_data = 0;
            else if( *vi == ~(*cvi) )
               vi->_data = 1;
            else 
            {
               ++vi;
               *vi = *cvi;
            }
         _fanins.resize( vi + 1 - _fanins.begin() );
         if( _fanins.back()._data <= 1 )
         {
            if( _fanins.back()._data == 1 )
               inv ^= 1;
            _fanins.pop_back();
         }
      }
      _links[root] = buildXorGate();
      _links[root]._sign ^= inv;
   }
   if( rootVar._gate->_type == Gate::ITE )
   {
      assert( rootVar._gate->_size == 4 );
      unsigned condLit = 0, thenLit = 0, elseLit = 0, inv1 = 2, inv2 = 2;
      const uint32_t * const lend = cls->_literals + cls->_size;
      const uint32_t *lit;
      for( lit = cls->_literals; lit != lend; ++lit )
      {
         if( ( *lit >> 1 ) == root ) 
         {
            inv1 = (*lit) & 1;
            continue;
         }
         if( condLit == 0 ) condLit = *lit;
         else 
         {
            assert( thenLit == 0 );
            thenLit = *lit;
         }
      }
      assert( inv1 < 2 );
      cls = rootVar._gate->_clauses[2];
      bool checkCond = false;
      const uint32_t * const lend1 = cls->_literals + cls->_size;
      for( lit = cls->_literals; lit != lend1; ++lit )
      {
         if( ( *lit >> 1 ) == root ) 
         {
            inv2 = (*lit) & 1;
            continue;
         }
         if( !checkCond )
         {
            if( (condLit^1) == *lit ) checkCond = true;
            else if( (thenLit^1) == *lit )
            {
               swap( condLit, thenLit );
               checkCond = true;
            }
         }
         if( (condLit^1) != *lit ) elseLit = *lit;
      }
      assert( inv2 < 2 );
      assert( checkCond && elseLit != 0 );
      const AigIndex condFanin = AigIndex( condLit ).getLink( _links );
      const AigIndex thenFanin = AigIndex( thenLit ^ inv1 ^ 1 ).getLink( _links );
      const AigIndex elseFanin = AigIndex( elseLit ^ inv2 ^ 1 ).getLink( _links );
      assert( condFanin._data != UINT_MAX && thenFanin._data != UINT_MAX && elseFanin._data != UINT_MAX );
      const AigIndex select0 = pushNode( ~condFanin, thenFanin );
      const AigIndex select1 = pushNode( condFanin, elseFanin );
      _links[root] = ~pushNode( ~select0, ~select1 );
   }
   if( rootVar._unit )
   {
      _cirConsts[ _links[root]._index ] |= ( 1 <<  
       ( ( rootVar._polarity == _links[root]._sign ) ? 1 : 0 ) );
   }
   return;
}

bool
CnfToAig::sortLevel( AigIndex a, AigIndex b )
{
   const unsigned la = (*_aigLevels)[a._index];
   const unsigned lb = (*_aigLevels)[b._index];
   if( la == lb ) return b < a;
   return la > lb;
}

AigIndex
CnfToAig::buildAndGate()
{
   if( _fanins.empty() ) return AigIndex( 1 );

   make_heap( _fanins.begin(), _fanins.end(), sortLevel );
   while( _fanins.size() > 1 )
   {
      const AigIndex fanin1 = _fanins.front();
      pop_heap( _fanins.begin(), _fanins.end(), sortLevel );
      _fanins.pop_back();
      const AigIndex fanin2 = _fanins.front();
      pop_heap( _fanins.begin(), _fanins.end(), sortLevel );
      _fanins.pop_back();
      _fanins.push_back( pushNode( fanin1, fanin2 ) );
      push_heap( _fanins.begin(), _fanins.end(), sortLevel );
   }
   return _fanins[0];
}

AigIndex
CnfToAig::buildXorGate()
{
   if( _fanins.empty() ) return AigIndex( 0 );

   make_heap( _fanins.begin(), _fanins.end(), sortLevel );
   while( _fanins.size() > 1 )
   {
      const AigIndex fanin1 = _fanins.front();
      pop_heap( _fanins.begin(), _fanins.end(), sortLevel );
      _fanins.pop_back();
      const AigIndex fanin2 = _fanins.front();
      pop_heap( _fanins.begin(), _fanins.end(), sortLevel );
      _fanins.pop_back();
      const AigIndex and0 = pushNode( fanin1, ~fanin2 );
      const AigIndex and1 = pushNode( ~fanin1, fanin2 );
      _fanins.push_back( ~pushNode( ~and0, ~and1 ) );
      push_heap( _fanins.begin(), _fanins.end(), sortLevel );
   }
   return _fanins[0];
}

AigIndex
CnfToAig::pushNode( AigIndex a, AigIndex b )
{
   if( ( _cirConsts[a._index] & 1 ) ) a._index = 0;
   else if( ( _cirConsts[a._index] & 2 ) )
   {
      a._index = 0;
      a._sign = !a._sign;
   }
   if( ( _cirConsts[b._index] & 1 ) ) b._index = 0;
   else if( ( _cirConsts[b._index] & 2 ) )
   {
      b._index = 0;
      b._sign = !b._sign;
   }
   if( b < a ) swap( a, b );
   //cout << a._data << " " << b._data << endl;
   unsigned index = _circuit.size();
   AigIndex resIndex = _aigHash.hashNode( a, b, index, true );
   assert( resIndex._index <= _circuit.size() );
   if( index == resIndex._index )
   {
      _circuit.pushNode( a, b );
      _cirConsts.push_back(0);
      _aigLevels->updateLevel( _circuit, index );
   }
   return resIndex;
}

void
CnfToAig::buildClauses()
{
   double avgSize = 0;
   unsigned num = 0, maxSize = 0;
   for( vector<Clause*>::const_iterator cvi = _clauses.begin(); cvi != _clauses.end(); ++cvi )
   {
      if( (*cvi)->_covered ) continue;
      avgSize += (*cvi)->_size;
      if( maxSize < (*cvi)->_size ) maxSize = (*cvi)->_size;
      ++num;
      buildClause( *cvi );
   }
   cout << "c Uncover Clauses avg size: " << avgSize / num << " max size: " << maxSize << endl;
   for( vector<unsigned>::const_iterator cvi = _units.begin(); cvi != _units.end(); ++cvi )
   {
      const unsigned index = *cvi >> 1;
      if( _links[index]._data != UINT_MAX ) continue;
      _links[index]._data = ( *cvi & 1 ) ^ 1;
   }
}

void
CnfToAig::buildClause( const Clause *cls )
{
   _marks.clearMark();
   _marks.resize( 2*_circuit.size(), 0 );
   _fanins.clear();
   const uint32_t * const lend = cls->_literals + cls->_size;
   for( const uint32_t *lit = cls->_literals; lit != lend; ++lit )
   {
      const uint32_t var = (*lit) >> 1;
      if( _variables[var]._unit )
      {
         if( _variables[var]._polarity == ( (*lit) & 1 ) ) return;
         else continue;
      }
      if( _links[var]._data == UINT_MAX )
      {
         assert( !_variables[var]._defined );
         buildPi( var );  
         _marks.resize( 2*_circuit.size(), 0 );
      }
      AigIndex fanin = _links[var];
      fanin._sign ^= ( ( (*lit) & 1 ) ^ 1 );
      if( _marks.isMark( fanin._data^1 ) ) return;
      if( _marks.isMark( fanin._data ) ) continue;
      _marks.setMark( fanin._data );
      _fanins.push_back( fanin );
   }
   const AigIndex resIndex = buildAndGate();
   _cirConsts[ resIndex._index ] |= ( 1 << resIndex._sign );
}

void
CnfToAig::setPo()
{
   if( _cirConsts[0] == 3 )
   {
      _unsat = true;
      cout << "c Gate 0 UNSAT" << endl;
      return;
   }
   for( unsigned i = 1; i < _circuit.size(); ++i )
   {
      const unsigned char constValue = _cirConsts[i];
      assert( constValue <= 3 );
      if( constValue == 0 ) continue;
      if( constValue == 3 ) 
      {
         _unsat = true;
         cout << "c Po " << i << " UNSAT" << endl;
         return;
      }
      _circuit.addPo( AigIndex( i, ( constValue == 1 ) ? 1 : 0 ) );
   }
}

void
CnfToAig::run()
{
   if( _unsat ) { freeHash(); return; }
   extractGate();
   freeHash();
   setDirection();
   _marks.initialize( 2*_varNum );
   _aigLevels = new AigLevel;
   _links.clear();
   _links.resize( _varNum );
   _cirConsts.push_back(1);
   coverGate();
   freeGate();
   buildClauses();
   delete _aigLevels;
   setPo();
   cout << "c Final circuit: ";
   _circuit.report( cout );
}

bool
CnfToAig::verify( const vector<unsigned>& varValue ) const
{
   unsigned value, i, j;
   
   assert( varValue.size() == _varNum );
   for( i = 0; i < _units.size(); ++i )
   {
      const unsigned lit = _units[i];
      value = varValue[ lit >> 1 ] ^ ( lit & 1 );
      if( value != 1 )
      {
         cout << "c CnfToAig: verify fail: unit: " << lit << " link: " << _links[lit>>1]._data 
              << " " << _circuit[_links[lit>>1]._index].isPi() << endl;
         return false;
      }
   }
   for( i = 0; i < _clauses.size(); ++i )
   {
      for( j = 0; j < _clauses[i]->_size; ++j )
      {
         const unsigned lit = _clauses[i]->_literals[j];
         value = varValue[ lit >> 1 ] ^ ( lit & 1 );
         if( value == 1 ) break;
      }
      if( j == _clauses[i]->_size )
      {
         cout << "c CnfToAig: verify fail: clause: ";
         for( j = 0; j < _clauses[i]->_size; ++j )
            cout << _clauses[i]->_literals[j] << " ";
         cout << endl;
         return false;
      }
   }
   return true;
}



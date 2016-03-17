#include <cassert>
#include "tmSat.h"
#include "../truth/truthTable.h"
#include "../cryptominisat/Solver.h"
#include "../util/utilResourceUsage.h"
#define VARLINK_CONST0 429496720U
#define VARLINK_CONST1 429496721U

static inline int isVarLinkConst( unsigned varLink, unsigned inv )
{
   varLink ^= inv;
   if( varLink == VARLINK_CONST0 ) return 0;
   if( varLink == VARLINK_CONST1 ) return 1;
   return -1;
}

void TmSat::addClauses( Solver &s )
{
   unsigned j;
   int res;
   unsigned char *lit;
   
   for( vector<GateClause>::const_iterator cvi = _addClauses.begin();
        cvi != _addClauses.end(); ++cvi )
   {
      const TmGate &gate = _cir[ cvi->_gateIndex ];
      const unsigned truth = gate.getTruth();
      const unsigned clsIndex = cvi->_clauseIndex;
      assert( truth <= 0x10000 );
      if( truth == 0x10000 )
      {
         if( clsIndex == 0 )
         {
            vec<Lit> cls;
            for( j = 0; j < gate.size(); ++j )
            {
               assert( gate[j]._index != cvi->_gateIndex );
               unsigned &varLink = _varLinks[gate[j]._index];
               if( varLink == UINT_MAX )
                  varLink = s.newVar();
               res = isVarLinkConst( varLink, gate[j]._sign );
               if( res == 0 ) break;
               if( res == 1 ) continue;
               assert( gate[j]._index != 0 );
               cls.push( Lit( varLink , gate[j]._sign ^ 1 ) );
            }
            if( j != gate.size() ) continue;
            unsigned &ovarLink = _varLinks[ cvi->_gateIndex ];
            if( ovarLink == UINT_MAX )
               ovarLink = s.newVar();
            res = isVarLinkConst( ovarLink, 0 );
            if( res == 1 ) continue;
            if( res != 0 ) cls.push( Lit( ovarLink, 0 ) );
            if( ( _polarity[cvi->_gateIndex] & 1 ) == 0 && cls.size() > 2 ) continue;
            ++_addNum;
            s.addClause( cls );
         }
         else
         {
            bool addOVar = true;
            unsigned &ovarLink = _varLinks[ cvi->_gateIndex ];
            if( ovarLink == UINT_MAX )
               ovarLink = s.newVar();
            res = isVarLinkConst( ovarLink, 0 );
            if( res == 0 ) continue;
            if( res == 1 ) addOVar = false;
            for( j = 0; j < gate.size(); ++j )
            {
               assert( gate[j]._index != cvi->_gateIndex );
               vec<Lit> cls;
               unsigned &varLink = _varLinks[gate[j]._index];
               if( varLink == UINT_MAX )
                  varLink = s.newVar();
               res = isVarLinkConst( varLink, gate[j]._sign );
               if( res == 1 ) continue;
               else if( res != 0 ) 
               {
                  assert( gate[j]._index != 0 );
                  cls.push( Lit( varLink , gate[j]._sign ) );
               }
               if( addOVar ) cls.push( Lit( ovarLink, 1 ) );
               ++_addNum;
               s.addClause( cls );
            }
         }
         continue;
      }
      const unsigned invTruth = 0xFFFF & ( ~truth );
#ifndef NDEBUG
      const unsigned litBound = 2*gate.size() + 2;
#endif
      const unsigned clsNum = _truthToCnf.getClauseNum( truth );
      if( clsIndex < clsNum )
         lit = _truthToCnf.getClauseToCnf( truth, clsIndex );
      else
         lit = _truthToCnf.getClauseToCnf( invTruth, clsIndex - clsNum );
      vec<Lit> cls;
      for( ; *lit != 0; ++lit )
      {
         assert( *lit < litBound );
         AigIndex fanin = gate[((*lit)>>1)-1];
         fanin._sign ^= ( (*lit) & 1 );
         if( fanin._index == 0 )
         {
            if( fanin._sign == 0 ) continue;
            else break;
         }
         unsigned &varLink =  _varLinks[ fanin._index ];
         if( varLink == UINT_MAX )
            varLink = s.newVar();
         res = isVarLinkConst( varLink, fanin._sign );
         if( res == 1 ) break;
         else if( res != 0 ) cls.push( Lit( varLink , fanin._sign ) );
      }
      if( *lit != 0 ) continue;
      unsigned &varLink = _varLinks[ cvi->_gateIndex ];
      if( varLink == UINT_MAX )
         varLink = s.newVar();
      res = isVarLinkConst( varLink, clsIndex >= clsNum );
      if( res == 1 ) continue;
      else if( res != 0 ) cls.push( Lit( varLink , clsIndex >= clsNum ) );
      if( clsIndex < clsNum )
      {
         if( ( _polarity[cvi->_gateIndex] & 1 ) == 0 && cls.size() > 2 ) continue;
      }
      else if( ( _polarity[cvi->_gateIndex] & 2 ) == 0 && cls.size() > 2 ) continue;
      ++_addNum;
      s.addClause( cls );
      /*cout << "addClause: " << truth << ": ";
      for( unsigned i = 0; i < cls.size(); ++i )
          cout << cls[i].toInt() << " ";
      cout << endl;*/
   }
}

void TmSat::addXorClauses( Solver &s )
{
   int res;
   for( vector<unsigned>::const_iterator cvi = _addXorClauses.begin();
        cvi != _addXorClauses.end(); ++cvi )
   {
      const TmGate &gate = _cir[ *cvi ];
      const unsigned truth = gate.getTruth();
      unsigned faninNum = isXorGate( truth );
      vec<Lit> cls;
      bool inv = true;
      if( faninNum == 0 )
      {
         faninNum = isXnorGate( truth );
         inv = false;
      }
      //if( inv ) cout << "Xor " << *cvi << " " << faninNum << " " << gate.size() << endl;
      //else cout << "Xnor " << *cvi << " " << faninNum << " " << gate.size() << endl;
      assert( faninNum != 0 );
      assert( faninNum <= gate.size() );
      ++_addNum;
      for( unsigned i = 0; i < faninNum; ++i )
      {
         AigIndex fanin = gate[i];
         if( fanin._index == 0 )
         {
            //cout << "Fanin Const!!" << endl;
            if( fanin._sign == 0 ) continue;
            else { inv = !inv; continue; }
         }
         unsigned &varLink =  _varLinks[ fanin._index ];
         if( varLink == UINT_MAX )
            varLink = s.newVar();
         res = isVarLinkConst( varLink, fanin._sign );
         //if( res != 0 ) cout << "Var Link Const!!" << endl;
         if( res == 1 ) inv = !inv;
         else if( res != 0 ) cls.push( Lit( varLink , fanin._sign ) );
      }
      unsigned &varLink =  _varLinks[ *cvi ];
      if( varLink == UINT_MAX )
         varLink = s.newVar();
      res = isVarLinkConst( varLink, 0 );
      if( res == 1 ) inv = !inv;
      else if( res != 0 ) cls.push( Lit( varLink , 0 ) );
      s.addXorClause( cls, inv );
   }
}

int TmSat::solveDirect()
{
   SolverConf sconf;
   sconf.verbosity = 0;
   sconf.doPartHandler = false;
   sconf.libraryUsage = false;
   sconf.origSeed = _seed;
   Solver s( sconf );
   lbool ret = l_Undef;
   _addNum = 0;
   init();
   for( unsigned i = 0; i < _cir.getPoNum(); ++i )
   {
      unsigned &varLink =  _varLinks[ _cir.getPo(i)._index ];
      if( varLink == ( VARLINK_CONST0 ^ _cir.getPo(i)._sign ) )
      {
         cout << "c Unit UNSAT" << endl;
         return 0; 
      }
      varLink = VARLINK_CONST1 ^ _cir.getPo(i)._sign;
   }
   addRemain();
   cout << "c Try to Add: #clause: " 
        << _addClauses.size() << " #xorclause: " << _addXorClauses.size() << endl;
   addClauses( s );
   addXorClauses( s );
   _addClauses.clear();
   _addXorClauses.clear();
   cout << "c #var: " << s.nVars() << " #clauses: " << s.nClauses() << " Solving... " << endl;
   ret = s.solve();
   if( ret == l_True ) 
   {
      setPiSolution( s );
      return 1;
   }
   else if( ret == l_False ) return 0;
   else return 2;
}

int TmSat::solve()
{ 
   SolverConf sconf;
   sconf.verbosity = 0;
   sconf.doPartHandler = false;
   sconf.libraryUsage = false;
   sconf.origSeed = _seed;
   Solver s( sconf );
   lbool ret = l_Undef;
   unsigned i, j, step = 0;
   vector<unsigned> pattern( _cir.getPiNum() );

   _addNum = 0;
   init();
   for( i = 0; i < _cir.getPoNum(); ++i )
   {
      unsigned &varLink =  _varLinks[ _cir.getPo(i)._index ];
      if( varLink == ( VARLINK_CONST0 ^ _cir.getPo(i)._sign ) )
      {
         cout << "c Unit UNSAT" << endl;
         return 0; 
      }
      varLink = ( VARLINK_CONST1 ^ _cir.getPo(i)._sign );
   }
   for( j = 0; j < 192 && !_sat; ++j )
   {
      for( i = 0; i < pattern.size(); ++i )
         pattern[i] = static_cast<unsigned>( rand() ) ^ ( static_cast<unsigned>( rand() ) << 16 ); 
      simulation( pattern );
   }
   _addNum = 0;
   for( step = 0; ; ++step )
   {
      if( _sat )
      {
         cout << "c Simulation SAT" << endl; 
         return 1;
      }
      reportSim();
      assert( !_addClauses.empty() || !_addXorClauses.empty() );
      addClauses( s );
      addXorClauses( s );
      _addClauses.clear();
      _addXorClauses.clear();
      coverBinaryClauses();
      addClauses( s );
      _addClauses.clear();
      /*if( step == 0 ) _addNum = 0;
      if( _addNum > 20000 )
      {
         //s.performStepsBeforeSolve();
         _addNum = 0;
      }*/
      cout << "c #var: " << s.nVars() << " #clauses: " << s.nClauses() << " Solving... " << endl;
      ret = s.solve();
      if( ret == l_True ) cout << "c Abstract SAT" << endl;
      else if( ret == l_False ) return 0;
      if( step == 2 )
      {
         addRemain();
         continue;
      }
      if( step == 3 ) 
      {
         setPiSolution( s );
         return 1;
      }
      for( i = 1; i < _cir.size(); ++i )
      {
         const unsigned &varLink = _varLinks[i];
         if( varLink == UINT_MAX ) _refModel[i] = 2;
         else if( varLink == VARLINK_CONST0 ) _refModel[i] = 0;
         else if( varLink == VARLINK_CONST1 ) _refModel[i] = 1; 
         else if( s.model[varLink] == l_False ) _refModel[i] = 0;
         else if( s.model[varLink] == l_True ) _refModel[i] = 1;
         else _refModel[i] = 2;
      }
      findConstRelation( s );
      for( j = 0; j < 32 && !_sat; ++j )
      {
         for( i = 0; i < _cir.getPiNum(); ++i )
         {
            const unsigned &value = _refModel[_cir.getPi(i)._index];
            if( value == 2 )
               pattern[i] = static_cast<unsigned>( rand() ) ^ ( static_cast<unsigned>( rand() ) << 16 );
            else if( value == 1 ) pattern[i] = ~unsigned(0);
            else pattern[i] = 0;
         }
         simulation( pattern );
      }
   }
}

void TmSat::init()
{
   srand( _seed );
   _sat = false;
   _simData.clear();
   _clauseTrans.clear();
   _varLinks.clear();
   _addClauses.clear();
   _addXorClauses.clear();
   
   _simData.resize( _cir.size(), 0  );
   _clauseTrans.resize( _cir.size(), 0 );
   _varLinks.resize( _cir.size(), UINT_MAX );
   _refModel.resize( _cir.size() );
   _varLinks[0] = VARLINK_CONST0;
   setPolarity();
}

void TmSat::simulation( const vector<unsigned> &pattern )
{
   unsigned i, j, orValue;
   unsigned simData[10];
   unsigned char *lit;
   
   for( i = 0; i < _cir.getPiNum(); ++i )
      _simData[_cir.getPi(i)._index] = pattern[i];
   for( i = 1; i < _cir.size(); ++i )
   {
      const TmGate &gate = _cir[i];
      if( gate.isPi() ) continue;
      const unsigned truth = gate.getTruth();
      if( truth == 0x10000 )
      {
         _simData[i] = ~unsigned(0);
         for( j = 0; j < gate.size(); ++j )
            _simData[i] &= ( gate[j]._sign  ? ~_simData[gate[j]._index] : _simData[gate[j]._index] );
         continue;
      }
      const unsigned litBound = 2*gate.size() + 2;
      for( j = 3; j < litBound; j+=2 )
      {
         const AigIndex &fanin = gate[(j>>1)-1];
         simData[j] = fanin._sign ? ~_simData[ fanin._index] : _simData[ fanin._index ];
      }
      for( j = 2; j < litBound; j+=2 )
         simData[j] = ~simData[j+1];
      _simData[i] = 0;
      for( j = 0; j < _truthToCnf.getClauseNum( truth ); ++j )
      {
         orValue = ~unsigned(0);
         for( lit = _truthToCnf.getClauseToCnf( truth, j ); *lit != 0; ++lit )
         {
            assert( *lit < litBound );
            orValue &= simData[*lit];
         }
         _simData[i] |= orValue;
      }
   }
   _simReasons.clear();
   _simReasons.resize( _cir.size() );
   unsigned satResult = ~unsigned(0);
   for( j = 0; j < _cir.getPoNum(); ++j )
   {
      const unsigned poData = _cir.getPo(j)._data;
      const unsigned poIndex = _cir.getPo(j)._index;
      const unsigned unsatData = ( poData & 1 ) ? ~unsigned(0) : 0;
      _simReasons[poIndex] = ~unsigned(0);
      satResult &= ( _simData[poIndex] ^ unsatData );
   }
   for( j = 0; j < _assumeConstGate.size(); ++j )
   {
      const unsigned assumeIndex = _assumeConstGate[j]._index;
      const unsigned unsatData = _assumeConstGate[j]._sign ? ~_simData[assumeIndex] : _simData[assumeIndex];
      _simReasons[assumeIndex] = unsatData;
   }
   if( satResult )
   {
      for( j = 0; ( satResult & 1 ) == 0; ++j, satResult >>= 1 );
      _sat = true;
      _piSolution.clear();
      _piSolution.resize( _cir.getPiNum(), 2 );
      for( unsigned i = 0; i < _cir.getPiNum(); ++i )
      {
         const unsigned index = _cir.getPi(i)._index;
         _piSolution[i] = ( _simData[index] >> j ) & 1;
      }
      return;
   }
   for( i = _cir.size() - 1; i > 0; --i  )
   {
      const TmGate &gate = _cir[i];
      const unsigned truth = gate.getTruth();
      const unsigned reason = _simReasons[i];
      if( truth == 0x10000 )
      {
         if( !( _clauseTrans[i] & 1 ) && ( _simData[i] & reason ) )
         {
            _addClauses.push_back( GateClause( i, 0 ) );
            _clauseTrans[i] |= 1;
         }
         if( !( _clauseTrans[i] & 2 ) && ( ~_simData[i] & reason ) )
         {
            _addClauses.push_back( GateClause( i, 1 ) );
            _clauseTrans[i] |= 2;
         }
         for( j = 0; j < gate.size(); ++j )
         {
            const unsigned faninData = gate[j]._sign ? ~_simData[gate[j]._index] : _simData[gate[j]._index];
            _simReasons[gate[j]._index] |= ~( faninData ^ _simData[i] ) & reason;
         }
         continue;
      }
      if( gate.isPi() ) continue;
      const unsigned invTruth = 0xFFFF & ( ~truth );
      const unsigned litBound = 2*gate.size() + 2;
      //assert( _truthToCnf.getClauseNum( truth ) == 1 && _truthToCnf.getClauseNum( invTruth ) == 2 );
      for( j = 3; j < litBound; j+=2 )
      {
         const AigIndex &fanin = gate[(j>>1)-1];
         simData[j] = fanin._sign ? ~_simData[ fanin._index] : _simData[ fanin._index ];
      }
      for( j = 2; j < litBound; j+=2 )
         simData[j] = ~simData[j+1];
      const unsigned clsNum = _truthToCnf.getClauseNum( truth );
      int isXor = isXorGate( truth );
      if( isXor == 0 ) isXor = isXnorGate( truth );
      for( j = 0; j < clsNum; ++j )
      {
         orValue =  ~unsigned(0);
         for( lit = _truthToCnf.getClauseToCnf( truth, j ); *lit != 0; ++lit )
         {
            assert( *lit < litBound );
            orValue &= simData[*lit];
         }
         orValue &= reason;
         if( orValue == 0 ) continue;
         if( !( _clauseTrans[i] & ( 1 << j ) ) )
         {
            if( isXor != 0 )
            {
               _addXorClauses.push_back( i );
               _clauseTrans[i] = UINT_MAX;
            }
            else
            {
               _addClauses.push_back( GateClause( i, j ) );
               _clauseTrans[i] |= ( 1 <<  j );
            }
         }
         for( lit = _truthToCnf.getClauseToCnf( truth, j ); *lit != 0; ++lit )
         {
            assert( *lit < litBound );
            const AigIndex &fanin = gate[(*lit>>1)-1];
            _simReasons[ fanin._index ] |= orValue;
         }
      }
      const unsigned invClsNum = _truthToCnf.getClauseNum( invTruth );
      for( j = 0; j < invClsNum; ++j )
      {
         orValue =  ~unsigned(0);
         for( lit = _truthToCnf.getClauseToCnf( invTruth, j ); *lit != 0; ++lit )
         {
            assert( *lit < litBound );
            orValue &= simData[*lit];
         }
         orValue &= reason;
         if( orValue == 0 ) continue;
         if( !( _clauseTrans[i] & ( 1 << ( j + clsNum ) ) ) )
         {
            if( isXor != 0 )
            {
               _addXorClauses.push_back( i );
               _clauseTrans[i] = UINT_MAX;
            }
            else
            {
               _addClauses.push_back( GateClause( i, j + clsNum ) );
               _clauseTrans[i] |= ( 1 <<  ( j + clsNum ) );
            }
         }
         for( lit = _truthToCnf.getClauseToCnf( invTruth, j ); *lit != 0; ++lit )
         {
            assert( *lit < litBound );
            const AigIndex &fanin = gate[(*lit>>1)-1];
            _simReasons[ fanin._index ] |= orValue;
         }
      }
   }
}

void
TmSat::coverBinaryClauses()
{
   unsigned i, j, k, mask;
   unsigned char *lit;

   for( i = 1; i < _cir.size(); ++i )
   {
      const TmGate &gate = _cir[i];
      if( gate.isPi() ) continue;
      if( _clauseTrans[i] == 0 ) continue;
      const unsigned truth = gate.getTruth();
      if( truth == 0x10000 )
      {
         if( ( _clauseTrans[i] & 2 ) != 0 ) continue;
         _addClauses.push_back( GateClause( i, 1 ) );
         _clauseTrans[i] |= 2;
         continue;
      }
      const unsigned clsNum = _truthToCnf.getClauseNum( truth );
      mask = 1;
      for( j = 0; j < clsNum; ++j, mask <<= 1 )
      {
         if( ( _clauseTrans[i] & mask ) != 0 ) continue;
         for( k = 0, lit = _truthToCnf.getClauseToCnf( truth, j ); k <= 2 && *lit != 0; ++lit, ++k )
         {
            const unsigned var = gate[(*lit >> 1) - 1]._index;
            if( _varLinks[var] == UINT_MAX ) break; 
         }
         if( *lit != 0 ) continue;
         _addClauses.push_back( GateClause( i, j ) );
         _clauseTrans[i] |= mask;
      }
      const unsigned invTruth = 0xFFFF & ( ~truth );
      const unsigned invClsNum = _truthToCnf.getClauseNum( invTruth );
      for( j = 0; j < invClsNum; ++j, mask <<= 1 )
      {
         if( ( _clauseTrans[i] & mask ) != 0 ) continue;
         for( k = 0, lit = _truthToCnf.getClauseToCnf( invTruth, j ); k <= 2 && *lit != 0; ++lit, ++k )
         {
            const unsigned var = gate[(*lit >> 1) - 1]._index;
            if( _varLinks[var] == UINT_MAX ) break; 
         }
         if( *lit != 0 ) continue;
         _addClauses.push_back( GateClause( i, j + clsNum ) );
         _clauseTrans[i] |= mask;
      }
   }
}

void
TmSat::reportSim()
{
   //static unsigned counter = 0;
   //static unsigned num = 0;
   unsigned i, j, transNum = 0, totalNum = 0;
   
   for( i = 1; i < _cir.size(); ++i )
   {
       const TmGate &gate = _cir[i];
       if( gate.isPi() ) continue;
       const unsigned truth = gate.getTruth();
       if( truth == 0x10000 )
       {
          totalNum += gate.size() + 1;
          if( ( _clauseTrans[i] & 1 ) )
             ++transNum;
          if( ( _clauseTrans[i] & 2 ) )
             transNum += gate.size();
          continue;
       }
       const unsigned invTruth = 0xFFFF & ( ~truth );
       const unsigned clsNum = _truthToCnf.getClauseNum( truth ) + _truthToCnf.getClauseNum( invTruth );
       totalNum += _truthToCnf.getRealClauseNum( truth, gate.size() ) ;
       for( j = 0; j < clsNum; ++j )
         if( _clauseTrans[i] & ( 1 << j ) ) 
            ++transNum;
   }
   cout << "c Simulation --> TransNum: " << transNum << "/" << totalNum << " Try to Add: #clause: " 
        << _addClauses.size() << " #xorclause: " << _addXorClauses.size() << endl;
}

void
TmSat::addRemain()
{
   unsigned i, j;
   
   for( i = 1; i < _cir.size(); ++i )
   {
      const TmGate &gate = _cir[i];
      if( gate.isPi() ) continue;
      const unsigned truth = gate.getTruth();
      assert( truth <= 0x10000 );
      if( truth == 0x10000 )
      {
         if( !( _clauseTrans[i] & 1 ) )
         {
            _addClauses.push_back( GateClause( i, 0 ) );
            _clauseTrans[i] |= 1;
         }
         if( !( _clauseTrans[i] & 2 ) )
         {
            _addClauses.push_back( GateClause( i, 1 ) );
            _clauseTrans[i] |= 2;
         }
         continue;
      }
      int isXor = isXorGate( truth );
      if( isXor == 0 ) isXor = isXnorGate( truth );
      if( isXor != 0 )
      {
         if( _clauseTrans[i] == UINT_MAX ) continue;
         _addXorClauses.push_back( i );
         _clauseTrans[i] = UINT_MAX;
         continue;
      }
      const unsigned invTruth = 0xFFFF & ( ~truth );
      const unsigned clsNum = _truthToCnf.getClauseNum( truth );
      for( j = 0; j < clsNum; ++j )
      {
         if( _clauseTrans[i] & ( 1 <<  j ) ) continue;
         _clauseTrans[i] |= ( 1 <<  j );
         _addClauses.push_back( GateClause( i, j ) );
      }
      const unsigned invClsNum = _truthToCnf.getClauseNum( invTruth );
      for( j = 0; j < invClsNum; ++j )
      {
         if( _clauseTrans[i] & ( 1 <<  ( j + clsNum ) ) ) continue;
         _clauseTrans[i] |= ( 1 <<  ( j + clsNum ) );
         _addClauses.push_back( GateClause( i, j + clsNum ) );
      }
   }
}

void
TmSat::setPolarity()
{
   unsigned i, j;
   unsigned char *lit;
   // polarity: 1:f, 2:~f, 3:both
   _polarity.resize( _cir.size(), 0 );
   for( i = 0; i < _cir.getPoNum(); ++i )
   {
      const AigIndex po = _cir.getPo(i);
      if( po._sign ) _polarity[po._index] |= 1;
      else _polarity[po._index] |= 2;
   }
   for( i = _cir.size() - 1; i > 0; --i )
   {
      unsigned char pol = _polarity[i];
      if( pol == 0 ) continue;
      const TmGate &gate = _cir[i];
      if( gate.isPi() ) continue; 
      unsigned truth = gate.getTruth();
      assert( pol <= 3 );
      if( truth == 0x10000 )
      {
         for( j = 0; j < gate.size(); ++j )
         {
            const AigIndex &fanin = gate[j];
            if( pol == 3 ) _polarity[fanin._index] |= 3;
            else if( pol == 2 ) _polarity[fanin._index] |= ( 2 >> fanin._sign );
            else if( pol == 1 ) _polarity[fanin._index] |= ( 1 << fanin._sign );
         }
         continue;
      }
      for( ; pol != 0; pol = pol >> 1, truth = 0xFFFF & ~truth )
      {
         if( ( pol & 1 ) == 0 ) continue;
         const unsigned clsNum = _truthToCnf.getClauseNum( truth );
         for( j = 0; j < clsNum; ++j )
            for( lit = _truthToCnf.getClauseToCnf( truth, j ); *lit != 0; ++lit )
            {
               AigIndex fanin = gate[(*lit>>1)-1];
               fanin._sign ^= ( *lit & 1 );
               if( fanin._sign ) _polarity[fanin._index] |= 1;
               else _polarity[fanin._index] |= 2;
            }
      }
   }
}

void
TmSat::setPiSolution( Solver &s )
{
   _piSolution.clear();
   _piSolution.resize( _cir.getPiNum(), 2 );
   for( unsigned i = 0; i < _cir.getPiNum(); ++i )
   {
      const unsigned index = _cir.getPi(i)._index;
      const unsigned &varLink = _varLinks[index];
      unsigned &value = _piSolution[i];
      if( varLink == UINT_MAX ) continue;
      if( varLink == VARLINK_CONST0 ) { value = 0; continue; }
      if( varLink == VARLINK_CONST1 ) { value = 1; continue; } 
      if( s.model[varLink] == l_False ) value = 0;
      else if( s.model[varLink] == l_True ) value = 1;
   }
}

unsigned
TmSat::isXorGate( unsigned truth )
{
   return 0;
   if( truth == 0x6666 ) return 2;
   if( truth == 0x9696 ) return 3;
   if( truth == 0x6996 ) return 4;
   return 0;
}

unsigned
TmSat::isXnorGate( unsigned truth )
{
   return 0;
   if( truth == 0x9999 ) return 2;
   if( truth == 0x6969 ) return 3;
   if( truth == 0x9669 ) return 4;
   return 0;
}

void
TmSat::findConstRelation( Solver &s )
{
   for( unsigned i = 1; i < _cir.size(); ++i )
   {
      unsigned &varLink = _varLinks[i];
      if( varLink == UINT_MAX ) continue;
      if( varLink == VARLINK_CONST0 || varLink == VARLINK_CONST1 ) continue;
      assert( varLink < s.nVars() );
      const lbool val = s.value( Var( varLink ) );
      if( val == l_Undef ) continue;
      if( val == l_True ) 
      {
         _assumeConstGate.push_back( AigIndex( i, 0 ) );
         varLink = VARLINK_CONST1;
      }
      else
      {
         assert( val == l_False );
         _assumeConstGate.push_back( AigIndex( i, 1 ) );
         varLink = VARLINK_CONST0;
      }
   }
}


#include <cassert>
#include <climits>
#include "truthTable.h"
#include "truthNPNClass.h"

const unsigned NPNClass::_npnClassNum[5] = { 1, 2, 4, 14, 222 };
NPNClass *NPNClass::_instances[4] = { NULL, NULL, NULL, NULL };

NPNClass::NPNClass( unsigned varnum )
   : _varnum( varnum ), _data( new NPNData[ 1 << (1 << varnum) ] )
{
   setClass();
}

NPNClass::~NPNClass()
{
   delete [] _data;
}

const NPNClass &
NPNClass::s_Instance( unsigned varnum )
{
   assert( varnum > 0 && varnum < 5 );
   NPNClass* &instance = _instances[varnum-1];
   if( instance == NULL )
      instance = new NPNClass( varnum );
   return *instance;
}

void
NPNClass::deleteInstance()
{
   for( unsigned i = 0; i < 3; ++i )
   {
      NPNClass* &instance = _instances[i];
      if( instance != NULL ) delete instance;
      instance = NULL;
   }
}

unsigned
NPNClass::getMaxId() const
{
   return _maxId;
}

unsigned
NPNClass::getSize() const
{
   return 1 << ( 1 << _varnum );
}

unsigned
NPNClass::getClassId( unsigned table ) const
{
   return _data[table]._classId;
}

unsigned
NPNClass::getPhase( unsigned table ) const
{
   return _data[table]._phase;
}

unsigned
NPNClass::getPermute( unsigned table ) const
{
   return _data[table]._permutation;
}

void
NPNClass::setClass()
{
   const unsigned tsize = getSize();
   const unsigned htsize = tsize >> 1;
   const unsigned maxPhase = 1 << ( _varnum );
   unsigned maxPermutation = 1;
   unsigned table, phase, permutation;
   TruthTable32 truth( _varnum, 0 );
   
   _maxId = 0;
   for( permutation = 2; permutation <= _varnum; ++permutation )
      maxPermutation *= permutation;
   for( table = 0; table < tsize; ++table )
      _data[table]._classId = UINT_MAX;
   
   for( table = 0; table < htsize; ++table )
   {
      if( _data[table]._classId != UINT_MAX ) continue;
      for( phase = 0; phase < maxPhase; ++phase )
         for( permutation = 0; permutation < maxPermutation; ++permutation )
         {
            truth.setTable( table );
            truth.changePhasePermute( phase, permutation );
            NPNData &pnData = _data[truth.getTable()];
            assert( pnData._classId == UINT_MAX || pnData._classId == _maxId );
            if( pnData._classId != UINT_MAX ) continue;
            pnData._classId = _maxId;
            pnData._phase = phase;
            pnData._permutation = permutation;
            NPNData &npnData = _data[(~truth).getTable()];
            assert( npnData._classId == UINT_MAX );
            npnData._classId = _maxId;
            npnData._phase = phase | maxPhase;
            npnData._permutation = permutation;
         }
      ++_maxId;
   }
   assert( _varnum != 1 || _maxId == 2 );
   assert( _varnum != 2 || _maxId == 4 );
   assert( _varnum != 3 || _maxId == 14 );
   assert( _varnum != 4 || _maxId  == 222 );
}


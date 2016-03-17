#include <cassert>
#include <climits>
#include "../truth/truthTable.h"
#include "tmCut.h"


static unsigned char cutOrder[16][2] = {
 {4,4}, {4,3}, {3,4}, {3,3}, {4,2}, {2,4},
 {3,2}, {2,3}, {4,1}, {1,4},
 {2,2}, {3,1}, {1,3},
 {2,1}, {1,2}, 
 {1,1}
};

bool TmCut::operator == ( const TmCut &cut2 ) const
{
   if( _signature != cut2._signature ||
       _size != cut2._size ||
       _truth != cut2._truth ) return false;
   for( unsigned i = 0; i < _size; ++i )
      if( _nodes[i] != cut2._nodes[i] ) return false;
   return true;
}

void TmCut::setSignature()
{
   _signature = 0;
   for( unsigned i = 0; i < _size; ++i )
      _signature |= ( 1 << ( _nodes[i] & 0x1F ) );
}

TmCutManager::TmCutManager( const AigCircuit &cir )
   : _cir( cir )
{
   for( unsigned i = 0; i < 5; ++i )
      _cuts[i] = new vector<TmCut> [cir.size()];
}

TmCutManager::~TmCutManager()
{
   for( unsigned i =0; i < 5; ++i )
      delete [] _cuts[i];
}


void
TmCutManager::setCuts()
{
   for( unsigned i = 1; i < _cir.size(); ++i )
      setCut(i);
}

void
TmCutManager::setCut( unsigned index )
{
   if( !_cuts[1][index].empty() ) return;
   const AigNode &node = _cir[index];
   TmCut newCut;
   
   newCut._size = 1;
   newCut._truth = 0xAAAA;
   newCut._nodes[0] = index;
   newCut.setSignature();
   _cuts[1][index].push_back( newCut );
   if( node.isPi() ) return;
   const AigIndex &f0 = node[0];
   const AigIndex &f1 = node[1];
   setCut( f0._index );
   setCut( f1._index );
   for( unsigned i = 0; i < 16; ++i )
   {
      const vector<TmCut> &cuts1 = _cuts[cutOrder[i][0]][f0._index];
      const vector<TmCut> &cuts2 = _cuts[cutOrder[i][1]][f1._index];
      for( vector<TmCut>::const_iterator cut1 = cuts1.begin(); cut1 != cuts1.end(); ++cut1 )
         for( vector<TmCut>::const_iterator cut2 = cuts2.begin(); cut2 != cuts2.end(); ++cut2 )
            if( setNewCut( newCut, *cut1, *cut2, f0._sign, f1._sign ) )
               addNewCut( newCut, _cuts[newCut._size][index] );
   }
}

bool 
TmCutManager::setNewCut( TmCut &newCut, const TmCut &cut1, const TmCut &cut2, bool sign1, bool sign2 )
{
   if( countBitOnes( cut1._signature | cut2._signature ) > 4 ) return false;
   const unsigned limit1 = 4 - cut1._size, limit2 = 4 - cut2._size;
   unsigned index1 = 0, index2 = 0, index3;
   unsigned truth1 = cut1._truth & TruthTable32::VMasks[cut1._size];
   unsigned truth2 = cut2._truth & TruthTable32::VMasks[cut2._size];

   for( index3 = 0; index3 < 4; ++index3 )
   {
      const unsigned n1 = ( index1 < cut1._size ) ? cut1._nodes[index1] : UINT_MAX;
      const unsigned n2 = ( index2 < cut2._size ) ? cut2._nodes[index2] : UINT_MAX;
      if( n1 < n2 )
      {
         if( index3 - index2 >= limit2 ) return false;
         newCut._nodes[index3] = n1;
         ++index1;
         truth2 = TruthTable32::getStretch( truth2, index3 );
         continue;
      }
      if( n1 > n2 )
      {
         if( index3 - index1 >= limit1 ) return false;
         newCut._nodes[index3] = n2;
         ++index2;
         truth1 = TruthTable32::getStretch( truth1, index3 );
         continue;
      }
      if( n1 == UINT_MAX ) break;
      newCut._nodes[index3] = n1;
      ++index1; ++index2;
   }
   assert( index1 == cut1._size );
   assert( index2 == cut2._size );
   if( sign1 ) truth1 = ~truth1;
   if( sign2 ) truth2 = ~truth2;
   newCut._size = index3;
   newCut._truth = truth1 & truth2 & TruthTable32::VMasks[newCut._size];
   for( ; index3 < 4; ++index3 )
      newCut._truth = TruthTable32::getStretch( newCut._truth, index3 );
   if( newCut._truth == 0 || newCut._truth == TruthTable32::VMasks[4] )
      newCut._size = 0;
   newCut.setSignature();
   return true;
}

void
TmCutManager::addNewCut( TmCut &newCut, vector<TmCut> &cuts )
{
   if( cuts.size() > 24 ) return;
   if( newCut._size == 3 && cuts.size() > 16 ) return;
   if( newCut._size == 4 && cuts.size() > 8 ) return;
   for( vector<TmCut>::const_iterator cut = cuts.begin(); cut != cuts.end(); ++cut )
      if( newCut == *cut ) return;
   cuts.push_back( newCut );
}


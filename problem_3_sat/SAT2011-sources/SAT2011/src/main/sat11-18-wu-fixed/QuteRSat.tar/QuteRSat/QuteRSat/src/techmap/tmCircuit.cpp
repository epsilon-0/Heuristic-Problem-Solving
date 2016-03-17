#include <iostream>
#include "tmCircuit.h"

void
TmCircuit::addGate( const vector<AigIndex> &fanins, unsigned truth )
{
   push_back( TmGate( fanins, truth ) );
}

void
TmCircuit::addPi()
{
   vector<AigIndex> fanins;
   
   _piList.push_back( AigIndex( size(), 0 ) );
   addGate( fanins, 0xAAAA );
}

void
TmCircuit::addPo( AigIndex po )
{
   _poList.push_back( po );
}

void
TmCircuit::mapFrom( const AigCircuit &cir )
{
   unsigned i, truth;
   vector<AigIndex> fanins;
   vector<unsigned> links( cir.size() );
   
   links[0] = 0;
   addGate( fanins, 0 );
   for( i = 0; i < cir.getPiNum(); ++i )
   {
      const unsigned piIndex = cir.getPi(i)._index;
      links[piIndex] = size();
      addPi();
   }
   fanins.resize( 2 );
   for( i = 1; i < cir.size(); ++i )
   {
      const AigNode &node = cir[i];
      if( node.isPi() ) continue;
      links[i] = size();
      if( node._fanin[1]._sign )
         if( node._fanin[0]._sign ) truth = 0x1111;
         else truth = 0x2222;
      else if( node._fanin[0]._sign ) truth = 0x4444;
      else truth = 0x8888;
      fanins[0]._index = links[node._fanin[0]._index];
      fanins[0]._sign = 0;
      fanins[1]._index = links[node._fanin[1]._index];
      fanins[1]._sign = 0;
      addGate( fanins, truth );
   }
   for( i = 0; i < cir.getPoNum(); ++i )
   {
      const AigIndex po = cir.getPo(i);
      addPo( AigIndex( links[po._index], po._sign ) );
   }
}


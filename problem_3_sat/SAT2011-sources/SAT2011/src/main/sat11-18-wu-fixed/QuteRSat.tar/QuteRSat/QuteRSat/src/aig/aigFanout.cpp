#include "aigCircuit.h"
#include "aigFanout.h"

void
AigFanout::setFanout( const AigCircuit &cir )
{
   resize( cir.size() );
   for( unsigned i = 1; i < cir.size(); ++i )
   {
      const AigNode &node = cir[i];
      if( node.isPi() ) continue;
      (*this)[node._fanin[0]._index].push_back( i );
      (*this)[node._fanin[1]._index].push_back( i );
   }
}


void
AigFanoutNum::setFanoutNum( const AigCircuit &cir )
{
   clear();
   resize( cir.size(), 0 );
   for( unsigned i = 1; i < cir.size(); ++i )
   {
      const AigNode &node = cir[i];
      if( node.isPi() ) continue;
      ++(*this)[node._fanin[0]._index];
      ++(*this)[node._fanin[1]._index];
   }
}

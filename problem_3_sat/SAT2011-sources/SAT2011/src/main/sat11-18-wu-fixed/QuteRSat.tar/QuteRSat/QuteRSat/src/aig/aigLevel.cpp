#include "aigCircuit.h"
#include "aigLevel.h"

AigLevel *AigLevel::_publicPtr = NULL;

unsigned
AigLevel::getMaxLevel() const
{
   return _maxLevel;
}
 
void
AigLevel::setLevel( const AigCircuit &cir )
{
   _maxLevel = 0;
   resize( cir.size() );
   for( unsigned i = 0; i < cir.size(); ++i )
      updateLevel( cir, i );
}

void
AigLevel::updateLevel( const AigCircuit &cir, unsigned index )
{
   if( index >= size() ) resize( index + 1, 0 );
   unsigned &level = (*this)[index];
   const AigNode &node = cir[index];
   if( node.isPi() ) level = 0;
   else if( (*this)[node._fanin[0]._index] > (*this)[node._fanin[1]._index] )
      level =  (*this)[node._fanin[0]._index] + 1;
   else level =  (*this)[node._fanin[1]._index] + 1;
   if( _maxLevel < level ) _maxLevel = level;
}

bool
AigLevel::sortHighFirst( unsigned a, unsigned b )
{
   return (*_publicPtr)[a] > (*_publicPtr)[b];
}


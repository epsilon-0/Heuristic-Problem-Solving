#include <cassert>
#include "utilMark.h"

void
UtilMark::initialize( unsigned num )
{
   _globalMark = 1;
   clear();
   resize( num );
}

void
UtilMark::clearMark()
{
   if( ++_globalMark == 0 )
   {
      _globalMark = 1;
      for( unsigned i = 0; i < size(); ++i )
         (*this)[i] = 0;
   }
}

void
UtilMark::setMark( unsigned index )
{
   assert( index < size() );
   (*this)[index] = _globalMark;
}

void
UtilMark::clearMark( unsigned index )
{
   (*this)[index] = _globalMark - 1;
}

bool
UtilMark::isMark( unsigned index ) const
{
   return (*this)[index] == _globalMark;
}

#include <cassert>
#include <climits>
#include <iostream>
#include "aigCircuit.h"
#include "aigDfs.h"

void
AigDfs::perform( const AigCircuit &orgCircuit, AigCircuit &newCircuit, bool travseAll )
{
   newCircuit.initialize( orgCircuit, _links );
   for( unsigned i = 0; i < orgCircuit.getDffNum(); ++i )
      setDfs( orgCircuit.getDff(i)._index, orgCircuit, newCircuit );
   for( unsigned i = 0; i < orgCircuit.getPoNum(); ++i )
      setDfs( orgCircuit.getPo(i)._index, orgCircuit, newCircuit );
   if( travseAll )
      for( unsigned i = 0; i < orgCircuit.size(); ++i )
         setDfs( i, orgCircuit, newCircuit );
   newCircuit.finalize( orgCircuit, _links );
}

void
AigDfs::perform( const AigCircuit &orgCircuit, AigCircuit &newCircuit, const vector<AigIndex> &piList, const vector<AigIndex> &poList )
{
   vector<AigIndex>::const_iterator vi;
      
   _links.clear();
   _links.resize( orgCircuit.size() );
   _links[0]._data = 0;
   for( vi = piList.begin(); vi != piList.end(); ++vi )
      _links[vi->_index] = newCircuit.pushPi();
   for( vi = poList.begin(); vi != poList.end(); ++vi )
      setDfs( vi->_index, orgCircuit, newCircuit );
   for( vi = poList.begin(); vi != poList.end(); ++vi )
      newCircuit.addPo( vi->getLink( _links ) ); 
}

const vector<AigIndex> &
AigDfs::getLinks() const
{
   return _links;
}

bool
AigDfs::check( const AigCircuit &circuit ) const
{
   for( unsigned i = 0; i < circuit.size(); ++i )
   {
      const AigNode &node = circuit[i];
      if( node.isPi() ) continue;
      if( i <= node._fanin[0]._index || i <= node._fanin[1]._index ) return false;
   }
   return true;
}

void
AigDfs::setDfs( unsigned index, const AigCircuit &orgCircuit, AigCircuit &newCircuit )
{
   if( _links[index]._data != UINT_MAX ) return;
   assert( _gstack.empty() );
   _gstack.push_back( index );
   do
   {
      index = _gstack.back();
      assert( !orgCircuit[index].isPi() );
      _links[index]._data = 1;                  //avoid combinational loop  
      const AigNode &node = orgCircuit[index];
      if( _links[node._fanin[0]._index]._data == UINT_MAX )
      {
         index = node._fanin[0]._index;
         _gstack.push_back( index );
         continue;
      }
      if( _links[node._fanin[1]._index]._data == UINT_MAX )
      {
         index = node._fanin[1]._index;
         _gstack.push_back( index );
         continue;
      }
      _links[index] = newCircuit.pushNode( node._fanin[0].getLink( _links ), node._fanin[1].getLink( _links ) );
      _gstack.pop_back();
   } while( !_gstack.empty() );
}

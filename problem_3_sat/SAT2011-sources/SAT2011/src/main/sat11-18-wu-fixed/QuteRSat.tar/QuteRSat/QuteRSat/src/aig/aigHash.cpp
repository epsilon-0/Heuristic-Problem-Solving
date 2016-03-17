#include <cassert>
#include <climits>
#include <algorithm>
#include "aigHash.h"

size_t
AigHashFunc::operator() ( const AigNode &a ) const
{
   return 2000000011 * unsigned( a[0]._data ) + 2000000033 * unsigned( a[1]._data );
}

/*
size_t
hash_value( const AigNode & node )
{
   size_t seed = 0;
   boost::hash_combine( seed, node._fanin[0]._data );
   boost::hash_combine( seed, node._fanin[1]._data );
   return seed;
}
*/

AigHash::AigHash()
{
   AigNode emp;
   emp[0]._data = UINT_MAX;
   emp[1]._data = UINT_MAX;
   _hashTable.set_empty_key( emp );
   emp[1]._data = UINT_MAX - 1;
   _hashTable.set_deleted_key( emp );
}

void
AigHash::perform( const AigCircuit &orgCircuit, AigCircuit &newCircuit )
{
   newCircuit.initialize( orgCircuit, _links );
   for( unsigned i = 1; i < orgCircuit.size(); ++i )
   {
      const AigNode &orgNode = orgCircuit[i];
      if( orgNode.isPi() ) continue;
      AigIndex fanin0 = orgNode._fanin[0].getLink( _links );
      AigIndex fanin1 = orgNode._fanin[1].getLink( _links );
      if( fanin1 < fanin0 ) swap( fanin0, fanin1 );
      const AigIndex link = hashNode( fanin0, fanin1, newCircuit.size(), true );
      _links[i] = link;
      if( link._index == newCircuit.size() ) newCircuit.pushNode( fanin0, fanin1 );
   }
   newCircuit.finalize( orgCircuit, _links );
}

void
AigHash::hashCircuit( const AigCircuit &circuit )
{
   for( unsigned i = 1; i < circuit.size(); ++i )
   {
      const AigNode &node = circuit[i];
      if( node.isPi() ) continue;
      if( node._fanin[0]._data <= node._fanin[1]._data )
         hashNode( node._fanin[0], node._fanin[1], i, true );
      else  hashNode( node._fanin[1], node._fanin[0], i, true );
   }
}

AigIndex
AigHash::hashNode( AigIndex fanin0, AigIndex fanin1, unsigned index, bool insertHash )
{
   return hashNode( AigNode( fanin0, fanin1 ), index, insertHash );
/*
   assert( !(fanin1 < fanin0) );
   if( fanin0._data == 0 ) return AigIndex(0);
   if( fanin0._data == 1 ) return fanin1;
   if( fanin0 == fanin1 ) return fanin0;
   if( fanin0._index == fanin1._index ) return AigIndex(0);
   if( fanin1._data == UINT_MAX ) return fanin1;
   const AigNode node( fanin0, fanin1 );
   google::dense_hash_set<AigHashData, AigHashFunc, AigHashEqual>::const_iterator chi = _hashTable.find( node );
   if( chi != _hashTable.end() )
      return AigIndex( chi->second, 0 );
   if( index == UINT_MAX ) return AigIndex( UINT_MAX );
   if( insertHash ) _hashTable.insert( chi, );
   return AigIndex( index, 0 );
*/
}

AigIndex
AigHash::hashNode( const AigNode &node, unsigned index, bool insertHash )
{
   const AigIndex &fanin0 = node[0];
   const AigIndex &fanin1 = node[1];
   assert( !(fanin1 < fanin0) );
   if( fanin0._data == 0 ) return AigIndex(0);
   if( fanin0._data == 1 ) return fanin1;
   if( fanin0 == fanin1 ) return fanin0;
   if( fanin0._index == fanin1._index ) return AigIndex(0);
   if( fanin1._data == UINT_MAX ) return fanin1;
   pair<google::dense_hash_map<AigNode, uint32_t, AigHashFunc>::iterator,bool> res = 
      _hashTable.insert( make_pair( node, uint32_t(index) ) );
   if( !res.second ) index = res.first->second;
   else if( !insertHash ) _hashTable.erase( res.first );
   if( index == UINT_MAX ) return AigIndex( UINT_MAX );
   return AigIndex( index, 0 );
}


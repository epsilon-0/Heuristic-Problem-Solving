#include <iomanip>
#include <cassert>
#include <climits>
#include "aigCircuit.h"

AigIndex::AigIndex()
   : _data( UINT_MAX )
{
}

AigIndex::AigIndex( const AigIndex &index )
   : _data( index._data )
{
}

AigIndex::AigIndex( unsigned data )
   : _data ( data )
{
}

AigIndex::AigIndex( unsigned index, bool sign )
   : _sign( sign ), _index( index )
{
}

AigIndex
AigIndex::getLink( const vector<AigIndex> &links ) const
{
   assert( _index < links.size() );
   if( links[_index]._data == UINT_MAX ) return AigIndex( UINT_MAX );
   return AigIndex( links[_index]._index, _sign ^ links[_index]._sign );
}

AigIndex
AigIndex::getLink( const vector<unsigned> &links ) const
{
   assert( _index < links.size() );
   if( links[_index] == UINT_MAX ) return AigIndex( UINT_MAX );
   return AigIndex( links[_index], _sign );
}

AigIndex
AigIndex::operator ~() const
{
   AigIndex inv(*this);
   inv._sign = !inv._sign;
   return inv;
}

bool
AigIndex::operator < ( const AigIndex &b ) const
{
   return ( _data < b._data );
}

bool
AigIndex::operator == ( const AigIndex &b ) const
{
   return ( _data == b._data );
}

AigNode::AigNode()
{
}

AigNode::AigNode( AigIndex fanin0, AigIndex fanin1 )
{
   _fanin[0] = fanin0;
   _fanin[1] = fanin1;
}

bool
AigNode::operator == ( const AigNode &b ) const
{
   return ( _fanin[0] == b._fanin[0] && _fanin[1] == b._fanin[1] );
}

bool
AigNode::isPi() const
{
   return _fanin[1]._data == 0;
}

AigCircuit::AigCircuit()
   : _nodes( 1 )
{
   _nodes[0]._fanin[0]._data = 0;
   _nodes[0]._fanin[1]._data = 0;
}

void
AigCircuit::clear()
{
   _nodes.resize( 1 );
   _piList.clear();
   _poList.clear();
   _dffList.clear();
   _piName.clear();
   _poName.clear();
   _dffName.clear();
}

void
AigCircuit::reserve( unsigned num )
{
   _nodes.reserve( num );
}

void
AigCircuit::resize( unsigned num )
{
   _nodes.resize( num );
}

unsigned
AigCircuit::size() const
{
   return _nodes.size();
}

void
AigCircuit::swap( AigCircuit &cir )
{
   _nodes.swap( cir._nodes );
   _piList.swap( cir._piList );
   _poList.swap( cir._poList );
   _dffList.swap( cir._dffList );
   _piName.swap( cir._piName );
   _poName.swap( cir._poName ); 
   _dffName.swap( cir._dffName );
}

unsigned
AigCircuit::getPiNum() const
{ 
   return _piList.size();
}

unsigned
AigCircuit::getPoNum() const
{
   return _poList.size();
}

unsigned
AigCircuit::getDffNum() const
{ 
   return _dffList.size();
}

AigIndex
AigCircuit::getPi( unsigned index ) const
{ 
   return _piList[index];
}

AigIndex
AigCircuit::getPo( unsigned index ) const 
{ 
   return _poList[index];
}

AigIndex
AigCircuit::getDff( unsigned index ) const 
{ 
   return _dffList[index];
}

const vector<AigNode> &
AigCircuit::getNodes() const
{
   return _nodes;
}

const AigNode &
AigCircuit::operator [] ( unsigned index ) const
{ 
   assert( index < size() );
   return _nodes[index];
}

AigNode &
AigCircuit::operator [] ( unsigned index )
{ 
   assert( index < size() );
   return _nodes[index];
}

void
AigCircuit::addPi( AigIndex index )
{
   _piList.push_back( index );
   _nodes[index._index]._fanin[1]._data = 0;
}

void
AigCircuit::addDff( AigIndex index )
{
   _dffList.push_back( index );
   _nodes[index._index]._fanin[1]._data = 0;
}

AigIndex
AigCircuit::pushPi()
{
   _piList.push_back( AigIndex( _nodes.size(), 0 ) );
   AigNode pi;
   pi._fanin[1]._data = 0;
   _nodes.push_back( pi );
   return _piList.back();
}

AigIndex
AigCircuit::pushDff( AigIndex fanin )
{
   _dffList.push_back( AigIndex( _nodes.size(), 0 ) );
   AigNode dff;
   dff._fanin[0] = fanin;
   dff._fanin[1]._data = 0;
   _nodes.push_back( dff );
   return _dffList.back();
}

void
AigCircuit::addPo( AigIndex index )
{
   _poList.push_back( index );
}

AigIndex
AigCircuit::pushNode( AigIndex fanin0, AigIndex fanin1 )
{
   AigNode node;
   node._fanin[0] = fanin0;
   node._fanin[1] = fanin1;
   AigIndex index( _nodes.size(), 0 );
   _nodes.push_back( node );
   return index;
}

void
AigCircuit::popNode()
{
   _nodes.pop_back();
}

void
AigCircuit::initialize( const AigCircuit &orgCircuit, vector<AigIndex> &links )
{
   links.clear();
   links.resize( orgCircuit.size() );
   links[0]._data = 0;
   for( vector<AigIndex>::const_iterator vi = orgCircuit._piList.begin();
        vi != orgCircuit._piList.end(); ++vi )
      links[vi->_index] = pushPi();
   for( vector<AigIndex>::const_iterator vi = orgCircuit._dffList.begin();
        vi != orgCircuit._dffList.end(); ++vi )
      links[vi->_index] = pushDff( orgCircuit[vi->_index]._fanin[1] );
}

void
AigCircuit::finalize( const AigCircuit &orgCircuit, const vector<AigIndex> &links )
{
   for( vector<AigIndex>::const_iterator vi = orgCircuit._poList.begin();
        vi != orgCircuit._poList.end(); ++vi )
      addPo( vi->getLink( links ) );
   for( vector<AigIndex>::const_iterator vi = orgCircuit._dffList.begin();
        vi != orgCircuit._dffList.end(); ++vi )
   {
      AigNode &dff = _nodes[ links[vi->_index]._index ];
      dff._fanin[0] = dff._fanin[0].getLink( links );
   }
}

void
AigCircuit::copyFrom( const AigCircuit &orgCircuit, vector<AigIndex> &links )
{
   links[0]._data = 0;
   for( unsigned i = 1; i < orgCircuit.size(); ++i  )
   {
      AigIndex &link = links[i];
      if( link._data != UINT_MAX ) continue;
      const AigNode &node = orgCircuit[i];
      if( node.isPi() )
      {
         link = pushPi();
         continue;
      }
      link = pushNode( node[0].getLink( links ), node[1].getLink( links ) );
   }
}

AigIndex
AigCircuit::pushOr( AigIndex fanin0, AigIndex fanin1 )
{
   return ~pushNode( ~fanin0, ~fanin1 );
}

AigIndex
AigCircuit::pushXor( AigIndex fanin0, AigIndex fanin1 )
{
   return pushOr( pushNode( fanin0, ~fanin1 ), pushNode( ~fanin0, fanin1 ) );
}

void
AigCircuit::setPiName( unsigned index, const string &name )
{
   if( _piName.size() <= index ) _piName.resize( index + 1 );
   _piName[index] = name;
}

void
AigCircuit::setPoName( unsigned index, const string &name )
{
   if( _poName.size() <= index ) _poName.resize( index + 1 );
   _poName[index] = name;
}

void
AigCircuit::setDffName( unsigned index, const string &name )
{
   if( _dffName.size() <= index ) _dffName.resize( index + 1 );
   _dffName[index] = name;
}

const string &
AigCircuit::getPiName( unsigned index ) const
{
   assert( index < _piName.size() );
   return _piName[index];
}

const string &
AigCircuit::getPoName( unsigned index ) const
{
   assert( index < _poName.size() );
   return _poName[index];
}

const string &
AigCircuit::getDffName( unsigned index ) const
{
   assert( index < _dffName.size() );
   return _dffName[index];
}

unsigned
AigCircuit::getPiNameNum() const
{
   return _piName.size();
}

unsigned
AigCircuit::getPoNameNum() const
{
   return _poName.size();
}

unsigned
AigCircuit::getDffNameNum() const
{
   return _dffName.size();
}

void
AigCircuit::report( ostream &os ) const
{
   os << "i/l/o/s " << setw(7) << getPiNum() << " " << setw(7) << getDffNum() << " " << setw(7) << getPoNum()
        << setw(10) << size() - getPiNum() - getDffNum() - 1 << endl;
}


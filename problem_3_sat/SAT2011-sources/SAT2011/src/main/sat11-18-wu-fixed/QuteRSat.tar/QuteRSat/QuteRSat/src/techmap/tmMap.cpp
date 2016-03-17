#include <cassert>
#include <climits>
#include <ctime>
#include <iostream>
#include "tmMap.h"


static unsigned and2truth[4] = { 0x1111,0x2222,0x4444,0x8888 };
static unsigned and3truth[8] = { 0x0101, 0x0202, 0x0404, 0x0808, 0x1010, 0x2020, 0x4040, 0x8080 };
static unsigned and4truth[16] = { 0x0001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080,
                                  0x0100, 0x0200, 0x0400, 0x0800, 0x1000, 0x2000, 0x4000, 0x8000 };
static unsigned char andinv[16][4] = { {1,1,1,1}, {0,1,1,1}, {1,0,1,1}, {0,0,1,1}, {1,1,0,1}, {0,1,0,1}, {1,0,0,1}, {0,0,0,1},
                                       {1,1,1,0}, {0,1,1,0}, {1,0,1,0}, {0,0,1,0}, {1,1,0,0}, {0,1,0,0}, {1,0,0,0}, {0,0,0,0} };

TmMap::TmMap( const AigCircuit &cir, const TruthToCnf &toCnf  )
   : _cir( cir ), _truthToCnf( toCnf ), _tmCutMan( cir ), _choices( cir.size() ),
     _collectBigAnd( true )
{
   _fanoutNum.setFanoutNum( cir );
   _tmCutMan.setCuts();
   _links.resize( cir.size() );
   _refs.resize( cir.size(), 0 );
   _marks.initialize( 2*cir.size() );
   _bigAndFanins = new vector<AigIndex> [ cir.size() ];
}

TmMap::~TmMap()
{
   delete [] _bigAndFanins;
}

double
TmMap::getCost( unsigned truth, unsigned varNum ) const
{
//   return 10 * static_cast<double>( _truthToCnf.getRealClauseNum( truth, varNum ) );
   return 10 * static_cast<double>( _truthToCnf.getCost( truth ) );
}

double
TmMap::getCost( const TmCut &cut ) const
{
   double cost = getCost( cut._truth, cut._size );
   for( unsigned i = 0; i < cut._size; ++i )
   {
      const unsigned index = cut._nodes[i];
      const unsigned fanoutNum = ( _fanoutNum[index] > 0 ) ? _fanoutNum[index] : 1;
      cost += _choices[index]._cost / fanoutNum;
   }
   return cost;
}

double
TmMap::getAndCost() const
{
   double cost = 0;
   for( unsigned i = 0; i < _fanins.size(); ++i )
   {
      const unsigned index = _fanins[i]._index;
      const unsigned fanoutNum = ( _fanoutNum[index] > 0 ) ? _fanoutNum[index] : 1;
      cost += _choices[index]._cost / fanoutNum;
   }
   const double weight = 1;
   //const double weight = ( _fanins.size() <= 100 ) ? 1 : 100 / _fanins.size();
   cost = weight * cost + 10 * ( _fanins.size() + 1 );
   return cost;  
}

void
TmMap::setChoices()
{
   for( unsigned i = 1; i < _cir.size(); ++i )
   { 
      TmChoice &choice = _choices[i];
      choice._cost = -1;
      choice._cutSize = 1;
      choice._cutIndex = 0;
      /*setBigAnd( i );
      if( _fanins.empty() )
      {
         choice._cost = 0;
         choice._cutSize = 0;
         choice._cutIndex = 255;
      }
      else if( _fanins.size() > 4 )
      {
         choice._cost = getAndCost();
         choice._cutSize = _fanins.size();
         choice._cutIndex = 255;
      }*/
      for( unsigned j = 0; j < 5; ++j )
      {
         const vector<TmCut> &cuts = _tmCutMan.getCuts( j, i );
         assert( cuts.size() < 255 );
         for( unsigned k = 0; k < cuts.size(); ++k )
         {
            if( j == 1 && k == 0 ) continue;   //self node
            const double cost = getCost( cuts[k] );
            if( cost > choice._cost && choice._cost > 0 ) continue;
            choice._cost = cost;
            choice._cutSize = j;
            choice._cutIndex = k;
         }
      }
      if( choice._cost < 0 ) choice._cost = 0;
   }
}

void
TmMap::markChoices()
{
   for( unsigned i = 0; i < _cir.getPoNum(); ++i )
      ++_refs[_cir.getPo(i)._index];
   for( unsigned i = _cir.size() - 1; i > 0; --i )
   {
      if( _refs[i] == 0 ) continue;
      const TmChoice &choice = _choices[i];
      if( choice._cutIndex == 255 )
      {
         if( choice._cutSize == 0 ) continue;
         setBigAnd( i );
         _bigAndFanins[i] = _fanins;
         for( unsigned j = 0; j < _fanins.size(); ++j )
            ++_refs[_fanins[j]._index];
         continue;
      }
      assert( choice._cutIndex < _tmCutMan.getCuts( choice._cutSize, i ).size() );
      const TmCut &cut = _tmCutMan.getCuts( choice._cutSize, i )[ choice._cutIndex ];
      for( unsigned j = 0; j < cut._size; ++j )
         ++_refs[cut._nodes[j]];
      /*cout << i << ": " << cut._truth << ": ";
      for( unsigned j = 0; j < cut._size; ++j )
         cout << cut._nodes[j] << " ";
      cout << endl;*/
   }
}

void
TmMap::decRef( unsigned index )
{
   _gstack.clear();
   _gstack.push_back( index );
   for( unsigned i = 0; i < _gstack.size(); ++i )
   {
      const unsigned index = _gstack[i];
      const TmChoice &choice = _choices[index];
      if( choice._cutSize == 0 ) continue;
      if( choice._cutIndex == 255 )
      {
         assert( _bigAndFanins[index].size() == choice._cutSize );
         const vector<AigIndex> &fanins = _bigAndFanins[index];
         for( unsigned j = 0; j < fanins.size(); ++j )
         {
            assert( _refs[fanins[j]._index] > 0 );
            if( --_refs[fanins[j]._index] == 0 )
               _gstack.push_back( fanins[j]._index );
         }
         continue;
      }
      const TmCut &cut = _tmCutMan.getCuts( choice._cutSize, index )[ choice._cutIndex ];
      for( unsigned j = 0; j < cut._size; ++j )
      {
         assert( _refs[cut._nodes[j]] > 0 );
         if( --_refs[cut._nodes[j]] == 0 )
            _gstack.push_back( cut._nodes[j] );
      }
   }
}

void
TmMap::optimizeChoices()
{
   for( unsigned i = _cir.size() - 1; i > 0; --i )
   {
      if( _refs[i] == 0 ) continue;
      TmChoice &choice = _choices[i];
      if( choice._cutSize == 0 ) continue;
      double minCost;
      _marks.clearMark();
      if( choice._cutIndex == 255 )
      {
         assert( _bigAndFanins[i].size() == choice._cutSize );
         const vector<AigIndex> &fanins = _bigAndFanins[i];
         minCost = 10 * ( fanins.size() + 1 );
         for( unsigned j = 0; j < fanins.size(); ++j )
         {
            _marks.setMark( fanins[j]._index );
            if( _refs[fanins[j]._index] == 1 )
               minCost += _choices[fanins[j]._index]._cost;  
         }
      }
      else
      {
         const TmCut &cut = _tmCutMan.getCuts( choice._cutSize, i )[ choice._cutIndex ];
         minCost = 10 * getCost( cut._truth, cut._size );
         for( unsigned j = 0; j < cut._size; ++j )
         {
            _marks.setMark( cut._nodes[j] );
            if( _refs[cut._nodes[j]] == 1 )
               minCost += _choices[cut._nodes[j]]._cost;  
         }
      }
      unsigned bestSize = 0, bestIndex = 0;
      for( unsigned j = 1; j < 5; ++j )
      {
         const vector<TmCut> &cuts = _tmCutMan.getCuts( j, i );
         for( unsigned k = 0; k < cuts.size(); ++k )
         {
            if( j == 1 && k == 0 ) continue;   //self node
            const TmCut &cut = cuts[k];
            double cost = 10 * getCost( cut._truth, cut._size );
            unsigned h = 0;
            for( ; h < cut._size; ++h )
            {
               const unsigned index = cut._nodes[h];
               const int ref = _refs[index];
               if( ref == 0 ) break;
               if( _marks.isMark( cut._nodes[h] ) && ref == 1 ) continue;
               cost += _choices[index]._cost;
            }
            assert( cut._size > 0 );
            //score /= cut._size;
            if( h != cut._size || minCost < cost ) continue;
            minCost = cost;
            bestSize = j;
            bestIndex = k;
         }
      }
      if( bestSize == 0 ) continue;
      const TmCut &cut = _tmCutMan.getCuts( bestSize, i )[ bestIndex ];
      for( unsigned j = 0; j < cut._size; ++j )
         ++_refs[cut._nodes[j]];
      decRef( i );
      choice._cutSize = bestSize;
      choice._cutIndex = bestIndex;
   }
}

void
TmMap::setBigAnd( unsigned index )
{
   //_fanins.resize(1);
   //return;
   unsigned i, send;
   _gstack.clear();
   _fanins.clear();
   _gstack.push_back( index );
   for( i = 0; i < _gstack.size(); ++i )
   {
      const AigNode &node = _cir[ _gstack[i] ];
      if( _gstack.size() > 500 ) break;
      if( node.isPi() ) continue;
      const AigIndex f0 = node[0];
      const AigIndex f1 = node[1];
      if( !f0._sign )
      {
         assert( _fanoutNum[f0._index] > 0 );
         if( --_fanoutNum[f0._index] == 0 )
            _gstack.push_back( f0._index );
      }
      if( !f1._sign )
      {
         assert( _fanoutNum[f1._index] > 0 );
         if( --_fanoutNum[f1._index] == 0 )
            _gstack.push_back( f1._index );
      }
   }
   send = i;
   _marks.clearMark();
   for( i = 0; i < _gstack.size(); ++i )
   {
      const AigNode &node = _cir[ _gstack[i] ];
      if( node.isPi() ) continue;
      const unsigned f0index = node[0]._index;
      const unsigned f1index = node[1]._index;
      if( ( _cir[node[0]._index].isPi() || _fanoutNum[f0index] > 0 ) && !_marks.isMark( node[0]._data ) )
      {
         _marks.setMark( node[0]._data );
         _fanins.push_back( node[0] );
         if( _marks.isMark( node[0]._data^1 ) )
         {
            _fanins.clear();
            break;
         }
      }
      if( ( _cir[node[1]._index].isPi() || _fanoutNum[f1index] > 0 ) && !_marks.isMark( node[1]._data ) )
      {
         _marks.setMark( node[1]._data );
         _fanins.push_back( node[1] );
         if( _marks.isMark( node[1]._data^1 ) )
         {
            _fanins.clear();
            break;
         }
      }
   }
   for( i = 0; i < send; ++i )
   {
      const AigNode &node = _cir[ _gstack[i] ];
      if( node.isPi() ) continue;
      const AigIndex f0 = node[0];
      const AigIndex f1 = node[1];
      if( !f0._sign )
         ++_fanoutNum[f0._index];
      if( !f1._sign )
         ++_fanoutNum[f1._index];
   }
}

static inline unsigned isAndType( unsigned cutSize, unsigned truth )
{
   if( cutSize == 0 ) return 255;
   if( cutSize == 1 )
   {
      assert( truth == 0xAAAA || truth == 0x5555 );
      if( truth == 0xAAAA )
         return 1;
      return 255;
   }
   if( cutSize == 2 )
   {
      for( unsigned i = 0; i < 4; ++i )
         if( truth == and2truth[i] )
            return i;
      return 255;
   }
   if( cutSize == 3 )
   {
      for( unsigned i = 0; i < 8; ++i )
         if( truth == and3truth[i] )
            return i;
      return 255;
   }
   assert( cutSize == 4 );
   for( unsigned i = 0; i < 16; ++i )
      if( truth == and4truth[i] )
         return i;
   return 255;
}

void
TmMap::collectBigAnd()
{
   unsigned i, j, k;
   vector<unsigned> andTypes;

   for( i = _cir.size() - 1; i > 0; --i )
   {
      if( _refs[i] == 0 ) continue;
      TmChoice &choice = _choices[i];
      assert( choice._cutSize < 5  && choice._cutIndex < 250 );
      unsigned andType = isAndType( choice._cutSize, _tmCutMan.getCuts( choice._cutSize, i )[ choice._cutIndex ]._truth );
      if( andType == 255 ) continue;
      bool const0 = false;
      andTypes.clear();
      _marks.clearMark();
      _gstack.clear();
      _fanins.clear();
      _gstack.push_back( i );
      andTypes.push_back( andType );
      for( j = 0; j < _gstack.size(); ++j )
      {
         const unsigned index = _gstack[j];
         const unsigned at = andTypes[j];
         const TmCut &cut = _tmCutMan.getCuts( _choices[index]._cutSize, index )[ _choices[index]._cutIndex ];
         for( k = 0; k < cut._size; ++k )
         {
            const unsigned findex = cut._nodes[k];
            const unsigned gindex = (findex << 1 ) | andinv[at][k];
            assert( _refs[findex] > 0 );
            --_refs[findex];
            if( _marks.isMark( gindex^1 )  ) const0 = true;
            if( !const0 && _refs[findex] == 0 && andinv[at][k] == 0 &&
                ( andType = isAndType( _choices[findex]._cutSize,  
                     _tmCutMan.getCuts( _choices[findex]._cutSize, findex )[ _choices[findex]._cutIndex ]._truth )
                ) != 255 )
            {
               assert( !_marks.isMark( gindex^1 ) );
               andTypes.push_back( andType );
               _gstack.push_back( findex );
               _marks.clearMark( gindex );
               continue;
            }
            if( _marks.isMark( gindex ) || _marks.isMark( gindex^1 ) ) continue;
            _fanins.push_back( AigIndex( gindex ) );
            _marks.setMark( gindex );
         }
      }
      if( const0 )
      {
         choice._cutSize = 0;
         choice._cutIndex = 255;
         for( j = 0; j < _fanins.size(); ++j )
         {
            const unsigned index = _fanins[j]._index;
            if( _refs[index] > 0 || !_marks.isMark( _fanins[j]._data ) ) continue;
            decRef( index );
         }
         continue;
      }
      vector<AigIndex>::iterator vi = _fanins.begin();
      for( vector<AigIndex>::const_iterator cvi = vi; cvi != _fanins.end(); ++cvi )
         if( _marks.isMark( cvi->_data ) )
         {
            *vi++ = *cvi;
            ++_refs[cvi->_index];
         }
      _fanins.resize( vi - _fanins.begin() );
      choice._cutSize = _fanins.size();
      choice._cutIndex = 255; 
      _bigAndFanins[i] = _fanins;
   }
}

void
TmMap::mapTo( TmCircuit &cir )
{
   clock_t tbegin = clock();
   setChoices();
   cout << "c TmMap: Set choices finish." << endl;
   markChoices();
   optimizeChoices();
   if( _collectBigAnd ) collectBigAnd();

   //build choices
   unsigned i, j;
   vector<AigIndex> fanins;

   _links[0]._data = 0;
   cir.addGate( fanins, 0 );
   for( i = 0; i < _cir.getPiNum(); ++i )
   {
      const unsigned piIndex = _cir.getPi(i)._index;
      _links[piIndex]._data = cir.size() << 1;
      _refs[piIndex] = 0;
      cir.addPi();
   }
   unsigned clauseNum = 0, bigAndNum = 0;
   for( i = 1; i < _cir.size(); ++i )
   {
      if( _refs[i] == 0 ) continue;
      const TmChoice &choice = _choices[i];
      _links[i]._data = cir.size() << 1;
      if( choice._cutIndex == 255 )
      {
         assert( _bigAndFanins[i].size() == choice._cutSize );
         ++bigAndNum;
         if( choice._cutSize == 0 )
         {
            fanins.clear();
            _links[i]._data = 0;
            continue;
         }
         fanins = _bigAndFanins[i];
         for( j = 0; j < fanins.size(); ++j )
            fanins[j] = fanins[j].getLink( _links );
         if( fanins.size() == 1 )
         {
            _links[i] = fanins[0];
            continue;
         }
         cir.addGate( fanins, 0x10000 );
         clauseNum += fanins.size() + 1;
         continue;
      }
      const TmCut &cut = _tmCutMan.getCuts( choice._cutSize, i )[ choice._cutIndex ];
      fanins.resize( cut._size );
      //cout << "Map: " << cir.size() << ": " << (int)cut._size << endl;
      for( j = 0; j < cut._size; ++j )
         fanins[j] = _links[ cut._nodes[j] ];
      if( fanins.size() == 0 )
      {
         assert( cut._truth == 0x0000 || cut._truth == 0xFFFF );
         if( cut._truth == 0x0000 ) _links[i]._data = 0;
         else _links[i]._data = 1;
         continue;
      }
      if( fanins.size() == 1 )
      {
         assert( cut._truth == 0xAAAA || cut._truth == 0x5555 );
         _links[i] = fanins[0];
         continue;
      }
      cir.addGate( fanins, cut._truth );
      clauseNum += _truthToCnf.getClauseNum( cut._truth ) + _truthToCnf.getClauseNum( ~cut._truth & 0xFFFF );
   }
   for( i = 0; i < _cir.getPiNum(); ++i )
   {
      const unsigned piIndex = _cir.getPi(i)._index;
      ++_refs[piIndex];
   }
   for( i = 0; i < _cir.getPoNum(); ++i )
   {
      const AigIndex po = _cir.getPo(i);
      assert( _refs[po._index] > 0 );
      cir.addPo( po.getLink( _links ) );
   }
   cout << "c TmMap: Set big and: " << bigAndNum << endl
        << "c TmMap: Origin: " << _cir.size() << " ClauseNum: " << 3*( _cir.size() - _cir.getPiNum() - 1 ) 
        << " --> New: " << cir.size() << " ClauseNum: " << clauseNum << endl
        << "c TmMap: Time: " << static_cast<double>( clock() - tbegin ) / CLOCKS_PER_SEC << endl;
}


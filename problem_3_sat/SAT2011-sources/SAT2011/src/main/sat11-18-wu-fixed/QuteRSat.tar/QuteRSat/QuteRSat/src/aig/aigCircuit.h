#ifndef _AIG_CIRCUIT_H_
#define _AIG_CIRCUIT_H_
#include <vector>
#include <string>
#include <iostream>
#include <stdint.h>

using namespace std;

// _data = UINT_MAX for undefined AigIndex

struct AigIndex
{
   union
   {
      struct
      {
         bool _sign  : 1;
         uint32_t _index : 31;
      };
      uint32_t _data;
   };
   AigIndex();
   AigIndex( const AigIndex &index );
   explicit AigIndex( unsigned data );
   explicit AigIndex( unsigned index, bool sign );
   
   AigIndex getLink( const vector<AigIndex> &links ) const;
   AigIndex getLink( const vector<unsigned> &links ) const;
   AigIndex operator ~() const;
   bool operator < ( const AigIndex &b ) const;
   bool operator == ( const AigIndex &b ) const;
};

struct AigNode
{
   AigIndex _fanin[2];

   AigNode();
   AigNode( AigIndex fanin0, AigIndex fanin1 );
   bool isPi() const;
   AigIndex &operator [] ( unsigned index ) { return _fanin[index]; }
   const AigIndex &operator [] ( unsigned index ) const { return _fanin[index]; }
   bool operator == ( const AigNode &b ) const;
};

class AigCircuit
{
public:
   AigCircuit();
   void clear();
   void reserve( unsigned num );
   void resize( unsigned num );
   unsigned size() const;
   void swap( AigCircuit &cir );
   
   unsigned getPiNum() const;
   unsigned getPoNum() const;
   unsigned getDffNum() const;
   AigIndex getPi( unsigned index ) const;
   AigIndex getPo( unsigned index ) const;
   AigIndex getDff( unsigned index ) const;
   const vector<AigNode> &getNodes() const;
   const vector<AigIndex> &getPiList() const { return _piList; }
   const vector<AigIndex> &getPoList() const { return _poList; }
   
   void addPi( AigIndex index );
   void addDff( AigIndex index );
   void addPo( AigIndex index );
   AigIndex pushPi();
   AigIndex pushDff( AigIndex fanin );
   AigIndex pushNode( AigIndex fanin0, AigIndex fanin1 );
   void popNode();
   void initialize( const AigCircuit &orgCircuit, vector<AigIndex> &links );
   void finalize( const AigCircuit &orgCircuit, const vector<AigIndex> &links );
   void copyFrom( const AigCircuit &orgCircuit, vector<AigIndex> &links );
   //Super Gate -> Aig
   AigIndex pushOr( AigIndex fanin0, AigIndex fanin1 );
   AigIndex pushXor( AigIndex fanin0, AigIndex fanin1 );
   //I/O name
   void setPiName( unsigned index, const string &name );
   void setPoName( unsigned index, const string &name );
   void setDffName( unsigned index, const string &name );
   const string &getPiName( unsigned index ) const;
   const string &getPoName( unsigned index ) const;
   const string &getDffName( unsigned index ) const;
   unsigned getPiNameNum() const;
   unsigned getPoNameNum() const;
   unsigned getDffNameNum() const;
   void report( ostream &os ) const;
   
   const AigNode &operator [] ( unsigned index ) const;
   AigNode &operator [] ( unsigned index );
protected:
   vector<AigNode>  _nodes;
   vector<AigIndex> _piList, _poList, _dffList;
   vector<string>   _piName, _poName, _dffName;
};

#endif


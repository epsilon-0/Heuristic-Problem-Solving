#ifndef _AIG_HASH_
#define _AIG_HASH_
#include <dense_hash_map>
#include "../aig/aigCircuit.h"

struct AigHashFunc
{
   inline size_t operator() ( const AigNode &a ) const;
};

class AigHash
{
public:
   AigHash();
   void perform( const AigCircuit &orgCircuit, AigCircuit &newCircuit );
   void hashCircuit( const AigCircuit &circuit );
   AigIndex hashNode( AigIndex fanin0, AigIndex fanin1, unsigned index, bool insertHash );
   AigIndex hashNode( const AigNode &node, unsigned index, bool insertHash );
private:
   vector<AigIndex> _links;
   google::dense_hash_map<AigNode, uint32_t, AigHashFunc> _hashTable;
   //Hash<AigNode,unsigned>::MapTable _hashTable;
};

#endif


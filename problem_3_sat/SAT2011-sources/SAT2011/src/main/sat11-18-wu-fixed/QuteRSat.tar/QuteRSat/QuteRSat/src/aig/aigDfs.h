#ifndef _AIG_DFS_
#define _AIG_DFS_
#include <vector>

using namespace std;

class AigCircuit;

class AigDfs
{
public:
   bool check( const AigCircuit &circuit ) const;
   void perform( const AigCircuit &orgCircuit, AigCircuit &newCircuit, bool travseAll = false );
   void perform( const AigCircuit &orgCircuit, AigCircuit &newCircuit, const vector<AigIndex> &pilist, const vector<AigIndex> &polist );
   const vector<AigIndex> &getLinks() const;
protected:
   vector<AigIndex> _links;
   vector<unsigned> _gstack;
   
   void setDfs( unsigned index, const AigCircuit &orgCircuit, AigCircuit &newCircuit );
};

#endif

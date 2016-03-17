#ifndef _TRUTH_CNF_H_
#define _TRUTH_CNF_H_
#include <string>

class TruthToCnf
{
public:
   TruthToCnf() : _truthToCnf( NULL ), _clauseNum( NULL ) {;}
   ~TruthToCnf();
   bool read( const std::string &fname );
   bool readInternal();
   bool write( const std::string &fname );
   inline unsigned char *getClauseToCnf( unsigned truth, unsigned index ) const
      { return _truthToCnf[truth][index]; }
   inline unsigned char getClauseNum( unsigned truth ) const
      { return _clauseNum[truth]; }
   unsigned char getCost( unsigned truth ) const
      { return _cost[truth]; }
   unsigned char getRealClauseNum( unsigned truth, unsigned varNum ) const;
private:
   unsigned char ***_truthToCnf;
   unsigned char *_clauseNum;
   unsigned char *_cost;
};

#endif

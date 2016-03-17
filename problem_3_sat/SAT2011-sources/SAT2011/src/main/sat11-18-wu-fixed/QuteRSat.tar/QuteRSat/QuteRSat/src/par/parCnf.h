#ifndef _PAR_CNF_H_
#define _PAR_CNF_H_
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <zlib.h>
#include "../cnf/cnfToAig.h"

using namespace std;

class CnfParser
{
public:
   CnfParser();
   virtual ~CnfParser();
   bool read( const string &fname );
   unsigned getVarNum() const { return _varNum; }
   unsigned getClauseNum() const { return _clauseNum; }
protected:
   bool       _perror;
   int        _bufPos;
   int        _bufSize;
   unsigned   _varNum;
   unsigned   _clauseNum;
   char       _buffer[32768];
   gzFile     _infile;
   vector<uint32_t> _literals;
  
   void fillBuffer();
   void incPos();
   int  getChar();
   int  getInt();
   void skipSpace();
   void skipLine();
   bool compareString( const char *str );
   void readHeader();
   void readClause();

   virtual void setVarNum() = 0;
   virtual void addClause() = 0;
};

class CnfToAigParser : public CnfParser 
{
public:
   CnfToAigParser( AigCircuit &cir, vector<AigIndex> &links )
      :_cir( cir ), _links( links ), _data(NULL) {;}
   CnfToAig *getData() { return _data; }
private:
   AigCircuit       &_cir;
   vector<AigIndex> &_links;
   CnfToAig         *_data;

   void setVarNum();
   void addClause();
};

#endif


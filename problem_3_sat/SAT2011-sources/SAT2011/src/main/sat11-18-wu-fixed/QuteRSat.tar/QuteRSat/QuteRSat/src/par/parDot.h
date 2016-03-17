#ifndef _PAR_DOT_H_
#define _PAR_DOT_H_
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class AigCircuit;

class DotParser
{
public:
   DotParser();
   virtual ~DotParser();

protected:
   bool write( const string &fname );
   virtual unsigned getSize() const = 0;
   virtual unsigned getFaninNum( unsigned index ) const = 0;
   virtual unsigned getFanin( unsigned index, unsigned faninIndex ) const = 0;
   virtual unsigned getPoNum() const = 0;
   virtual unsigned getPo( unsigned index ) const = 0;
   virtual const string &getGateName( unsigned index ) const = 0;
   virtual const string &getGraphName() const;
   virtual bool isPi( unsigned index ) const = 0;
   mutable string _buffer;
private:
   ofstream *_outfile;
   
   void writeHeader();
   void writeGate( unsigned index );
   void writePo();
   void writeEnd();
};

class AigDotParser : public DotParser
{
public:
   AigDotParser();
   bool write( const string &fname, AigCircuit &cir );
private:
   AigCircuit *_cir;
   
   unsigned getSize() const;
   unsigned getFaninNum( unsigned index ) const;
   unsigned getFanin( unsigned index, unsigned faninIndex ) const;
   unsigned getPoNum() const;
   unsigned getPo( unsigned index ) const;
   const string &getGateName( unsigned index ) const;
   const string &getGraphName() const;
   bool isPi( unsigned index ) const;
};

#endif

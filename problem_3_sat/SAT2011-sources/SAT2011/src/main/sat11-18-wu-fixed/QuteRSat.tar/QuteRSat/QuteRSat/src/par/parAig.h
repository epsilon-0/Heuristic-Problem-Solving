#ifndef _PAR_AIG_H_
#define _PAR_AIG_H_
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class AigCircuit;

//Aiger format
class AigerParser
{
public:
   AigerParser();
   virtual ~AigerParser();
   void setAsciiFormat();
   void setBinaryFormat();
protected:
   bool read( const string &fname );
   bool write( const string &fname );
   virtual void     resize( unsigned sz ) = 0;
   virtual bool     isPi( unsigned gindex ) const = 0;
   virtual bool     isPo( unsigned gindex ) const = 0;
   virtual void     insertGate( unsigned gindex, unsigned f0, unsigned f1 ) = 0;
   virtual void     insertLatch( unsigned gindex, unsigned fanin ) = 0;
   virtual void     insertPi( unsigned gindex ) = 0;
   virtual void     insertPo( unsigned gindex ) = 0;
   virtual unsigned getFanin0( unsigned gindex ) const = 0;
   virtual unsigned getFanin1( unsigned gindex ) const = 0;
   virtual unsigned getGIndex( unsigned index ) const = 0;
   virtual unsigned getLatch( unsigned index ) const = 0;
   virtual unsigned getLatchNum() const = 0;
   virtual const string &getLatchName( unsigned index ) const;
   virtual unsigned getPi( unsigned index ) const = 0;
   virtual unsigned getPiNum() const = 0;
   virtual const string &getPiName( unsigned index ) const;
   virtual unsigned getPo( unsigned index ) const = 0;
   virtual unsigned getPoNum() const = 0;
   virtual const string &getPoName( unsigned index ) const;
   virtual unsigned getSize() const = 0;
   virtual void setLatchName( unsigned index, const string &name );
   virtual void setPiName( unsigned index, const string &name );
   virtual void setPoName( unsigned index, const string &name );
   virtual bool finishRead() const;
   mutable string _buffer;

private:
   enum FILEFORMAT
   {
      FORMAT_ASCII,
      FORMAT_BINARY 
   };
   
   ifstream      *_infile;
   ofstream      *_outfile;
   FILEFORMAT     _format;
   unsigned       _maxvar;
   unsigned       _inputs;
   unsigned       _latches;
   unsigned       _outputs;
   unsigned       _ands;
   
   ifstream &getInFile();
   ofstream &getOutFile();
   bool readHeader();
   bool readInputs();
   bool readLatches();
   bool readOutputs();
   bool readAnds();
   bool readNames();
   bool decodeDelta( unsigned& delta );
   bool encodeDelta( unsigned delta );
   
   bool writeHeader();
   bool writeInputs();
   bool writeLatches();
   bool writeOutputs();
   bool writeAnds();
   bool writeNames();
};

class AigParser : public AigerParser
{
public:
   AigParser();
   bool read( const string &fname, AigCircuit *cir );
   bool write( const string &fname, AigCircuit *cir );   
private:
   AigCircuit *_cir;
   void     resize( unsigned sz );
   bool     isPi( unsigned gindex ) const;
   bool     isPo( unsigned gindex ) const;
   void     insertGate( unsigned gindex, unsigned f0, unsigned f1 );
   void     insertLatch( unsigned gindex, unsigned fanin );
   void     insertPi( unsigned gindex );
   void     insertPo( unsigned gindex );
   unsigned getFanin0( unsigned gindex ) const;
   unsigned getFanin1( unsigned gindex ) const;
   unsigned getGIndex( unsigned index ) const;
   unsigned getLatch( unsigned index ) const;
   unsigned getLatchNum() const;
   const string &getLatchName( unsigned index ) const;
   unsigned getPi( unsigned index ) const;
   unsigned getPiNum() const;
   const string &getPiName( unsigned index ) const;
   unsigned getPo( unsigned index ) const;
   unsigned getPoNum() const;
   const string &getPoName( unsigned index ) const;
   unsigned getSize() const;
   void setLatchName( unsigned index, const string &name );
   void setPiName( unsigned index, const string &name );
   void setPoName( unsigned index, const string &name );
};

#endif

#include <cassert>
#include <algorithm>
#include "../aig/aigCircuit.h"
#include "parAig.h"

AigerParser::AigerParser()
   : _infile( NULL ), _outfile( NULL )
{
   setBinaryFormat();
}

AigerParser::~AigerParser()
{
}

void
AigerParser::setAsciiFormat()
{
   _format = FORMAT_ASCII;
}

void
AigerParser::setBinaryFormat()
{
   _format = FORMAT_BINARY;
}
  
bool
AigerParser::read( const string &fname )
{
   ifstream infile;
   _infile = &infile; 
   getInFile().open( fname.c_str(), ios::binary );
   if( !getInFile().is_open() ) return false;
   if( !readHeader() ) return false;
   if( !readInputs() ) return false;
   if( !readLatches() ) return false;
   if( !readOutputs() ) return false;
   if( !readAnds() ) return false;
   if( !readNames() ) return false;
   if( !finishRead() ) return false;
   return true;
}

ifstream &
AigerParser::getInFile()
{
   assert( _infile != NULL );
   return *_infile;
}

ofstream &
AigerParser::getOutFile()
{
   assert( _outfile != NULL );
   return *_outfile;
}

bool
AigerParser::readHeader()
{
   getInFile() >> _buffer;
   if( _buffer == "aag" )
      _format = FORMAT_ASCII;
   else if( _buffer == "aig" )
      _format = FORMAT_BINARY;
   else
   {
      cerr<< "Error: AigerParser: Undefine Mode: " << _buffer << endl;
      return false;
   }
   getInFile() >> _maxvar >> _inputs >> _latches >> _outputs >> _ands;
   if( _format == FORMAT_BINARY &&
       _maxvar != _inputs + _latches + _ands )
   {
      cerr << "Error: AigerParser: Invalid Maximum Variable index: " << _maxvar << endl;
      return false;
   }
   resize( _maxvar + 1 );
   return true;
}

bool
AigerParser::readInputs()
{
   unsigned i, lit, var;
   if( _format == FORMAT_ASCII )
      for( i = 1; i <= _inputs; i++ )
      {
         getInFile() >> lit;
         var = lit >> 1;
         if( ( lit & 1 ) || var > _maxvar )
         {
            cerr << "Error: AigerParser: Invalid Input Literal: " << lit << endl;
            return false;
         }
         insertPi( lit );
      }
   else
      for( i = 1; i <= _inputs; i++ )
         insertPi( i << 1 );
   return true;
}


bool
AigerParser::readLatches()
{
   unsigned i, lit, var, faninLit;
   if( _format == FORMAT_ASCII )
      for( i = 1; i <= _latches; i++ )
      {
         getInFile() >> lit >> faninLit;
         var = lit >> 1;
         if( ( lit & 1 ) || var > _maxvar )
         {
            cerr << "Error: AigerParser: Invalid Latch Literal: " << lit << endl;
            return false;
         }
         if( ( faninLit >> 1 ) > _maxvar )
         {
            cerr << "Error: AigerParser: Invalid Latch Output Literal: " << faninLit << endl;
            return false;
         }
         insertLatch( lit, faninLit );
      }
   else
      for( i = 1; i <= _latches; i++ )
      {
         lit = (_inputs + i) << 1;
         getInFile() >> faninLit;
         if( ( faninLit >> 1 ) > _maxvar )
         {
            cerr << "Error: AigerParser: Invalid Latch Output Literal: " << faninLit << endl;
            return false;
         }
         insertLatch( lit, faninLit );
      }
   return true;
}

bool
AigerParser::readOutputs()
{
   unsigned i, polit;
   for( i = 1; i <= _outputs; i++ )
   {
      getInFile() >> polit;
      if( ( polit >> 1 ) > _maxvar )
      {
         cerr << "Error: AigerParser: Invalid Output Literal: " << polit << endl;
         return false;
      }
      insertPo( polit );
   }
   return true;
}

bool
AigerParser::readAnds()
{
   char ch;
   unsigned i, gindex, f0, f1, delta;
   if( _format == FORMAT_ASCII )
      for( i = 0; i < _ands; i++ )
      {
         getInFile() >> gindex >> f0 >> f1;
         if( ( gindex & 1 ) || ( gindex >> 1 ) > _maxvar )
         {
            cerr<< "Error: AigerParser: Invalid And Gate Literal: " << gindex <<endl;
            return false;
         }
         if( ( f0 >> 1 ) > _maxvar )
         {
            cerr<< "Error: AigerParser: Invalid Fanin0 Literal: " << f0 <<endl;
            return false;
         }
         if( ( f1 >> 1 ) > _maxvar )
         {
            cerr<< "Error: AigerParser: Invalid Fanin1 Literal: " << f1 <<endl;
            return false;
         }
         insertGate( gindex, f0, f1 );
      }
   else
   {
      while( !getInFile().eof() )
      {
         getInFile().get( ch );
         if( ch == '\n' ) break;
      }
      for( i = 1; i <= _ands; i++ )
      {
         const unsigned gindex = ( i + _inputs + _latches ) << 1;
         if( !decodeDelta( delta ) )
            return false;
         assert( gindex >= delta );
         const unsigned f0 = gindex - delta;
         if( !decodeDelta( delta ) )
            return false;
         assert( f0 >= delta );
         const unsigned f1 = f0 - delta;
         insertGate( gindex, f0, f1 );
      }
   }
   return true;
}

bool
AigerParser::readNames()
{
   int index;
   string str, name;
   while( true )
   {
      getInFile() >> str;
      if( getInFile().eof() ) return true;
      if( str.empty() ) return true;
      if( str[0] == 'c' ) return true;
      getInFile() >> name;
      if( str[0] == 'i' )
      {
         index = atoi( str.substr(1).c_str() );
         if( index < 0 || index > int( getPiNum() ) )
         {
            cerr << "Error: AigerParser: Invalid index for PI: " 
                 << str << " / " << getPiNum() << endl;
            return false;
         }
         setPiName( index, name );
      }
      else if( str[0] == 'l' )
      {
         index = atoi( str.substr(1).c_str() );
         if( index < 0 || index > static_cast<int>( getLatchNum() ) )
         {
            cerr << "Error: AigerParser: Invalid index for Latch: " 
                 << str << " / " << getLatchNum() << endl;
            return false;
         }
         setLatchName( index, name );
      }
      else if( str[0] == 'o' )
      {
         index = atoi( str.substr(1).c_str() );
         if( index < 0 || index > static_cast<int>( getPoNum() ) )
         {
            cerr << "Error: AigerParser: Invalid index for PO: " 
                 << str << " / " << getPoNum() << endl;
            return false;
         }
         setPoName( index, name );
      }
      if( getInFile().eof() ) return true;
   }
}

bool
AigerParser::decodeDelta( unsigned& delta )
{
   char ch = 0x80;
   int i;
   
   getInFile().get( ch );
   for( i = 0, delta = 0; ( ch & 0x80 ) ; i+=7 )
   {
      if( getInFile().eof() || i >= 35 )
      {
         cerr << "Error: AigerParser: Decoding Fail" << endl; 
         return false;
      }
      delta |= ( ch & 0x7f ) << i;
      getInFile().get( ch );
   }
   if( getInFile().eof() || ( ch >= 8 && i == 35 ) )
   {
      cerr<< "Error: AigerParser: Decoding Fail" <<endl; 
      return false;
   }
   delta |= ch << i;
   return true;
}

bool
AigerParser::encodeDelta( unsigned delta )
{
   char ch;
   
   while( delta != 0 )
   {
      ch = delta & 0x7f;
      delta >>= 7;
      if( delta != 0 )
         ch |= 0x80;
      getOutFile().put( ch );
   }
   return true;
}

bool
AigerParser::write( const string &fname  )
{
   ofstream outfile;
   _outfile = &outfile;
   getOutFile().open( fname.c_str() );
   if( !getOutFile().is_open() ) return false;
   if( !writeHeader() ) return false;
   if( !writeInputs() ) return false;
   if( !writeLatches() ) return false;
   if( !writeOutputs() ) return false;
   if( !writeAnds() ) return false;
   if( !writeNames() ) return false;
   return true;
}

bool
AigerParser::writeHeader()
{
   if( _format == FORMAT_ASCII )
      getOutFile() << "aag ";
   else getOutFile() << "aig ";
   getOutFile() << ( getSize() - 1 ) << " "<< getPiNum() << " " 
            << getLatchNum() << " " << getPoNum() << " "
            << getSize() - getPiNum() - getLatchNum() - 1 << endl;
   return true;
}

bool
AigerParser::writeInputs()
{
   unsigned i;
   const unsigned pinum = getPiNum();
   if( _format == FORMAT_BINARY ) return true;
   for( i = 0; i < pinum; i++ )
      getOutFile() << getPi( i ) <<endl;
   return true;
}

bool
AigerParser::writeLatches()
{
   unsigned i;
   const unsigned latchnum = getLatchNum();
   for( i = 0; i < latchnum; i++ )
   {
      const unsigned latch = getLatch( i );
      if( _format == FORMAT_ASCII )
         getOutFile() << latch << " ";
      getOutFile() << getFanin0( latch ) << endl;
   }
   return true;
}

bool
AigerParser::writeOutputs()
{
   unsigned i;
   const unsigned ponum = getPoNum();
   for( i = 0; i < ponum; i++ )
      getOutFile() << getPo(i) <<endl;
   return true;
}

bool
AigerParser::writeAnds()
{
   unsigned i, f0, f1;
   const unsigned gsize = getSize();
   for( i = 1; i < gsize; i++ )
   {
      const unsigned gindex = getGIndex(i);
      if( isPi( gindex ) || isPo( gindex ) ) continue;
      if( _format == FORMAT_ASCII )
      {
         getOutFile() << gindex << " " << getFanin0(gindex) << " " << getFanin1(gindex) << endl;
         continue;
      }
      if( gindex != ( i << 1 ) )
      {
         cerr << "Error: AigerParser: Invalid gindex for aig format: " << gindex << " != "
              << ( i << 1 ) << endl;
         return false;
      }
      f0 = getFanin0( gindex );
      f1 = getFanin1( gindex );
      if( f0 < f1 ) swap( f0, f1 );
      assert( gindex > f0 );
      if( !encodeDelta( gindex - f0 ) )
         return false;
      assert( f0 > f1 );
      if( !encodeDelta( f0 - f1 ) )
         return false;
   }
   return true;
}

bool
AigerParser::writeNames()
{
   unsigned i = 0;
   const unsigned piNum = getPiNum();
   const unsigned poNum = getPoNum();
   const unsigned latchNum = getLatchNum();
   
   for( i = 0; i < piNum; i++ )
      if( !getPiName(i).empty() )
         getOutFile() << "i" << i << " " << getPiName( i ) << endl;
   for( i = 0; i < latchNum; i++ )
      if( !getLatchName(i).empty() )
         getOutFile() << "l" << i << " " << getLatchName( i ) << endl;
   for( i = 0; i < poNum; i++ )
      if( !getPoName(i).empty() )
         getOutFile() << "o" << i << " " << getPoName( i ) << endl;
   //getOutFile() << "c" << endl;
   return true;
}

const string &
AigerParser::getLatchName( unsigned index ) const
{
   _buffer.clear();
   return _buffer;
}

const string &
AigerParser::getPiName( unsigned index ) const
{
   _buffer.clear();
   return _buffer;
}

const string &
AigerParser::getPoName( unsigned index ) const
{
   _buffer.clear();
   return _buffer;
}

void
AigerParser::setLatchName( unsigned index, const string &name )
{
}

void
AigerParser::setPiName( unsigned index, const string &name )
{
}

void
AigerParser::setPoName( unsigned index, const string &name )
{
}

bool
AigerParser::finishRead() const
{
   return true;
}

AigParser::AigParser()
   : _cir( NULL )
{
}

bool
AigParser::read( const string &fname, AigCircuit *cir )
{
   _cir = cir;
   assert( _cir != NULL );
   return AigerParser::read( fname );
}

bool
AigParser::write( const string &fname, AigCircuit *cir )
{
   _cir = cir;
   assert( _cir != NULL );
   return AigerParser::write( fname );
}

void
AigParser::resize( unsigned sz )
{
   _cir->resize( sz );
}

bool
AigParser::isPi( unsigned gindex ) const
{
   return (*_cir)[gindex>>1].isPi();
}

bool
AigParser::isPo( unsigned gindex ) const
{
   return false;
}


void
AigParser::insertGate( unsigned gindex, unsigned f0, unsigned f1 )
{
   //AigGate newGate( gindex, f0, f1 );
   //_cir->insertGateFromGate( gindex , newGate );
   const unsigned index = gindex >> 1;
   (*_cir)[index]._fanin[0]._data = f0;
   (*_cir)[index]._fanin[1]._data = f1;
}

void
AigParser::insertLatch( unsigned gindex, unsigned fanin )
{
   //_cir->insertLatch( gindex , fanin );
   const unsigned index = gindex >> 1;
   _cir->addDff( AigIndex( index, 0 ) );
   (*_cir)[index]._fanin[0]._data = fanin;
   (*_cir)[index]._fanin[1]._data = 0;
}

void
AigParser::insertPi( unsigned gindex )
{
   _cir->addPi( AigIndex( gindex ) );
}

void
AigParser::insertPo( unsigned gindex )
{
   AigIndex po;
   po._data = gindex;
   _cir->addPo( po );
}

unsigned
AigParser::getFanin0( unsigned gindex ) const
{
   return (*_cir)[gindex>>1]._fanin[0]._data;
}

unsigned
AigParser::getFanin1( unsigned gindex ) const
{
   return (*_cir)[gindex>>1]._fanin[1]._data;
}

unsigned
AigParser::getGIndex( unsigned index ) const
{
   return index << 1;
}

unsigned
AigParser::getLatch( unsigned index ) const
{
   return _cir->getDff( index )._data;
}

unsigned
AigParser::getLatchNum() const
{
   return _cir->getDffNum();
}

const string &
AigParser::getLatchName( unsigned index ) const
{
   if( index < _cir->getDffNameNum() )
      return _cir->getDffName( index );
   _buffer.clear();
   return _buffer;
}

void
AigParser::setLatchName( unsigned index, const string &name )
{
   _cir->setDffName( index, name );
}

unsigned
AigParser::getPi( unsigned index ) const
{
   return _cir->getPi( index )._data;
}

unsigned
AigParser::getPiNum() const
{
   return _cir->getPiNum();
}

const string &
AigParser::getPiName( unsigned index ) const
{
   if( index < _cir->getPiNameNum() )
      return _cir->getPiName( index );
   _buffer.clear();
   return _buffer;
}

void
AigParser::setPiName( unsigned index, const string &name )
{
   _cir->setPiName( index, name );
}

unsigned
AigParser::getPo( unsigned index ) const
{
   return _cir->getPo( index )._data;
}

unsigned
AigParser::getPoNum() const
{
   return _cir->getPoNum();
}

const string &
AigParser::getPoName( unsigned index ) const
{
   if( index < _cir->getPoNameNum() )
      return _cir->getPoName( index );
   _buffer.clear();
   return _buffer;
}

void
AigParser::setPoName( unsigned index, const string &name )
{
   _cir->setPoName( index, name );
}

unsigned
AigParser::getSize() const
{
   return _cir->size();
}


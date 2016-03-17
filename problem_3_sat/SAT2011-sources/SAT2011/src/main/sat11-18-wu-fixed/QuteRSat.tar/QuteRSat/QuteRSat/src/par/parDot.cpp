#include <sstream>
#include "../aig/aigCircuit.h"
#include "parDot.h"

DotParser::DotParser()
   : _outfile( NULL )
{
}

DotParser::~DotParser()
{
}

bool
DotParser::write( const string &fname )
{
   ofstream outfile( fname.c_str() );
   
   if( !outfile.is_open() ) return false;
   _outfile = &outfile;
   writeHeader();
   for( unsigned i = 0, csize = getSize();
        i < csize; ++i )
      writeGate( i );
   writePo();
   writeEnd();
   return true;
}

void
DotParser::writeHeader()
{
   (*_outfile) << "digraph " << getGraphName() << " {" << endl;
}

void
DotParser::writeGate( unsigned index )
{
   const string gateName = getGateName( index );
   if( isPi( index ) )
   {
      (*_outfile) << "\"" << gateName << "\" ;" << endl;
      return;
   }  
   for( unsigned i = 0, fnum = getFaninNum( index );
        i < fnum; ++i )
   {
      const unsigned fanin = getFanin( index, i ); 
      (*_outfile) << "\"" << getGateName( fanin >> 1 ) << "\" -> \"" << gateName << "\" ";
      if( fanin & 1 ) (*_outfile) << "[arrowhead=dot]";
      (*_outfile) << ";" << endl; 
   }
}

void
DotParser::writePo()
{
   const unsigned poNum = getPoNum();
   for( unsigned i = 0; i < poNum; ++i )
   {
      const unsigned fanin = getPo( i );
      ostringstream ss;
      ss << "PO_" << i;
      (*_outfile) << "\"" << getGateName( fanin >> 1 ) << "\" -> \"" << ss.str() << "\" ";
      if( fanin & 1 ) (*_outfile) << "[arrowhead=dot]";
      (*_outfile) << ";" << endl; 
   }
}

void
DotParser::writeEnd()
{
   (*_outfile) << "}" << endl;
}

const string &
DotParser::getGraphName() const
{
   _buffer = "dotGraph";
   return _buffer;
}


AigDotParser::AigDotParser()
   : _cir( NULL )
{
}

bool
AigDotParser::write( const string &fname, AigCircuit &cir )
{
    _cir = &cir;
    return DotParser::write( fname );
}

unsigned
AigDotParser::getSize() const
{
   return _cir->size();
}

unsigned
AigDotParser::getFaninNum( unsigned index ) const
{
   return 2;
}

unsigned
AigDotParser::getFanin( unsigned index, unsigned faninIndex ) const
{
   return (*_cir)[index]._fanin[faninIndex]._data;
}

unsigned
AigDotParser::getPoNum() const
{
   return _cir->getPoNum();
}

unsigned
AigDotParser::getPo( unsigned index ) const
{
   return _cir->getPo( index )._data;
}

const string &
AigDotParser::getGateName( unsigned index ) const
{
   stringstream ss;
   ss << "n" << index;
   _buffer = ss.str();
   return _buffer;    
}

const string &
AigDotParser::getGraphName() const
{
   _buffer = "AigGraph";
   return _buffer;
}

bool
AigDotParser::isPi( unsigned index ) const
{
   return (*_cir)[index].isPi();
}

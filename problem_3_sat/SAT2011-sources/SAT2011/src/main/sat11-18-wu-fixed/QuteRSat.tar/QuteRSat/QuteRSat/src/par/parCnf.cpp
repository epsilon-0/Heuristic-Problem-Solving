#include <cassert>
#include "parCnf.h"

CnfParser::CnfParser()
{
}

CnfParser::~CnfParser()
{
}

void
CnfParser::fillBuffer()
{
   _bufPos = 0;
   _bufSize = gzread( _infile, _buffer, sizeof( _buffer ) );
}

void
CnfParser::incPos()
{
   if( ++_bufPos >= _bufSize ) fillBuffer();
}

int
CnfParser::getChar()
{
   if( _bufPos >= _bufSize ) return EOF;
   return _buffer[ _bufPos ];
}

int
CnfParser::getInt()
{
   int value = 0, ch;
   bool neg = false;

   skipSpace();
   ch = getChar();
   if( ch == '-' )
   {
      neg = true;
      incPos();
   }
   else if( ch == '+' )
      incPos();
   ch = getChar();
   if( ch < '0' || ch > '9' )
   {
      cout << "c Error: CnfParser : parse integer error!" << endl;
      _perror = true;
      return 0;
   }
   while( ch >= '0' && ch <= '9' )
   {
      value *= 10;
      value += ch - '0';
      incPos();
      ch = getChar();
   }
   return (neg) ? -value : value;
}

void
CnfParser::skipSpace()
{
   int ch;
   for( ch = getChar(); 
         ( ch >= 9 && ch <= 13 ) || ch == 32;
         ch = getChar() )
      incPos();
}

void
CnfParser::skipLine()
{
   int ch;
   for( ch = getChar(); 
         ch != '\n' && ch != EOF; 
         ch = getChar() )
      incPos();
   if( ch == '\n' ) incPos();
}

bool
CnfParser::compareString( const char *str )
{
   for( ; *str != 0; ++str, incPos() )
      if( getChar() != *str )
         return false;
   return true;
}

bool
CnfParser::read( const string &fname )
{
   _infile = gzopen( fname.c_str(), "rb" );
   _perror = false;
   if( _infile == NULL )
   {
      _perror = true;
      cout << "c Error: CnfParser : can't open " << fname << endl; 
      return false;
   }
   _bufPos = _bufSize = 0;
   fillBuffer();
   readHeader();
   if( _perror ) return false;
   readClause();
   if( _perror ) return false;
   return true;
}

void
CnfParser::readHeader()
{
   int ch;

   while( true )
   {
      skipSpace();
      ch = getChar();
      if( ch == EOF )
      {
         _perror = true;
         cout << "c Error: CnfParser: readHeader: No header (p cnf) " << endl;
         return;
      }
      if( ch == 'c' )
      {
         skipLine();
         continue;
      }
      if( ch == 'p' )
      {
         incPos();
         skipSpace();
         if( !compareString( "cnf" ) )
         {
            _perror = true;
            cout << "c Error: CnfParser: readHeader: Wrong format (p) " << endl;
            return;
         }
         _varNum = getInt();
         ++_varNum;
         if( _perror )
         {
            cout << "c Error: CnfParser: readHeader: Wrong var num " << endl;
            return;
         }
         _clauseNum = getInt();
         if( _perror )
         {
            cout << "c Error: CnfParser: readHeader: Wrong clause num " << _clauseNum << endl;
            return;
         }
         return;
      }
      _perror = true;
      cout << "c Error: CnfParser: readHeader: Wrong format " << ch << endl;
      return;
   }
}

void
CnfParser::readClause()
{
   unsigned i;
   int lit;
   
   setVarNum();
   for( i = 0; i < _clauseNum && getChar() != EOF; ++i )
   {
      _literals.clear();
      skipSpace();
      if( getChar() == 'c' )
      {
         skipLine();
         continue;
      }
      while( true )
      {
         lit = getInt();
         if( _perror )
         {
            cout << "c Error: CnfParser: readClause: expect number" << endl;
            return;
         }
         if( lit == 0 ) break;
         if( lit >= 0 ) lit *= 2;
         else
         { 
            lit *= -2;
            ++lit;
         }
         if( ( lit >> 1 ) >= static_cast<int>( _varNum ) )
         {
            _perror = true;
            cout << "c Error: CnfParser: readClause: Wrong variable " << (lit>>1) << "/" << _varNum << endl;
            return;
         }
         _literals.push_back( lit );
      }
      addClause();
   }
   if( i != _clauseNum )
   {
      _perror = true;
      cout << "c Error: CnfParser: readClause: Wrong clause num " << i << "/" << _clauseNum << endl;
   }
}


void CnfToAigParser::setVarNum()
{
   _data = new CnfToAig( _varNum, _cir, _links );
}

void CnfToAigParser::addClause()
{
   _data->addClause( _literals );
}


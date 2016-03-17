#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <readline/readline.h>
#include <readline/history.h>
#include "cmdReadline.h"

ReadLineManager *ReadLineManager::_runPtr = NULL;

ReadLineManager::ReadLineManager()
   : _linePtr( NULL )
{
}

ReadLineManager::~ReadLineManager()
{
}

void
ReadLineManager::addCommand( const string &command, ReadLineArg *args )
{
   _commands.push_back( command );
   _args.push_back( args );
}

string
ReadLineManager::getCommand() const
{
   if( _linePtr == NULL ) return string("");
   return string(_linePtr);
}

int
ReadLineManager::getArgIndex() const
{
   return _argIndex;
}

void
ReadLineManager::executeLine()
{
   if( strcmp("quit", _linePtr ) == 0 )
      setStop();
   else cout << "You type : " << _linePtr << endl;
}

void
ReadLineManager::run( const string &prompt )
{
   rl_readline_name = "ReadLineManager";
   rl_attempted_completion_function = completeText;
   _runPtr = this;
   _stop = false;
   while( !_stop )
   {
      _linePtr = readline( prompt.c_str() );
      if( _linePtr != NULL )
      {
         add_history( _linePtr );
         executeLine();
         free( _linePtr );
         _linePtr = NULL;
      }
   }
}

void
ReadLineManager::setStop()
{
   _stop = true;
}

char **
ReadLineManager::completeText( const char *text, int start, int end )
{
   assert( _runPtr != NULL );
   char ** matches = NULL;
   if( start == 0 )
      matches = rl_completion_matches( text, matchCommand );
   else if( *text == '-' )
   {
      const int cmdSize = _runPtr->_commands.size();
      int &index = _runPtr->_cmdIndex;
      unsigned &length = _runPtr->_textLength;
      for( length = 0; length < static_cast<unsigned>(start) && 
                       rl_line_buffer[length] != ' '; ++length );
      for( index = 0; index < cmdSize; ++index )
         if( strncmp( rl_line_buffer, _runPtr->_commands[index].c_str(), length ) == 0 )
         {
            matches = rl_completion_matches( text, matchArg );
            break;
         }
   }
   return matches;
}

char *
ReadLineManager::matchCommand( const char *text, int state )
{
   assert( _runPtr != NULL );
   const int cmdSize = _runPtr->_commands.size();
   int &index = _runPtr->_cmdIndex;
   unsigned &length = _runPtr->_textLength;
   if( state == 0 )
   {
      index = 0;
      length = strlen( text );
   }
   while( index < cmdSize )
      if( strncmp( text, _runPtr->_commands[index].c_str(), length ) == 0 )
      {
         char *command = 
            reinterpret_cast<char*>( malloc( _runPtr->_commands[index].size() + 1 ) );
         strcpy( command, _runPtr->_commands[index].c_str() );
         ++index;
         return command;
      }
      else ++index;
   return NULL;
}

char *
ReadLineManager::matchArg( const char *text, int state )
{
   assert( _runPtr != NULL );
   assert( _runPtr->_cmdIndex < static_cast<int>( _runPtr->_args.size() ) );
   const ReadLineArg *args = _runPtr->_args[_runPtr->_cmdIndex];
   unsigned &length = _runPtr->_textLength;
   int &index = _runPtr->_argIndex;
   if( args == NULL ) return NULL;
   if( state == 0 )
   {
      index = 0;
      length = strlen( text );
   }
   while( args[index]._name != NULL )
      if( strncmp( text, args[index]._name, length ) == 0 )
      {
         char *command = 
            reinterpret_cast<char*>( malloc( strlen(args[index]._name) + 1 ) );
         strcpy( command, args[index]._name );
         ++index;
         return command;
      }
      else ++index;
   return NULL;
}

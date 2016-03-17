#include <cassert>
#include <cstdlib>
#include <iomanip>
#include "../util/utilResourceUsage.h"
#include "cmdManager.h"

CmdManager *CmdManager::_instance = NULL;

CmdManager &
CmdManager::s_Instance()
{
   if( _instance == NULL ) _instance = new CmdManager;
   return *_instance;
}

void
CmdManager::deleteInstance()
{
   if( _instance != NULL ) delete _instance;
   _instance = NULL;
}

CmdManager::CmdManager()
   : _executeNum(0), _usage( NULL )
{
}

bool
CmdManager::addCommand( const string& command, CmdFunPtr fun, ReadLineArg *args, string helpmsg )
{
   ReadLineManager::addCommand( command, args );
   _functions.push_back( fun );
   _helpmsgs.push_back( helpmsg );
   return true;
}

void
CmdManager::executeLine()
{
   executeString( getCommand() );
}

int
CmdManager::executeString( const string &cmd )
{
   const int csize = _commands.size();
   
   _commandWords.clear();
   splitString( cmd, _commandWords );
   if( _commandWords.empty() ) return 0;
   for( _cmdIndex = 0; _cmdIndex < csize; ++_cmdIndex )
      if( _commandWords[0] == _commands[_cmdIndex] ) break;
   if( _cmdIndex >= csize )
   {
      cerr << "Error: CmdManager: No such command: " << _commandWords[0] << endl;
      return -1;
   }
   searchArg();
   if( _executeNum == 0 && _usage != NULL && _commandWords[0] != "usage" ) _usage->start();
   ++_executeNum;
   const int res = (*_functions[_cmdIndex])(this);
   --_executeNum;
   if( _executeNum == 0 && _usage != NULL && _commandWords[0] != "usage" ) _usage->stop();
   return res;
}

void
CmdManager::setUsage( ResourceUsage &usage )
{
   _usage = &usage;
}

ResourceUsage *
CmdManager::getUsage() const
{
   return _usage;
}

void
CmdManager::splitString( const string& str, vector<string>& strs ) const
{
   size_t foundpos, startpos = 0;
   
   do
   {
      foundpos = str.find(' ',startpos);
      if( foundpos == string::npos )
         foundpos = str.size();
      if( foundpos != startpos )
      {
         assert( str[startpos] != ' ' );
         strs.push_back( str.substr( startpos, foundpos - startpos) );
      }
      startpos = foundpos + 1;
   } while( startpos < str.size() );
}

void 
CmdManager::searchArg()
{
   const int cwSize = _commandWords.size();
   
   _preWordIndex = 1;
   for( _wordIndex = 1, _argNum = 0; _wordIndex < cwSize; ++_wordIndex, ++_argNum )
   {
      const string &cmdWord = _commandWords[_wordIndex];
      assert( !cmdWord.empty() );
      if( cmdWord[0] == '-') break;
   }
}

int 
CmdManager::getArgNum() const
{
   return _argNum;
}

bool
CmdManager::findNextArg()
{
   const int cwsize = _commandWords.size();
   const ReadLineArg *args = _args[_cmdIndex];
   for( ; _wordIndex < cwsize; ++_wordIndex )
   {
      const string &cmdWord = _commandWords[_wordIndex];
      assert( !cmdWord.empty() );
      if( cmdWord[0] != '-' ) continue;
      if( cmdWord == "-h" || cmdWord == "-help" || cmdWord == "--help" )
      {
         DisplayCmdHelp( _cmdIndex );
         _argIndex = -1;
         return true;
      }
      if( args != NULL )
         for( _argIndex = 0; args[_argIndex]._name != NULL; ++_argIndex )
            if( cmdWord == args[_argIndex]._name )
            {
               ++_wordIndex;
               _preWordIndex = _wordIndex;
               _wordIndex += args[_argIndex]._dataNum;
               return true;
            }
      cerr << "Error: CmdManager: No such command argument: "<< cmdWord << endl;
      _argIndex = -2;
      return true;
   }
   return false;
}
 
string
CmdManager::getArgStr( int index ) const
{
   if( index + _preWordIndex >= static_cast<int>( _commandWords.size() ) ) return "";
   return _commandWords[index + _preWordIndex];
}

int
CmdManager::getArgInt( int index ) const
{
   string str = getArgStr( index );
   if( str.empty() ) return 0;
   else return atoi( str.c_str() );
}

void 
CmdManager::DisplayHelp( bool displayArg ) const
{
   unsigned i;
      
   for( i = 0; i != _commands.size(); ++i )
      DisplayCmdHelp( i, true, displayArg );
}

void 
CmdManager::DisplayCmdHelp( unsigned index, bool displayCmd, bool displayArg ) const
{   
   if( index >= _commands.size() )
   {
      cerr << "Error: CmdManager: Wrong index for displaying help" << endl;
      return;
   }
   if( displayCmd )
      cout << setiosflags(ios_base::left) << setw(20) << _commands[index]
           << _helpmsgs[index] << endl;
   const ReadLineArg *args = _args[index];
   if( !displayArg || args == NULL ) return;
   for( unsigned i = 0; args[i]._name != NULL; ++i )
      cout << " " << setiosflags(ios_base::left) << setw(19) << args[i]._name
           << args[i]._helpmsg << endl;
}

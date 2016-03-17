#ifndef _CMD_MANAGER_H_
#define _CMD_MANAGER_H_
#include "../cmd/cmdReadline.h"

class CmdManager;
class ResourceUsage;

typedef int (*CmdFunPtr)(CmdManager*);

class CmdManager : public ReadLineManager
{
public:
   static CmdManager &s_Instance();
   static void deleteInstance();
   bool addCommand( const string& command, CmdFunPtr fun, ReadLineArg *args = NULL, string helpmsg = "" );
   bool findNextArg(); 
   string getArgStr( int index ) const;
   int  getArgInt( int index ) const;
   void DisplayHelp( bool displayArg = false ) const;
   void DisplayCmdHelp( unsigned index, bool displayCmd = true, bool displayArg = true ) const;
   int getArgNum() const;
   int executeString( const string &cmd );
   void setUsage( ResourceUsage &usage );
   ResourceUsage *getUsage() const;
   
private:
   CmdManager();
   int _executeNum;
   int _argNum;
   int _preWordIndex;
   int _wordIndex;
   vector<string>    _commandWords;
   vector<CmdFunPtr> _functions;
   vector<string>    _helpmsgs;
   ResourceUsage    *_usage;
   
   static CmdManager *_instance;
   
   void executeLine();
   void searchArg();
   void splitString( const string &str, vector<string> &strs ) const;
};

#endif

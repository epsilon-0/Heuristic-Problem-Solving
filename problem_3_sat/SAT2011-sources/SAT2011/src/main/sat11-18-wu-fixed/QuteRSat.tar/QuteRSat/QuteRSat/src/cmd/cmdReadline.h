#ifndef _CMD_READLINE_H_
#define _CMD_READLINE_H_
#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct ReadLineArg
{
   const char *_name;
   int   _dataNum;
   const char *_helpmsg;
};

class ReadLineManager
{
public:
   ReadLineManager();
   virtual ~ReadLineManager();
   void addCommand( const string &command, ReadLineArg *args );
   string getCommand() const;
   int getArgIndex() const;
   void run( const string &prompt );
   void setStop();
protected:
   bool _stop;
   char *_linePtr;
   int _argIndex;
   int _cmdIndex;
   unsigned _textLength;
   vector<string>      _commands;
   vector<ReadLineArg*> _args;
   static ReadLineManager *_runPtr;
   
   virtual void executeLine();
   static char ** completeText( const char *text, int start, int end );
   static char * matchCommand( const char *text, int state );
   static char * matchArg( const char *text, int state );
};

#endif

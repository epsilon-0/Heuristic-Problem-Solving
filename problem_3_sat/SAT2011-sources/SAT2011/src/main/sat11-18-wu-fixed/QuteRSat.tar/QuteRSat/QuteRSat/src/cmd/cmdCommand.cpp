#include "../util/utilResourceUsage.h"
#include "cmdManager.h"

ReadLineArg cmd_help_arg[] = {
   { "-all", 0, "For all information" },
   { NULL, 0, NULL }
};

int Command_Help( CmdManager* cmd )
{
   bool all = false;
   while( cmd->findNextArg() )
      switch( cmd->getArgIndex() )
      {
      case 0:
         all = true;
         break;
      default:
         return 0;
      }
   cmd->DisplayHelp( all );
   return 0;
}

ReadLineArg cmd_quit_arg[] = {
   { "-print", 1, "For Test: print next word" },
   { "-bye", 0, "For Test" },
   { NULL, 0, NULL }
};

int Command_Quit( CmdManager* cmd )
{
   int i;
   
   if( cmd->getArgNum() > 0 ) cout << "Arguements:";
   for( i = 0; i < cmd->getArgNum(); i++ )
      cout << " " << cmd->getArgStr(i);
   if( cmd->getArgNum() > 0 ) cout << endl;

   while( cmd->findNextArg() )
      switch( cmd->getArgIndex() )
      {
      case 0:
         cout << "Print: " << cmd->getArgStr(0) << endl;
         break;
      case 1:
         cout << "Byebye, zzz..." << endl;
         break;
      default:
         return 0;
      }
   cmd->setStop();
   return 0;
}

ReadLineArg cmd_usage_arg[] = {
   { "-clear", 0, "clear usage" },
   { "-current", 0, "current usage" },
   { NULL, 0, NULL }
};

int Command_Usage( CmdManager* cmd )
{
   ResourceUsage *usage = cmd->getUsage();
   if( usage == NULL )
   {
      cerr << "Error: CmdManager: no assigned usage" << endl;
      return 0;
   }
   while( cmd->findNextArg() )
      switch( cmd->getArgIndex() )
      {
      case 0:
         usage->clear();
         return 0;
      case 1:
         usage->report( cout, true, false );
         return 0;
      default:
         return 0;
      }
   usage->report( cout, false, true );
   return 0;
}

void addCmdCommands( CmdManager& cmd )
{
   cmd.addCommand( "help", Command_Help, cmd_help_arg, "Help Information" );
   cmd.addCommand( "quit", Command_Quit, cmd_quit_arg, "Quit Program" );
   cmd.addCommand( "usage", Command_Usage, cmd_usage_arg, "Report usage" );
}


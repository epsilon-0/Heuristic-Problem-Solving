#include <cstdlib>
#include <ctime>
#include <fstream>
#include <signal.h>
#if defined(__linux__)
#include <fpu_control.h>
#endif
#include "../cmd/cmdManager.h"

/*
extern void addCmdCommands( CmdManager& cmd );
extern void addAigCommands( CmdManager& cmd );
extern void addParCommands( CmdManager& cmd );
extern void addTruthCommands( CmdManager& cmd );*/
extern void addTmCommands( CmdManager& cmd );

void SignalHandler( int signalNum )
{
    cout << "c Time Out !!" << endl
         << "s UNKNOWN" << endl;
    exit(1);
}

int
main( int argc, char **argv )
{
   clock_t tbegin = clock();
   CmdManager &cmd = CmdManager::s_Instance();
   
#if defined(__linux__)
    fpu_control_t oldcw, newcw;
    _FPU_GETCW(oldcw);
    newcw = (oldcw & ~_FPU_EXTENDED) | _FPU_DOUBLE;
    _FPU_SETCW(newcw);
    cout << "c Set FPU double precision." << endl;
#endif
   signal( SIGINT, SignalHandler );
   signal( SIGTERM, SignalHandler );

  //signal( SIGKILL, SignalHandler );
/* addAigCommands( cmd );
   addCmdCommands( cmd );
   addParCommands( cmd );
   addTruthCommands( cmd );*/
   addTmCommands( cmd );
   if( argc == 2 ) 
      cmd.executeString( string("tmSat ") + argv[1] );
   else if( argc == 3 )
      cmd.executeString( string("tmSat ") + argv[1] + " " + argv[2] );
   else 
   {
      cout << "c Error Input!! Usage: ./cirVerify <input_file> [random_seed]" << endl
           << "s UNKNOWN" << endl;
   }
   cout << "c CPU time: " << static_cast<double>( clock() - tbegin ) / CLOCKS_PER_SEC << " s" << endl;
   //CmdManager::deleteInstance();
   return 0;
}


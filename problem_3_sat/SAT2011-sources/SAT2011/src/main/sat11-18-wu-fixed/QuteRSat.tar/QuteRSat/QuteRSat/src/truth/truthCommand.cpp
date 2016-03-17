#include "../cmd/cmdManager.h"
#include "truthTable.h"
#include "truthNPNClass.h"

int
Command_TestTruthTable( CmdManager* cmd )
{
   while( cmd->findNextArg() )
      switch( cmd->getArgIndex() )
      {
      default:
         return 0;
      }
   TruthTable32 t1(2,1<<2);    //c~a
   
   t1.stretch( 3, 2 ); //c~a --> c~b~a + cb~a
   if( t1 != TruthTable32(3,(1<<4) + (1<<6)) )
   {
      cerr << "Error : TruthTable32 : stretch error: " << t1 << endl;
      return 0;
   }
   t1.shrink( 2, 2 );  //c~b~a + cb~a --> c~a
   if( t1 != TruthTable32(2,1<<2) )
   {
      cerr << "Error : TruthTable32 : shrink error: " << t1 << endl;
      return 0;
   }
   TruthTable32 a(2), b(2), t2;
   
   a.setElementary(0);
   b.setElementary(1);
   t1 = ~( a & b );
   t2 = ~a | ~b;
   if( t1 != t2 )
   {
      cerr << "Error : TruthTable32 : operation error: " << t1 << " != " << t2 << endl;
   } 
   return 0;
}

int
Command_GenerateTruthPermute( CmdManager* cmd )
{
   while( cmd->findNextArg() )
      switch( cmd->getArgIndex() )
      {
      default:
         return 0;
      }
   TruthTable32::generatePermute();
   return 0;
}

int
Command_GenerateTruthStretch( CmdManager* cmd )
{
   unsigned varNum = 3;
   
   if( cmd->getArgNum() > 0 )
      varNum = cmd->getArgInt(0);
   while( cmd->findNextArg() )
      switch( cmd->getArgIndex() )
      {
      default:
         return 0;
      }
   TruthTable32::generateStretch( varNum );
   return 0;
}

int
Command_GenerateNPNClass( CmdManager* cmd )
{
   unsigned varNum = 0;
   
   if( cmd->getArgNum() > 0 )
      varNum = cmd->getArgInt(0);
   while( cmd->findNextArg() )
      switch( cmd->getArgIndex() )
      {
      default:
         return 0;
      }
   if( varNum == 0 || varNum >= 5 )
   {
      cerr << "Error: Command_GenerateNPNClass: no support variable number: " << varNum << endl;
      return 0;
   }
   cout << "Class Num: " << NPNClass::s_Instance( varNum ).getMaxId() << endl;
   NPNClass::deleteInstance();
   return 0;
   
}

void addTruthCommands( CmdManager& cmd )
{
   cmd.addCommand( "testTruthTable", Command_TestTruthTable, NULL, "test TruthTable" );
   cmd.addCommand( "genTruthPermute", Command_GenerateTruthPermute, NULL, "Generate Permute Data of TruthTable" );
   cmd.addCommand( "genTruthStretch", Command_GenerateTruthStretch, NULL, "Generate Stretch Data of TruthTable" );
   cmd.addCommand( "generateNPNClass", Command_GenerateNPNClass, NULL, "[varnum], Generate NPNClass of [varnum]" );
}

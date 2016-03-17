#include <ctime>
#include "../cmd/cmdManager.h"
#include "../par/parCnf.h"
#include "tmSat.h"
#include "tmMap.h"
//#define TMSAT_VERIFY

int
Command_TmSat( CmdManager* cmd )
{
   const unsigned argNum = cmd->getArgNum();
   string fname;
   unsigned seed = 0;
   
   if( argNum > 0 )
      fname = cmd->getArgStr(0);
   if( argNum > 1 )
      seed = cmd->getArgInt(1);
   while( cmd->findNextArg() )
      switch( cmd->getArgIndex() )
      {
      default:
         return 0;
      }
   if( argNum == 0 ) return 0;
   clock_t tbegin = clock();
   AigCircuit cnfCir;
   vector<AigIndex> links;
   CnfToAig *cnfAig;
   
   {
      CnfToAigParser cnfPar( cnfCir, links );
      if( !cnfPar.read( fname ) )
      {
         //if( cnfPar.getData() != NULL )
         //   delete cnfPar.getData();
         cout << "s UNKNOWN" << endl;
         return 0;
      }
      cout << "c Parse Cnf success: #var: " << cnfPar.getVarNum() - 1 << " #clause: " << cnfPar.getClauseNum() << endl;
      cnfAig = cnfPar.getData();
      assert( cnfAig != NULL );
      cnfAig->run();
      cout << "c CnfToAig: Time: " << static_cast<double>( clock() - tbegin ) / CLOCKS_PER_SEC << " s" << endl;
      if( cnfAig->isUnSat() )
      {
         cout << "s UNSATISFIABLE" << endl;
         return 0;
      }
   }
   const double coverRate = cnfAig->getCoverRate();
#ifndef TMSAT_VERIFY
   delete cnfAig;
#endif
   vector<unsigned> piSolution;
   {
      TruthToCnf toCnf;
      TmCircuit tmCir;
      
      toCnf.readInternal();
      {
         TmMap tmap( cnfCir, toCnf );
         tmap._collectBigAnd = true;
         //if( coverRate > 50 ) tmap._collectBigAnd = false;
         //else tmap._collectBigAnd = true;
         tmap.mapTo( tmCir );
      }
      {
         TmSat solver( tmCir, toCnf );
         int res;
         solver._seed = seed;
         if( coverRate > 50 && tmCir.size() < 2000000 ) res = solver.solve();
         else res = solver.solveDirect();
         if( res == 0 ) cout << "s UNSATISFIABLE" << endl;
         else if( res == 1 ) cout << "s SATISFIABLE" << endl;
         else cout << "s UNKNOWN" << endl;
         if( res != 1 ) return 0;
         piSolution = solver.getPiSolution();
      }
   }
   
   assert( piSolution.size() == cnfCir.getPiNum() );
   vector<unsigned> simData( cnfCir.size(), 0 );
   for( unsigned i = 0; i < cnfCir.getPiNum(); ++i )
      simData[ cnfCir.getPi(i)._index ] = piSolution[i];
   for( unsigned i = 1; i < cnfCir.size(); ++i )
   {
       const AigNode &node = cnfCir[i];
       if( node.isPi() ) continue;
       simData[i] = ( node._fanin[0]._sign ? ~simData[node._fanin[0]._index] : simData[node._fanin[0]._index] ) &
                    ( node._fanin[1]._sign ? ~simData[node._fanin[1]._index] : simData[node._fanin[1]._index] );
   }
   vector<unsigned> varValue( links.size(), 0 );
   for( unsigned i = 1; i < links.size(); ++i )
   {
      const AigIndex &varLink = links[i];
      if( varLink._data == UINT_MAX || varLink._data == 1 ) varValue[i] = 1; 
      else if( varLink._data == 0 ) varValue[i] = 0;
      else
      {
         assert( varLink._index < cnfCir.size() );
         varValue[i] = ( simData[varLink._index] & 1 ) ^ varLink._sign;
      }
   }
   cout << "v ";
   for( unsigned i = 1; i < varValue.size(); ++i )
   {
      if( varValue[i] == 0 ) cout << '-';
      cout << i << ' ';
   }
   cout << '0' << endl;
#ifdef TMSAT_VERIFY
   for( unsigned i = 0; i < cnfCir.getPoNum(); ++i )
      assert( ( simData[cnfCir.getPo(i)._index] & 1 ) == unsigned( cnfCir.getPo(i)._sign ^ 1 ) );
   cnfAig->verify( varValue );
#endif
   return 0;
}

void
addTmCommands( CmdManager& cmd )
{
   cmd.addCommand( "tmSat", Command_TmSat, NULL, "tmSat" );
}

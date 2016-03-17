#ifndef _TRUTH_TABLE_H_
#define _TRUTH_TABLE_H_
#include <iostream>
#include <vector>

using namespace std;

inline unsigned countBitOnes( unsigned word )
{
    word = (word & 0x55555555) + ((word>>1) & 0x55555555);
    word = (word & 0x33333333) + ((word>>2) & 0x33333333);
    word = (word & 0x0F0F0F0F) + ((word>>4) & 0x0F0F0F0F);
    word = (word & 0x00FF00FF) + ((word>>8) & 0x00FF00FF);
    return (word & 0x0000FFFF) + (word>>16);
}

class TruthTable32
{
public:
   TruthTable32( unsigned varNum = 0 , unsigned table = 0 );
   virtual ~TruthTable32();
   void clear();
   void changeVarPhase( unsigned v );          //invert input
   void cofactor0( unsigned v );
   void cofactor1( unsigned v );
   unsigned getTable() const;
   unsigned getVarNum() const;
   void pushVar();
   void setElementary( unsigned v );
   void setVarNum( unsigned num );
   void setTable( unsigned table );
   bool isContradiction() const;
   bool isTautology() const;
   void shrink( unsigned varNum, unsigned vpos ); // vpos 00011 means to remove 2 var into 1th, 2th
   void stretch( unsigned varNum, unsigned vpos );  // vpos 00011 means to insert 2 var into 1th, 2th
   void swapAdjacentVar( unsigned v );
   
   void changePhase( unsigned phase ); // input inv + output inv, final bit is for output
   void permute( unsigned permutation, bool reverse = false );  //permute by permutation table
   void changePhasePermute( unsigned phase, unsigned permutation, bool reverse = false );
   static void changePhasePermute( vector<unsigned> &inputs, unsigned phase,
                                   unsigned permutation, bool reverse = false );
   
   void changePhase4( unsigned phase );   //invert inputs of 4 varNum and output invert
   void permute4( unsigned permutation, bool reverse = false ); //permute inputs of 4 varNum
   void changePhasePermute4( unsigned phase, unsigned permutation, bool reverse = false );
   TruthTable32 operator ~ () const;
   TruthTable32 operator | ( const TruthTable32 &b ) const;
   TruthTable32 operator & ( const TruthTable32 &b ) const;
   void operator &= ( const TruthTable32 &b );
   bool operator == ( const TruthTable32 &b ) const;
   bool operator != ( const TruthTable32 &b ) const;
   static void generatePermute( unsigned varNum = 5 );
   static void generateStretch( const unsigned varNum = 3 );
   static unsigned getPermuteIndex( unsigned permutation, unsigned var );
   static unsigned getStretch( unsigned table, unsigned insertIndex );
   static const unsigned TMasks[5][2];
   static const unsigned VMasks[6];
   static const unsigned char Permute5Var[120][5];
   static const unsigned Stretch3Var[256][4];
   friend ostream &operator << ( ostream &os, const TruthTable32 &a );
protected:
   unsigned _varNum;
   unsigned _table;
};

#endif

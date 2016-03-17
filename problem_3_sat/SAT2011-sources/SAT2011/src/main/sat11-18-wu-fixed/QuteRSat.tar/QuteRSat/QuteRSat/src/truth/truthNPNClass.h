#ifndef _TRUTH_NPNCLASS_
#define _TRUTH_NPNCLASS_
#include <iostream>

using namespace std;

struct NPNData
{
   unsigned _classId;
   unsigned _phase;
   unsigned _permutation;
};

class NPNClass
{
public:
   ~NPNClass();
   static const NPNClass &s_Instance( unsigned varnum );
   static void deleteInstance();
   unsigned getMaxId() const;
   unsigned getSize() const;
   unsigned getClassId( unsigned table ) const;
   unsigned getPhase( unsigned table ) const;
   unsigned getPermute( unsigned table ) const;
   static const unsigned _npnClassNum[5];
private:
   unsigned  _varnum;
   unsigned  _maxId;
   NPNData  *_data;
   
   static NPNClass *_instances[4];
   
   NPNClass( unsigned varnum );
   void setClass();
};

#endif

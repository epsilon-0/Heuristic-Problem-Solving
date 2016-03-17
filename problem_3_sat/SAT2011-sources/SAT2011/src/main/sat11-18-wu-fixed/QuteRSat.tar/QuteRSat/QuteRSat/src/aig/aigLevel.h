#ifndef _AIG_LEVEL_H_
#define _AIG_LEVEL_H_

class AigCircuit;

class AigLevel : public vector<unsigned>
{
public:
   AigLevel() : _maxLevel(0) {;}
   void setLevel( const AigCircuit &cir );
   void updateLevel( const AigCircuit &cir, unsigned index );
   unsigned getMaxLevel() const;
   static AigLevel *_publicPtr;
   static bool sortHighFirst( unsigned a, unsigned b );
private:
   unsigned _maxLevel;
};

#endif

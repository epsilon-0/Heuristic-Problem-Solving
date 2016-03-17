#ifndef _UTIL_MARK_H_
#define _UTIL_MARK_H_
#include <vector>

using namespace std;

class UtilMark : public vector<unsigned>
{
public:
   void initialize( unsigned num );
   void clearMark();
   void setMark( unsigned index );
   void clearMark( unsigned index );
   bool isMark( unsigned index ) const;
protected:
   unsigned         _globalMark;
};

#endif

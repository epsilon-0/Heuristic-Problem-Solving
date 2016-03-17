#ifndef _UTIL_RESOURCE_USAGE_H_
#define _UTIL_RESOURCE_USAGE_H_
#include <ctime>
#include <iostream>

using namespace std;

class ResourceUsage
{
public:
   enum UsageDataFlag
   {
      USAGE_NONE = 0,
      USAGE_CLK_TIME = 1,
      USAGE_RES_TIME = 1 << 1,
      USAGE_WALL_TIME = 1 << 2,
      USAGE_MEMORY   = 1 << 3,
      USAGE_ALL      = (1 << 4) - 1
   };
   
   static ResourceUsage &s_Instance();
   ResourceUsage();
   ~ResourceUsage();
   void clear();
   void setDataFlag( UsageDataFlag dataFlag );
   void unsetDataFlag( UsageDataFlag dataFlag );
   bool isDataFlag( UsageDataFlag dataFlag ) const;
   double getCurResourceTime() const;
   double getTotalResourceTime() const;
   void start();
   void pause();
   void stop();
   void report( ostream &os, bool currentUsage, bool totalUsage );
   
private:
   bool      _running;
   clock_t   _startClock;
   double    _curClockSecond;
   double    _totalClockSecond;
   double    _startResouceSecond;
   double    _curResouceSecond;
   double    _totalResouceSecond;
   time_t    _startWallSecond;
   time_t    _curWallSecond;
   time_t    _totalWallSecond;
   double    _startMemory;
   double    _curMemory;
   double    _totalMemory;
   UsageDataFlag _dataFlag;
   
   void startClock();
   void pauseClock();
   void stopClock();
   void clearClock();
   void startResourceTime();
   void pauseResourceTime();
   void stopResourceTime();
   double getResouceTime();
   void startWallTime();
   void pauseWallTime();
   void stopWallTime();
   time_t getWallTime();
   void startMem();
   void pauseMem();
   void stopMem();
   double getMem();
};

#endif

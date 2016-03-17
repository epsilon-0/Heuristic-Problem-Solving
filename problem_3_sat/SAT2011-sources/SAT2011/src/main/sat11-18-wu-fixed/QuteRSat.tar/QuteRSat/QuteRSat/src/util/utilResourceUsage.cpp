#include <cassert>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <sys/resource.h>
#include "utilResourceUsage.h"
#define CLOCK_MAX ( size_t(1) << ( sizeof(clock_t) - 1 ) )

using namespace std;

ResourceUsage &
ResourceUsage::s_Instance()
{
   static ResourceUsage usage;
   return usage;
}

ResourceUsage::ResourceUsage()
   : _running(false),
     _startClock(0), _curClockSecond(0.0), _totalClockSecond(0.0),
     _startResouceSecond(0.0), _curResouceSecond(0.0), _totalResouceSecond(0.0),
     _startMemory(0.0), _curMemory(0.0), _totalMemory(0.0),
     _dataFlag( USAGE_ALL )
{
}

ResourceUsage::~ResourceUsage()
{
}

double
ResourceUsage::getCurResourceTime() const
{ 
   return _curResouceSecond;
}

double 
ResourceUsage::getTotalResourceTime() const
{
   return _totalResouceSecond;
}

void
ResourceUsage::clear()
{
   _running = false;
   _startClock = 0;
   _curClockSecond = 0.0;
   _totalClockSecond = 0.0;
   _startResouceSecond = 0.0;
   _curResouceSecond = 0.0;
   _totalResouceSecond = 0.0;
   _startMemory = 0.0;
   _curMemory = 0.0;
   _totalMemory = 0.0;
}

void
ResourceUsage::setDataFlag( UsageDataFlag dataFlag )
{
   _dataFlag = dataFlag;
}

void
ResourceUsage::unsetDataFlag( UsageDataFlag dataFlag )
{
   int df = _dataFlag;
   df &= ~dataFlag;
   _dataFlag = static_cast<UsageDataFlag>( df );
}

bool
ResourceUsage::isDataFlag( UsageDataFlag dataFlag ) const
{
   return ( _dataFlag & dataFlag ) != 0;
}

void
ResourceUsage::start()
{
   assert( !_running );
   _running = true;
   if( isDataFlag( USAGE_CLK_TIME ) ) startClock();
   if( isDataFlag( USAGE_RES_TIME ) ) startResourceTime();
   if( isDataFlag( USAGE_WALL_TIME ) ) startWallTime();
   if( isDataFlag( USAGE_MEMORY ) ) startMem();
}

void
ResourceUsage::pause()
{
   assert( _running );
   _running = false;
   if( isDataFlag( USAGE_CLK_TIME ) ) pauseClock();
   if( isDataFlag( USAGE_RES_TIME ) ) pauseResourceTime();
   if( isDataFlag( USAGE_WALL_TIME ) ) pauseWallTime();
   if( isDataFlag( USAGE_MEMORY ) ) pauseMem();
}

void
ResourceUsage::stop()
{
   assert( _running );
   _running = false;
   if( isDataFlag( USAGE_CLK_TIME ) ) stopClock();
   if( isDataFlag( USAGE_RES_TIME ) ) stopResourceTime();
   if( isDataFlag( USAGE_WALL_TIME ) ) stopWallTime();
   if( isDataFlag( USAGE_MEMORY ) ) stopMem();
}

void
ResourceUsage::report( ostream &os, bool currentUsage, bool totalUsage )
{
   if( currentUsage )
   {
      os << "==== Current Usage ==== " << endl;
      if( isDataFlag( USAGE_CLK_TIME ) )
         os << "Clock Time: " << _curClockSecond << " s" << endl;
      if( isDataFlag( USAGE_RES_TIME ) )
         os << "Resource Time: " << _curClockSecond << " s" << endl;
      if( isDataFlag( USAGE_WALL_TIME ) )
         os << "Wall Time: " << _curWallSecond << " s" << endl;
      if( isDataFlag( USAGE_MEMORY ) )
         os << "Memory: " << _curMemory << " MB" << endl;
   }
   if( totalUsage )
   {
      os << "==== Total Usage ==== " << endl;
      if( isDataFlag( USAGE_CLK_TIME ) )
         os << "Clock Time: " << _totalClockSecond << " s" << endl;
      if( isDataFlag( USAGE_RES_TIME ) )
         os << "Resource Time: " << _totalClockSecond << " s" << endl;
      if( isDataFlag( USAGE_WALL_TIME ) )
         os << "Wall Time: " << _totalWallSecond << " s" << endl;
      if( isDataFlag( USAGE_MEMORY ) )
         os << "Memory: " << _totalMemory << " MB" << endl;  
   }
}

void
ResourceUsage::startClock()
{
   _startClock = clock();
   _curClockSecond = 0.0;
}

void
ResourceUsage::pauseClock()
{
   const clock_t nowClock = clock();
   
   if( nowClock >= _startClock )
      _curClockSecond += static_cast<double>( nowClock - _startClock ) / CLOCKS_PER_SEC;
   else _curClockSecond += static_cast<double>( CLOCK_MAX - _startClock + nowClock ) / CLOCKS_PER_SEC;
}

void
ResourceUsage::stopClock()
{
   pauseClock();
   _totalClockSecond += _curClockSecond;
}

void
ResourceUsage::startResourceTime()
{
   _startResouceSecond = getResouceTime();
   _curResouceSecond = 0.0;
}

void
ResourceUsage::pauseResourceTime()
{
   _curResouceSecond += getResouceTime() - _startResouceSecond;
}

void
ResourceUsage::stopResourceTime()
{
   pauseResourceTime();
   _totalResouceSecond += _curResouceSecond;
}

double
ResourceUsage::getResouceTime()
{
   struct rusage usage;
   if( getrusage( RUSAGE_SELF, &usage ) < 0 )
   {
      unsetDataFlag( USAGE_RES_TIME );
      return 0.0;
   }
   return static_cast<double>( usage.ru_utime.tv_sec ) + static_cast<double>( usage.ru_utime.tv_usec ) * 1e-6;
}

void
ResourceUsage::startWallTime()
{
   _startWallSecond = getWallTime();
   _curWallSecond = 0;
}

void
ResourceUsage::pauseWallTime()
{
   _curWallSecond = getWallTime() - _startWallSecond;
}

void
ResourceUsage::stopWallTime()
{
   pauseWallTime();
   _totalWallSecond += _curWallSecond;
}

time_t
ResourceUsage::getWallTime()
{
   return time( NULL );
}

void
ResourceUsage::startMem()
{
   _startMemory = getMem();
}

void
ResourceUsage::pauseMem()
{
   _curMemory += getMem() - _startMemory;
}

void
ResourceUsage::stopMem()
{
   pauseMem();
   _totalMemory += _curMemory;
}

double
ResourceUsage::getMem()
{
   ifstream fstatus("/proc/self/status");
 
   _curMemory = 0.0;  
   if( !fstatus )
   {
      unsetDataFlag( USAGE_MEMORY );
      return 0.0;  
   }
   
   char buffer[256];
   
   while( !fstatus.eof() )
   {
      fstatus.getline( buffer, 256 );
      if( strncmp( buffer, "VmSize", 6 ) == 0 )
      {
         double memSize = atol( strchr(buffer, ' ') );
         return memSize / 1024.0;  //MB
      }
   }
   unsetDataFlag( USAGE_MEMORY );
   return 0.0;
}

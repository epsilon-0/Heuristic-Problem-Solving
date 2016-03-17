#ifndef _UTIL_GLOBAL_DATA_
#define _UTIL_GLOBAL_DATA_
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <map>

using namespace std;

template <class T>
class GlobalData
{
public:
   static GlobalData<T>& s_Instance() 
   {
      static GlobalData<T> globaldata;
      return globaldata;
   }
   ~GlobalData()
   {
      clear();
   }
   void clear()
   {
      for( unsigned i = 0; i < _data.size(); i++ )
         if( _data[i] != NULL )
            delete _data[i];
      _data.clear();
      _idMap.clear();
      _curptr = 0;
   }
   void setName( const string name )
   {
      _name = name;
   }
   void report( ostream &os, bool useId = false ) const
   {
      if( _data.empty() ) return;
      os <<"------ GlobalData of " << _name << " ------" << endl;
      if( useId )
         for( map<string,unsigned>::const_iterator mi = _idMap.begin();
              mi != _idMap.end(); mi++ )
         {
            unsigned i = mi->second;
            if( i == _curptr ) cout << "*";
            else cout << " ";
            if( _data[i] == NULL ) continue;
             cout << setw(8) << mi->first << " : ";
            _data[i]->report( os );
         }
      else
         for( unsigned i = 0; i < _data.size(); i++ )
         {
            if( i == _curptr ) cout << "*";
            else cout << " ";
            cout << setw(2) << i << "th : ";
            if( _data[i] != NULL )
               _data[i]->report( os ); 
            else os << "NULL "<< endl;
         }
   }
   T * getCurrent()
   {
      if( _data.empty() )
      {
         cerr<<"Error: GlobalData: No current " << _name << endl;
         return NULL;
      }
      else return _data[_curptr];
   }
   T * getData( unsigned index )
   {
      return ( _data.size() > index ) ? _data[index] : NULL;
   }
   T *getData( const string &id )
   {
      if( _idMap.find(id) == _idMap.end() )
      {
         cerr << "Error: GlobalData: No such id: " << id << endl;
         return NULL;
      }
      return getData( _idMap[id] );
   }
   void pushBack( T * newptr, string id = "" )
   {
      _curptr = _data.size();
      _data.push_back( newptr );
      if( !id.empty() ) _idMap[id] = _curptr;
   }
   void popBack()
   {
      if( _data.back() != NULL )
         delete _data.back(); 
      _data.pop_back();  
      if( _curptr >= _data.size() ) 
         _curptr = _data.size();
   }
   void setCurrent( unsigned index )
   {
      _curptr = _data.empty() ? 0 : ( _data.size() > index ) ? index : _data.size() - 1;
   }
   void setCurrent( const string &id )
   {
      if( _idMap.find(id) == _idMap.end() )
      {
         cerr << "Error: GlobalData: No such id: " << id << endl;
         return;
      }
      return setCurrent( _idMap[id] );
   }
   void insertCurrent( T * newptr )
   {
      insertData( _curptr, newptr );
   }
   void insertData( unsigned index, T * newptr )
   {
      deleteData( index );
      if( _data.size() <= index ) _data.resize( index + 1, NULL );
      _data[index] = newptr;
   }
   void deleteCurrent()
   {
      deleteData( _curptr );
   }
   void deleteData( unsigned index )
   {
      if( _data.size() <= index ) return;
      if( _data[index] != NULL )
         delete _data[index];
      _data[index] = NULL;
      if( index + 1 == _data.size() )
         while( !_data.empty() && _data.back() == NULL )
            popBack();
   }
protected:
   string               _name;
   unsigned             _curptr;
   vector<T*>           _data;
   map<string,unsigned> _idMap;
};

#endif


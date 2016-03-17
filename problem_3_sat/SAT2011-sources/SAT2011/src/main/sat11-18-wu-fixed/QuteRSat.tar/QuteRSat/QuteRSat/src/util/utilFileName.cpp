#include<iostream>
#include<vector>
#include<string>
#include<dirent.h>

using namespace::std;
   
bool matchString( string& a, string& b )
{
   const unsigned asize = a.size();
   const unsigned bsize = b.size();
   unsigned i;
   for( i = 0; i < asize; i++ )
   {
      if( a[i] == '*' ) break;
      if( i >= bsize ) return false;
      if( a[i] != b[i] ) return false;
   }
   for( i = 0; i < asize; i++ )
   {
      if( a[asize-i-1] == '*' ) break;
      if( i >= bsize ) return false;
      if( a[asize-i-1] != b[bsize-i-1] ) return false;
   }
   return true;
}

void splitFullPath( string& fullpath, string& path, string& fname, string& ext )
{
   const size_t fpsize = fullpath.size();
   size_t sindex, pindex;
   path.clear();
   fname.clear();
   ext.clear();
   if( fpsize == 0 ) return;
   sindex = fullpath.rfind('.');
   if( sindex == string::npos ) sindex = fpsize;
   else ext.assign( fullpath, sindex, fpsize - sindex );
   pindex = fullpath.rfind('/');
   if( pindex == string::npos ) pindex = 0;
   else ++pindex;
   if( pindex > 0 ) path.assign( fullpath, 0, pindex );
   if( pindex < sindex )
      fname.assign( fullpath, pindex, sindex - pindex );
}

void findFileList( string& fullpath, vector<string>& fnamelist )
{
   string path, fname[2], ext[2];
   string dname;
   DIR *dp;
   struct dirent * d;
	splitFullPath( fullpath, path, fname[0], ext[0] );
	dp = opendir( path.c_str() );
	if( dp == NULL ) return;
	while( ( d = readdir(dp) ) != NULL )
	{
		dname = string( d->d_name );
		if( dname == "." || dname == ".." ) continue;
		splitFullPath( dname, path, fname[1], ext[1] );
		if( matchString(ext[0],ext[1]) && matchString(fname[0],fname[1]) )
		   fnamelist.push_back( fname[1] + ext[1] );
	}
	return;
}


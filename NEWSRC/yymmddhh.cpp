#ifdef _DOS
#include <afx.h>
#else
#include <afxwin.h>
#endif
#include <afxcoll.h>
                         
#include <iostream.h>                         
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>  
#include <sys\types.h>
#include <sys\stat.h>                  
#include <direct.h>

  

#define BATFILE c:\\yymmddhh.bat
#define BKUPROOTDIR "e:\\bkup"  


struct _stat sbuf;
//char bkuppath[_MAX_PATH], yymmddhh_str[_MAX_PATH], yymmddhhenv_str[_MAX_PATH];
char yymmddhh_str[_MAX_PATH];
struct tm *newtime;
time_t aclock;

FILE *yymmfile;

int
main( int argc, char *argv[] )
{
 
    CStdioFile se( stderr );
    CFileStatus status;
    CString sBkuppath;  

    
	if( argc == 1 ) {
		//fprintf( stderr, "using default backup root directory = '%s'\n", BKUPROOTDIR ); 
		//se.WriteString( "using default backup root directory = '"+ (CString)BKUPROOTDIR+"'\n" );
		cerr << "using default backup root directory = '" << BKUPROOTDIR << "'\n";
		//strcpy ( bkuppath, BKUPROOTDIR );
		sBkuppath = BKUPROOTDIR ;
	} else if (argc == 2 ) {
		/* argv[1] is a backup root directory.  verify it exists first */ 
		//strcpy ( bkuppath, argv[1] ); 
		sBkuppath = argv[1];
		//if ( (_stat(sBkuppath,&sbuf)==0 && sbuf.st_mode&S_IFDIR != S_IFDIR) 
   			//|| _stat(sBkuppath,&sbuf)==-1 )    {
   		if( (CFile::GetStatus( sBkuppath, status ) && status.m_attribute&0x10 != 0x10)
   			|| ! CFile::GetStatus( sBkuppath, status ) ) {	
   			//fprintf( stderr, "The directory '%s' does not exist\n", bkuppath );   
   			//se.WriteString( "The directory '+sBkuppath+' does not exist\n" );
   			cerr << "The directory '" << sBkuppath << "' does not exist\n";
   		    exit( -1 );	 
   		}	
	}    


		
    CStdioFile yymmfile;
    if( !yymmfile.Open( "c:\\yymmddhh.bat",
		CFile::modeCreate | CFile::modeWrite | CFile::typeText ) ) { 
		//fprintf( stderr,  "yymmddhh file could not open\n" ); 
		//se.WriteString( "yymmddhh file could not open\n" );
		cerr << "yymmddhh file could not open\n";
	    exit( 1 );
	}
	//fprintf( stderr, "Creating file c:\\yymmddhh.bat\n" );
	//se.WriteString( "Creating file c:\\yymmddhh.bat\n" );
	cerr << "Creating file c:\\yymmddhh.bat\n";

	/* Open for write */
   //if( (yymmfile = fopen( "c:\\yymmddhh.bat", "w" )) == NULL ) {
     // fprintf( stderr,  "yymmddhh file could not open\n" ); 
      //exit( -1 );      
   //}
   
   
   

   //strcat ( bkuppath, "\\" );   
   sBkuppath += "\\";
   //fprintf( stderr, "bkuppath='%s'\n", bkuppath );
   //se.WriteString( "sBkuppath='"+sBkuppath+"'\n" );  
   cerr << "sBkuppath='" << sBkuppath << "'\n";
   
   //time( &aclock );                 /* Get time in seconds */
   //newtime = localtime( &aclock );  /* Convert time to struct tm form  */
                                                                            
                                                                            
   /*
   sprintf( yymmddhh_str, "Year-'%d', Month-'%d', Day-'%d', Hour-'%d'", 
   			newtime->tm_year, newtime->tm_mon, newtime->tm_mday, newtime->tm_hour);
   fprintf( stderr, "yymmddhh_str='%s'\n", yymmddhh_str );
   */
   
   //sprintf( yymmddhh_str, "%2.2d%2.2d%2.2d%2.2d", 
   			//newtime->tm_year, newtime->tm_mon, newtime->tm_mday, newtime->tm_hour);  
   			
   CTime t = CTime::GetCurrentTime();
   sprintf( yymmddhh_str, "%2.2d%2.2d%2.2d%2.2d",
   			t.GetYear()-1900, t.GetMonth(), t.GetDay(), t.GetHour() );
   			
   //fprintf( stderr, "yymmddhh_str='%s'\n", yymmddhh_str ); 
   //se.WriteString( "yymmddhh_str='"+(CString)yymmddhh_str+"'\n" );
   cerr << "yymmddhh_str='" << yymmddhh_str << "'\n";
   
   //fprintf( yymmfile, "set yymmddhh=%s\n", yymmddhh_str);
   yymmfile.WriteString( "set yymmddhh=" + (CString)yymmddhh_str + "\n" );
   
   //sprintf( yymmddhhenv_str, "yymmddhh=%s\n", yymmddhh_str);
   //_putenv( yymmddhhenv_str );     // this does not work.  it gets zapped on exit
   //system( "set" );    
   
   //strcat ( bkuppath, yymmddhh_str );
   sBkuppath += yymmddhh_str;
   //fprintf( stderr, "bkuppath='%s'\n", bkuppath );        
   //se.WriteString( "sBkuppath='"+sBkuppath+"'\n" );
   cerr << "sBkuppath='" << sBkuppath << "'\n";
   
   //fprintf( yymmfile, "set bkuppath=%s\n", bkuppath);
   yymmfile.WriteString( "set bkuppath=" + sBkuppath + "\n" );  
   
   //cerr << "test << for stderr";
   
   /* Does the backup directory exist?  If not, creat it */
   //if ( (_stat(sBkuppath,&sbuf)==0 && sbuf.st_mode&S_IFDIR != S_IFDIR) 
   		//|| _stat(sBkuppath,&sbuf)==-1 )    {
   if ( ! CFile::GetStatus( sBkuppath, status ) ) {		
   		//fprintf( stderr, "The directory '%s' does not exist, creating it.\n", bkuppath );
   		//se.WriteString( "The directory '"+sBkuppath+"' does not exist, creating it.\n" );
   		cerr << "The directory '"+sBkuppath+"' does not exist, creating it.\n";
   		if( _mkdir( sBkuppath ) != 0 ) {
   			//fprintf( stderr," Unable to create directory '%s'. Exiting...\n", bkuppath );
   			//se.WriteString( " Unable to create directory '"+sBkuppath+"'. Exiting...\n" );
   			cerr << " Unable to create directory '"+sBkuppath+"'. Exiting...\n";
   			exit( -1 );	 
   		}	
   }    
   

 


   	
   /* Close stream */
   //if( fclose( yymmfile ) )   {
      //fprintf( stderr, "yymmddhh file could not close\n" );
      //exit( -1 );      
   //}
      
      
   return( 0 );   
                                                                     
}                                                                     
                                                                     
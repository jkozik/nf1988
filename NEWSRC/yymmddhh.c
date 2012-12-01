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
char bkuppath[_MAX_PATH], yymmddhh_str[_MAX_PATH], yymmddhhenv_str[_MAX_PATH];
struct tm *newtime;
time_t aclock;

FILE *yymmfile;

int
main( int argc, char *argv[] )
{
 

	if( argc == 1 ) {
		fprintf( stderr, "using default backup root directory = '%s'\n", BKUPROOTDIR );
		strcpy ( bkuppath, BKUPROOTDIR );
	} else if (argc == 2 ) {
		/* argv[1] is a backup root directory.  verify it exists first */ 
		strcpy ( bkuppath, argv[1] ); 
		if ( (_stat(bkuppath,&sbuf)==0 && sbuf.st_mode&S_IFDIR != S_IFDIR) 
   			|| _stat(bkuppath,&sbuf)==-1 )    {
   			fprintf( stderr, "The directory '%s' does not exist\n", bkuppath );
   		    exit( -1 );	 
   		}	
	}    


		
    
	/* Open for write */
   if( (yymmfile = fopen( "c:\\yymmddhh.bat", "w" )) == NULL ) {
      fprintf( stderr,  "yymmddhh file could not open\n" ); 
      exit( -1 );      
   }
   

   strcat ( bkuppath, "\\" );   
   fprintf( stderr, "bkuppath='%s'\n", bkuppath );  
   
   time( &aclock );                 /* Get time in seconds */
   newtime = localtime( &aclock );  /* Convert time to struct tm form  */
                                                                            
                                                                            
   /*
   sprintf( yymmddhh_str, "Year-'%d', Month-'%d', Day-'%d', Hour-'%d'", 
   			newtime->tm_year, newtime->tm_mon, newtime->tm_mday, newtime->tm_hour);
   fprintf( stderr, "yymmddhh_str='%s'\n", yymmddhh_str );
   */
   
   sprintf( yymmddhh_str, "%2.2d%2.2d%2.2d%2.2d", 
   			newtime->tm_year, newtime->tm_mon, newtime->tm_mday, newtime->tm_hour);
   fprintf( stderr, "yymmddhh_str='%s'\n", yymmddhh_str ); 
   fprintf( yymmfile, "set yymmddhh=%s\n", yymmddhh_str);
   sprintf( yymmddhhenv_str, "yymmddhh=%s\n", yymmddhh_str);
   _putenv( yymmddhhenv_str );     // this does not work.  it gets zapped on exit
   //system( "set" );    
   
   strcat ( bkuppath, yymmddhh_str );
   fprintf( stderr, "bkuppath='%s'\n", bkuppath );       
   fprintf( yymmfile, "set bkuppath=%s\n", bkuppath);
   
   /* Does the backup directory exist?  If not, creat it */
   if ( (_stat(bkuppath,&sbuf)==0 && sbuf.st_mode&S_IFDIR != S_IFDIR) 
   		|| _stat(bkuppath,&sbuf)==-1 )    {
   		fprintf( stderr, "The directory '%s' does not exist, creating it.\n", bkuppath );
   		if( _mkdir( bkuppath ) != 0 ) {
   			fprintf( stderr," Unable to create directory '%s'. Exiting...\n", bkuppath );
   			exit( -1 );	 
   		}	
   }    
   

 


   	
   /* Close stream */
   if( fclose( yymmfile ) )   {
      fprintf( stderr, "yymmddhh file could not close\n" );
      exit( -1 );      
   }   
      
   return( 0 );   
                                                                     
}                                                                     
                                                                     
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

#define cntMONTHS	13
CString months[cntMONTHS] = {"00","01","02","03","04","05","06","07","08","09","10","11","12"};
#define cntYEARS	8
CString years[cntYEARS] = {"91","92","93","94","95","96","97","98"};

void SearchSglFile(CStdioFile * sglfile, CString sStock, CString year );

int
main( int argc, char *argv[] )
{

	char *eF, *eYEAR;  
	CString sRootDir, sSglFile, sSglDir, sTickerSymbol;
	                                                               
	                                                               
	if( argc != 2 ) {
		cerr << "usage:  stkdtl TICKER\n";
		return -1;
	}
	
	sTickerSymbol = argv[1];
	cerr << "sTickerSymbol=" << sTickerSymbol << "\n";
	
		                                                                
	CStdioFile sglfile;
	eF = getenv ( "F" );
	eYEAR = getenv( "YEAR" );
	cerr << "F=" << eF << " YEAR=" << eYEAR << "\n";      
	
	sRootDir = "\\" + (CString)eF;	
	if( _chdir( sRootDir ) ) {
		cerr << "Unable to switch to directory=" << sRootDir;
	}
	
	for( int idxYears=0; idxYears<cntYEARS; idxYears++  ) {
		for( int idxMonths=0; idxMonths<cntMONTHS; idxMonths++ ) {  
			sSglDir = sRootDir + "\\" + years[idxYears];  
			_chdir( sSglDir ); 
			
			sSglFile = months[idxMonths] + ".sgl";
			//cerr << years[idxYears] << " " << months[idxMonths] << "sSglFile=" << sSglFile << "\n";
			if(  sglfile.Open( sSglFile, CFile::modeRead | CFile::typeText ) ) {
				SearchSglFile( &sglfile, sTickerSymbol, years[idxYears] );
				//cerr << "sSglFile=" << sSglFile << " openned successfully.\n";
				sglfile.Close();
			}	
			
		}
	}		
	                                           
	                                           
	return 0;
}		
void SearchSglFile(CStdioFile * sglfile, CString sStock, CString year )
{   
	CString sInputLine, sTmp;
	char caInputLine[_MAX_PATH];
	int idx;
	while( sglfile->ReadString( caInputLine, _MAX_PATH-1 ) != NULL ) {
		sInputLine = caInputLine; 
		if( sInputLine.Find( ",261," )>=0 || sInputLine.Find( ",262," )>=0 ) {
			if( sInputLine.Find( sStock )>=0 ) {
				cerr << year + ":" << sInputLine ; 
				cout << "\"" << sInputLine.Left(2);
				cout << "/" << sInputLine.Mid(2,2);
				cout << "/" << year << "\",";    
				cout << "\"" << sInputLine.Mid(5,3);
				cout << "\",";
				 
				sTmp = sInputLine.Mid(9);  
				sInputLine = sTmp;
				idx = sInputLine.Find( "," );
				cout << "\"" << sInputLine.Left( idx ) << "\",";
				
				sTmp = sInputLine.Mid(idx+1);  
				sInputLine = sTmp;
				 
				idx = sInputLine.Find( " " );
				cout << "\"" << sInputLine.Left( idx ) << "\","; 
				  
				sTmp = sInputLine.Mid(idx+1);  
				sInputLine = sTmp;
			  
				idx = sInputLine.Find( " " );
				cout << "\"" << sInputLine.Left( idx ) << "\","; 
				  
				sTmp = sInputLine.Mid(idx+1);  
				sInputLine = sTmp;
				
				
				if( sInputLine.Left(6) != "shs @ " ) {
					cerr << "Sgl Record syntax incorrect.  Ignoring...\n";
					continue;
				}
				sTmp = sInputLine.Mid(6);
				sInputLine = sTmp.Left(sTmp.GetLength()-1);
				cout << "\"" << sInputLine << "\"";
				cout << "\n";
					
			}	
		}	
	};

}
#ifdef _DOS
#include <afx.h>
#else
#include <afxwin.h>
#endif
#include <afxcoll.h>
                         
#include <iostream.h>                         
#include <fstream.h>  
#include <iomanip.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>  
#include <sys\types.h>
#include <sys\stat.h>                  
#include <direct.h>
                             
#include "gldefs.h"                             
char cwdstr[SZPATH+1];
                       
#define cntMONTHS	13
CString months[cntMONTHS] = {"00","01","02","03","04","05","06","07","08","09","10","11","12"};
#define cntYEARS	18
CString years[cntYEARS] = {"91","92","93","94","95","96","97","98","99","00","01","02","03","04","05","06","07","08"};

void SearchSglFile(CStdioFile * sglfile, CString sStock, CString year );
                                                                          
ofstream stkdtlfile, tickerfile;                                        
double fAmt=0, fShares=0, fCumAmt=0, fCumShares=0, fPrice;                                  
int
main( int argc, char *argv[] )
{

	char *eF, *eYEAR;  
	CString sRootDir, sSglFile, sSglDir, sTickerSymbol;
	stkdtlfile << setiosflags( ios::fixed );	                                                               
	fAmt=0, fShares=0, fCumAmt=0, fCumShares=0;                                                               
	if( argc != 2 ) {
		cerr << "usage:  stkdtl TICKER\n";
		return -1;
	}
	
	sTickerSymbol = argv[1];
	// cerr << "sTickerSymbol=" << sTickerSymbol << "\n"; 
	
	
		                                                                
	CStdioFile sglfile;
	eF = getenv ( "F" );
	eYEAR = getenv( "YEAR" );
	 cerr << "F=" << eF << " YEAR=" << eYEAR << "\n";  
	
	getcwd(cwdstr,SZPATH);          
	 cerr << "CWD=" << cwdstr << "\n";
	
	sRootDir = "\\" + (CString)eF;	
	if( _chdir( sRootDir ) ) {
		cerr << "Unable to switch to directory=" << sRootDir;
	}           
	
	stkdtlfile.open( (CString)eYEAR + "\\stkdtl.out" ); 
	stkdtlfile << "\nTicker Symbol = " << sTickerSymbol + "\n\n"; 
	stkdtlfile << "DATE     ACCT   AMOUNT     SHARES      PRICE  CumAMOUNT CumSHARES\n";	
	tickerfile.open( (CString)eYEAR + "\\" + sTickerSymbol + ".csv" );
	// cerr << "stkdtlfile opened" << "\n";
	
	if( eYEAR<"10" && eYEAR > years[cntYEARS-1] ) {
		cerr << "stkdtl: Maximum Year Supported is '" << years[cntYEARS-1] << "'\n";
	}		
	
	int iYYYY;
	if( atoi(eYEAR) < 10 ) {
		iYYYY = 2000 +  atoi(eYEAR);
	} else {
		iYYYY = 1900 + atoi(eYEAR);
	}                                      
	// cerr << "iYYYY=" << iYYYY << "\n";  
	// cerr << "eYEAR=" << eYEAR << "\n";
	// real calendar year = idxYears + 1991		
	for( int idxYears=0; idxYears<cntYEARS && idxYears+1991<=iYYYY; idxYears++  ) {
		// cerr << "idxYears=" << idxYears << "\n";
		for( int idxMonths=0; idxMonths<cntMONTHS; idxMonths++ ) {  
			sSglDir = sRootDir + "\\" + years[idxYears];  
			_chdir( sSglDir ); 
			
			sSglFile = months[idxMonths] + ".sgl";
			// cerr << years[idxYears] << " " << months[idxMonths] << "sSglFile=" << sSglFile << "\n";
			if(  sglfile.Open( sSglFile, CFile::modeRead | CFile::typeText ) ) {
				SearchSglFile( &sglfile, sTickerSymbol, years[idxYears] );
				// cerr << "sSglFile=" << sSglFile << " openned successfully.\n";
				sglfile.Close();
			}	
			
		}
	}		
	stkdtlfile << "      *TOTAL-" 
	            << setw(9) << setprecision(2) << fCumAmt << "*" 
				<< setw(10) << setprecision(4) << fCumShares << "*\n"; 
	_chdir ( cwdstr );	
		getcwd(cwdstr,SZPATH);          
	 cerr << "CWD=" << cwdstr << "\n";		                             
	return 0;
}		
void SearchSglFile(CStdioFile * sglfile, CString sStock, CString year )
{   
	CString sInputLine, sTmp;
	CString sDate, sAcct, sAmt, sShares, sPrice, sTickerSymbol, sDesc; 

	char caInputLine[_MAX_PATH], *stop;
	int idx;
	while( sglfile->ReadString( caInputLine, _MAX_PATH-1 ) != NULL ) {
		sInputLine = caInputLine; 
		if( sInputLine.Find( ",261," )>=0 || sInputLine.Find( ",262," )>=0
			|| sInputLine.Find( ",237," )>=0 || sInputLine.Find( ",238," )>=0 ) {
			if( sInputLine.Find( sStock )>=0 ) {
				//stkdtlfile << year + ":" << sInputLine ;
				
				sDate = sInputLine.Left(2) + "/" + sInputLine.Mid(2,2) + "/" + year; 
				tickerfile << "\"" + sDate + "\",";
				//tickerfile << "\"" << sInputLine.Left(2);
				//tickerfile << "/" << sInputLine.Mid(2,2);
				//tickerfile << "/" << year << "\","; 
				
				sAcct =  sInputLine.Mid(5,3);
				tickerfile << "\"" + sAcct + "\",";  
				//tickerfile << "\"" << sInputLine.Mid(5,3);
				//tickerfile << "\",";
				 
				sTmp = sInputLine.Mid(9);  
				sInputLine = sTmp;
				idx = sInputLine.Find( "," );  
				sAmt =  sInputLine.Left( idx );
				fAmt = strtod( sAmt, &stop);
				tickerfile << "\"" + sAmt + "\",";
				//tickerfile << "\"" << sInputLine.Left( idx ) << "\",";
				
				sTmp = sInputLine.Mid(idx+1);  
				sInputLine = sTmp;
				 
				idx = sInputLine.Find( " " );  
				sTickerSymbol =  sInputLine.Left( idx );
				tickerfile << "\"" + sTickerSymbol + "\",";
				//tickerfile << "\"" << sInputLine.Left( idx ) << "\","; 
				  
				sTmp = sInputLine.Mid(idx+1);  
				sInputLine = sTmp;
			  
				
				
				if( sInputLine.Find( " shs @ " ) < 0 )  {
					
					sShares = "";
					
					fShares = 0;
					sPrice = "";
					fPrice = 0; 
					sDesc = sInputLine.Left(sInputLine.GetLength()-1);
					
				} else {
					idx = sInputLine.Find( " " );
					sShares = sInputLine.Left( idx );
					fShares = strtod( sShares, &stop);
				  
					sTmp = sInputLine.Mid(idx+1);  
					sInputLine = sTmp;
				  
					sDesc = "";
					sTmp = sInputLine.Mid(6);
					sPrice = sTmp.Left(sTmp.GetLength()-1); 
					fPrice = strtod( sPrice, &stop );
				}
				tickerfile << "\"" + sShares + "\",";
				tickerfile << "\"" + sPrice + "\"";
				tickerfile << "\n";	
				fCumAmt = fCumAmt + fAmt;
				fCumShares = fCumShares + fShares;
				
				//stkdtlfile << "fCumAmt=" << setprecision(2) << fCumAmt << " fCumShares=" << setprecision(4) <<fCumShares << "\n";
				stkdtlfile << sDate + " " + sAcct << " "
							<< setw(9) << setprecision(2) << fAmt << " "
							<< setw(10) << setprecision(4) << fShares << " @ "
							<< setw(9) << setprecision(4) << fPrice << " "    
							<< setw(9) << setprecision(2) << fCumAmt << " " 
							<< setw(9) << setprecision(4) << fCumShares << " " 
							<< sDesc 
							<< "\n"; 
						
							 	
			}	
		}	
	};

}

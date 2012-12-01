#include "amt.h"
#include "ctype.h"
#include "stdlib.h"
#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__ ;
#endif

// amt.cpp - Defines the class member functions for CAmt


/////////////////////////////////////////////////////////////////////////
// CAmt::CAmt
// Default and Single argument constructors
//
CAmt::CAmt() {m_lAmt = 0;};
CAmt::~CAmt() {};

CAmt::CAmt( const char* pszAmt ){*this = pszAmt; };

CAmt::CAmt( const long lAmt ) {m_lAmt = lAmt;};

CAmt::CAmt( const CAmt& Amt ) { m_lAmt = Amt; };
////////////////////////////////////////////////////////////////////////////
// CAmt::Set
// If Amount is valid, return TRUE, set m_lAmt
//
BOOL CAmt::Set( const char* pszAmt )
{
    long amt;
    int sign;
    const char* arptr;

    amt = 0;
    arptr = pszAmt;
    sign = 1;
    if (*arptr == '-') {
	sign = -1;
	arptr++;
    }
    while (isdigit(*arptr)) {
	amt = amt*10 + (int)*arptr - (int)'0';
	arptr++;
    }
    if (*arptr == '.') {
	arptr++;
	if (isdigit(*arptr)) {
		amt = amt*10 + (int)*arptr - (int)'0';
		arptr++;
	}
	if (isdigit(*arptr)) {
		amt = amt*10 + (int)*arptr - (int)'0';
		arptr++;
	}
     } else {
	amt = amt * 100;
     }

	/* set sign */
	amt = amt*sign;

	if (*arptr != '\0') {
	       m_lAmt = 0;
	       return FALSE;
	} else {
		m_lAmt = amt;
		return TRUE;
	}

}
BOOL CAmt::Set( const long lAmt )    // 100L eqv to 1.00
{
    m_lAmt = lAmt;
    return TRUE;

}

///////////////////////////////////////////////////////////////////////
// CAmt::Valid
// Validate Always TRUE
//
BOOL CAmt::Valid() const
{
    return TRUE;
}

////////////////////////////////////////////////////////////////////////
// CAmt::Get
// Return String for m_lAmt
//
const CString CAmt::Get() const
{
    long amt;
    char ar[100],*arptr;
    int sign, lsd;
    amt = m_lAmt;
    arptr = ar;
    sign = 1;
    *ar = '\0';

    /* sign */
    if (amt < 0L) {
	sign = -1;
	amt = amt * -1L;
    }

	/*
	** 10000 converts to
	**	 DMAMT - 100.00
	*/
	//if (amt!=(amt/100L)*100L && domain==DMBUDAMT || domain==DMAMT) {

	   /* hundreths */
	   lsd = (int) ( amt - (amt/10L)*10L);
	   *arptr = (char) (lsd + (int)'0');
	   arptr++;
	   amt = amt/10L;

	   /* tenths */
	   lsd = (int) (amt - (amt/10L)*10L);
	   *arptr = (char) (lsd + (int)'0');
	   arptr++;
	   amt = amt/10L;

	   /* decimal */
	   *arptr = '.';
	   arptr++;


	/* string should have leading zero:  0.12, -0.01, etc. */
	if (amt == 0L) {
		*arptr = '0';
		arptr++;
	}

	/* integer part */
	while ( amt != 0L) {
		lsd = (int)(amt - (amt/10L)*10L);
		*arptr = (char) ((int)lsd + (int)'0');
		arptr++;
		amt = amt/10L;
	}



	/* sign */
	if (sign == -1) {
		*arptr = '-';
		arptr++;
	}
	*arptr = '\0';
	return	CString( strrev(ar) );	// Needs to be fixed!!
}

////////////////////////////////////////////////////////////////////
// CAmt::Value
// Return long amount
//
long CAmt::Value()
{
    return m_lAmt;
}

////////////////////////////////////////////////////////////////////
// CAmt::operator=
// Assignment operator for copy and long
//
CAmt& CAmt::operator=( const CAmt& b )
{
    m_lAmt = b.m_lAmt;
    return *this;
}
CAmt& CAmt::operator=( const long lAmt )
{
    m_lAmt = lAmt;
    return *this;
}
CAmt& CAmt::operator=( const char* pszAmt )
{
    (void) Set( pszAmt );
    return *this;

}
CAmt operator+( const CAmt& Amt, const char* pszAmt )
{
    CAmt amt( pszAmt );
    return CAmt( amt + Amt );
}

/////////////////////////////////////////////////////////////////////
// CAmt::operator==
//
BOOL CAmt::operator==( const CAmt& a )
{
    return ( a.m_lAmt == m_lAmt ) ;
}
BOOL CAmt::operator==( const long a )
{
    return ( a == (long) m_lAmt ) ;
}
/////////////////////////////////////////////////////////////////////
// CAmt::operator long() const
//
CAmt::operator long() const
{
    return (long)m_lAmt;
}

///////////////////////////////////////////////////////////////////
// CAmt::Test
// Test the CAmt class
//
BOOL
CAmt::Test()
{
    TRACE( "\nEntering CAmt::Test()\n");

    CMemoryState point, endpoint, diff;
    point.Checkpoint();

    {
    CAmt amt;
    amt = CAmt("1.00");
    afxDump << "\n" << amt << " " << amt.Get();
    amt = amt + CAmt(100);
    afxDump << "\n" << amt << " " << amt.Get();
    amt = amt + 155;
    afxDump << "\n" << amt << " " << amt.Get();


    amt.Set("99");
    ASSERT( amt.Get() == "99.00" );
    ASSERT( amt == 9900L );
    amt.Set(9900);
    ASSERT( amt.Get() == "99.00" );
    ASSERT( amt == 9900L );

    goto endTest;
endTest: ;
    TRACE( "\nLeaving CAmt::Test()\n" );
    }
    endpoint.Checkpoint();
    if( diff.Difference( point, endpoint ) ) {
	afxDump << "\n";
	diff.DumpStatistics();
	diff.DumpAllObjectsSince();
    }

    return TRUE;
}

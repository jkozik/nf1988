#include "chart.h"
#include "je.h"
#include "env.h"
#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__ ;
#endif

// clstest.cpp : Calls the class's ::Test() functions

CEnv env;

void main()
{

    CMemoryState point;
    point.Checkpoint();
    afxDump << "\n";
    point.DumpStatistics();

    afxDump << env;


    GltAllMonths::Test();
#if FALSE
    CChartList::Test();
    CAmt::Test();
    CGlTran::Test();
    CGltArray::Test();
    CJournalEntry::Test();
    CJEList::Test();
#endif
    point.Checkpoint();
    afxDump << "\n";
    point.DumpStatistics();
    point.DumpAllObjectsSince();
}

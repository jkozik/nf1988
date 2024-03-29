#ident "@(#)/usr/src/lib/libc/port/gen/tfind.c  1.2 6/6/85 05:59:51 - Amdahl/UTS"
/*      @(#)tfind.c     1.2     */
/*LINTLIBRARY*/
/*
 * Tree search algorithm, generalized from Knuth (6.2.2) Algorithm T.
 *
 * The NODE * arguments are declared in the lint files as char *,
 * because the definition of NODE isn't available to the user.
 */

#include <search.h>
typedef char *POINTER;
typedef struct node { POINTER key; struct node *llink, *rlink; } NODE;

#define NULL    0


/*      tfind - find a node, or return 0        */
NODE *
tfind(key, rootp, compar)
POINTER key;                    /* Key to be located */
register NODE   **rootp;        /* Address of the root of the tree */
int     (*compar)();            /* Comparison function */
{
        if (rootp == NULL)
                return (NULL);
        while (*rootp != NULL) {                        /* T1: */
                int r = (*compar)(key, (*rootp)->key);  /* T2: */
                if (r == 0)
                        return (*rootp);        /* Key found */
                rootp = (r < 0) ?
                    &(*rootp)->llink :          /* T3: Take left branch */
                    &(*rootp)->rlink;           /* T4: Take right branch */
        }
        return (NODE *)(NULL);
}

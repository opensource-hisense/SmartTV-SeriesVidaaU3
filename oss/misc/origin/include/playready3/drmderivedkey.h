/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __DRMDERIVEDKEY_H__
#define __DRMDERIVEDKEY_H__

ENTER_PK_NAMESPACE;

/*
** Macro that defines the location prefix:
** Each bit of '1' represents a path leg from the root to the
** key tree node that is represented by the location. All
** other bits are 0. In other words, the prefix is a bit mask
** with all bits before the stop bit be 1 and all bits from the
** stop bit be 0.
*/
#define LP( x )     ( ~( ( x ) ^ ( ( x ) -1 ) ) )

/*
** Macro that defines the stop bit mask which is a bit mask with
** all bits except the stop bit be 0.
*/
#define SBM( x )    ( ( ( ~LP( x ) ) >> 1 ) + 1 )

/*
** Macro to check whether a key tree node with location x is the
** ancestor of another key tree node with location y. x is an ancestor
** of y means x and y are at the same branch from the root and x is
** located closer to the root than y does.
*/
#define IsAncestor( x, y )  ( SBM( x ) >= SBM( y ) && ( y  & LP( x ) ) == ( x & LP( x ) ) )

/*
** The maximum depth of the stack that is used to store the intermediate keys
** during derivation. It should be the maximum depth of any subtree in the
** whole key tree.
*/
#define MAX_KEY_STACK   20

/*
** Implementation of function which determines whether the given location
** exists in an aux key entry array.
** If so, it sets the out parameter to the index and returns DRM_SUCCESS.
** If not, it returns the DRM_RESULT specified in the macro as __drToReturn.
**
** The macro assumes that it is being used in the following way:
**
** DRM_RESULT _MyFunc(
**     __in                                DRM_DWORD                      f_dwLocation,
**     __in                          const DRM_DWORD                      f_cAuxKeys,
**     __in_ecount_opt( f_cAuxKeys ) const DRM_XMRFORMAT_AUX_KEY_ENTRY   *f_prgAuxKeys,
**     __inout                             DRM_DWORD                     *f_pdwAuxKeyIndex )
** {
**     FIND_AUX_KEY_ENTRY_IMPL( ... );
** }
**
** The __drToReturn will typically be DRM_S_FALSE or DRM_E_UNABLE_TO_RESOLVE_LOCATION_TREE
*/
#define FIND_AUX_KEY_ENTRY_IMPL( __drToReturn )                                                     \
    DRM_RESULT dr    = DRM_SUCCESS;                                                                 \
                                                                                                    \
    DRMASSERT( f_pdwAuxKeyIndex != NULL );                                                          \
                                                                                                    \
    if( f_cAuxKeys        == 0                                                                      \
     || f_prgAuxKeys      == NULL                                                                   \
     || *f_pdwAuxKeyIndex >= f_cAuxKeys )                                                           \
    {                                                                                               \
        dr = __drToReturn;                                                                          \
    }                                                                                               \
    else                                                                                            \
    {                                                                                               \
        DRM_BOOL   fDone = FALSE;                                                                   \
        DRM_LONG   nLeft;               /* Initialized before usage below */                        \
        DRM_LONG   nRight;              /* Initialized before usage below */                        \
        DRM_LONG   nMiddle;             /* Initialized before usage below */                        \
        DRM_LONG   nStart;              /* Initialized before usage below */                        \
        DRM_DWORD  dwLocationToTry;     /* Initialized before usage below */                        \
                                                                                                    \
        nStart = nLeft = (DRM_LONG)*f_pdwAuxKeyIndex;                                               \
                                                                                                    \
        /* Can't underflow because we get here only if f_cAuxKeys != 0 */                           \
        nRight = (DRM_LONG)( f_cAuxKeys - 1 );                                                      \
                                                                                                    \
        while( !fDone )                                                                             \
        {                                                                                           \
            nMiddle = ( nLeft + nRight ) / 2;                                                       \
                                                                                                    \
            NETWORKBYTES_TO_DWORD( dwLocationToTry, &f_prgAuxKeys[ nMiddle ].dwLocation, 0 );       \
            if( IsAncestor( dwLocationToTry, f_dwLocation ) )                                       \
            {                                                                                       \
                *f_pdwAuxKeyIndex = (DRM_DWORD)nMiddle;                                             \
                fDone = TRUE;   /* Found the index */                                               \
            }                                                                                       \
            else                                                                                    \
            {                                                                                       \
                if( dwLocationToTry > f_dwLocation )                                                \
                {                                                                                   \
                    nRight = nMiddle - 1;                                                           \
                }                                                                                   \
                else                                                                                \
                {                                                                                   \
                    nLeft = nMiddle + 1;                                                            \
                }                                                                                   \
                                                                                                    \
                if( nLeft  >= (DRM_LONG)f_cAuxKeys                                                  \
                 || nRight <  nStart                                                                \
                 || nLeft  >  nRight )                                                              \
                {                                                                                   \
                    dr = __drToReturn;                                                              \
                    fDone = TRUE;   /* Index not found */                                           \
                }                                                                                   \
            }                                                                                       \
        }                                                                                           \
    }                                                                                               \
                                                                                                    \
    return dr;

EXIT_PK_NAMESPACE;

#endif /* __DRMDERIVEDKEY_H__ */


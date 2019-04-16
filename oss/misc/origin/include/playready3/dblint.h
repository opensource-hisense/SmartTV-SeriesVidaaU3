/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef DBLINT_H
#define DBLINT_H 1

#include <drmtypes.h>

#if defined(_M_IX86) || defined(_M_AMD64)

#ifdef __cplusplus
extern "C"
#endif
unsigned __int64 __emulu(
   unsigned int a,
   unsigned int b
);

#pragma intrinsic(__emulu)

#endif

ENTER_PK_NAMESPACE;

/*
        File: dblint.h.  Supplement to bignum.h.  Version 10 December, 2002.

        This file has declarations related to double-precision integers,
        such as typedefs, constants, and primitive operations.

        The DRM_UINT64 type is unsigned and holds twice as many bits
        as a digit_t datum.  If (DRM_SUPPORT_NATIVE_64BIT_TYPES = 1), then use the type
        already in the language.  Otherwise (DRM_SUPPORT_NATIVE_64BIT_TYPES = 0)
        construct one of our own, using a struct with two digit_t fields.

        Let u, u1, u2 have type digit_t and
        d, d1, d2 have type DRM_UINT64.
        The following primitives are defined,
        whether we use the built-in type or our own type:

                DPRODUU(u1, u2) -- Product of u1 and u2, as a DRM_UINT64.
                HPRODUU(u1, u2) -- Most significant half of product
                                   of u1 and u2, as a digit_t.
*/

#if DRM_SUPPORT_NATIVE_64BIT_TYPES

#if defined (DRM_MSC_VER)
#if DRM_INLINING_SUPPORTED

/*
    Note: it seems that for Arm platform this should be moved to just (DWORD)u1*(DWORD)u2.
            DRM_UI64(u1) * DRM_UI64(u2) on x86&x64 produces a [slow]  __allmul call.
            which can be very miserable for mod_exp and other functions which use lots of this.
*/
static DRM_ALWAYS_INLINE DRM_UINT64 DRM_CALL DPRODUU(const digit_t u1, const digit_t u2)
{
#if defined(_M_IX86) || defined(_M_AMD64)
    return __emulu(u1, u2);
#else
    return DRM_UI64(u1) * DRM_UI64(u2);
#endif

}
#else /* DRM_INLINING_SUPPORTED */
#define DPRODUU(u1, u2) (DRM_UI64(u1) * DRM_UI64(u2))
#endif /* DRM_INLINING_SUPPORTED */

#else /* DRM_MSC_VER */

#define DPRODUU(u1, u2) (DRM_UI64(u1) * DRM_UI64(u2))

#endif /* DRM_MSC_VER */

#define MULTIPLY_ADD1(d1, d2, d3) \
        DRM_UI64Add(DRM_UI64(d3), DPRODUU(d1, d2))
           /* d1*d2 + d3 */

#define MULTIPLY_ADD2(d1, d2, d3, d4) \
        DRM_UI64Add(DPRODUU(d1, d2), DRM_UI64Add(DRM_UI64(d4), DRM_UI64(d3)))
          /* d1*d2 + d3 + d4 */

#define HPRODUU(u1, u2) DRM_UI64High32(DRM_UI64Mul(DRM_UI64((u1)), DRM_UI64((u2))))

#else  /* DRM_SUPPORT_NATIVE_64BIT_TYPES */

/* No native support for 64-bit types */

#if defined( _M_AMD64_ )
    #pragma intrinsic(__umulh)
    #define HPRODUU(u1, u2) __umulh(u1, u2)
#else
    #define HPRODUU(u1, u2) DRM_UI64High32(DRM_UI64Mul(DRM_UI64((u1)), DRM_UI64((u2))))
#endif

#if !DRM_INLINING_SUPPORTED

DRM_API DRM_UINT64 DRM_CALL DPRODUU(const digit_t, const digit_t);
DRM_API DRM_UINT64 DRM_CALL MULTIPLY_ADD1(const digit_t, const digit_t, const digit_t);
DRM_API DRM_UINT64 DRM_CALL MULTIPLY_ADD2(const digit_t, const digit_t,
                                            const digit_t, const digit_t);


#else /* !DRM_INLINING_SUPPORTED */

#if DRM_SUPPORT_NATIVE_64BIT_TYPES
#define ADDSame64_32( p64, v32 ) \
    *p64 += v32;

#else
#define ADDSame64_32( p64, v32 )    \
    (p64)->val[0] += v32;            \
    (p64)->val[1] += (p64)->val[0] < v32;

#endif

DRM_ALWAYS_INLINE DRM_UINT64 DRM_CALL DPRODUU(const digit_t u1, const digit_t u2) DRM_ALWAYS_INLINE_ATTRIBUTE;
DRM_ALWAYS_INLINE DRM_UINT64 DRM_CALL DPRODUU(const digit_t u1, const digit_t u2)
/*
        Multiply two single-precision operands,
        return double precision product.
        This will normally be replaced by an assembly language routine.
        unless the top half of the product (HPRODUU) is available in C.
*/
{
    DRM_UINT64 t;
    DRM_WORD u1h = (DRM_WORD)( u1 >> 16 );
    DRM_WORD u2h = (DRM_WORD)( u2 >> 16 );
    DRM_WORD u1l = (DRM_WORD)u1;
    DRM_WORD u2l = (DRM_WORD)u2;
    digit_t t2 = (digit_t)u1h * u2l;
    digit_t t3 = (digit_t)u1l * u2h;
    digit_t t23l = ( t2 & 0xffff ) + ( t3 & 0xffff );
    digit_t t23h = ( t2 >> 16 ) + ( t3 >> 16 );
    digit_t a = t23l << 16;
    digit_t u12l = (digit_t) u1l * u2l + a;

#if DRM_SUPPORT_NATIVE_64BIT_TYPES
    t = DRM_UI64HL(
          (digit_t)u1h * u2h
        + t23h
        + (t23l>>16)
        + (a > u12l), u12l);
#else
    t.val[0] = u12l;
    t.val[1] =
          (digit_t)u1h * u2h
        + t23h
        + ( t23l >> 16 )
        + ( a > u12l );
#endif
    return t;
}   /* end DPRODUU */

/*
    The MULTIPLY_ADD1. MULTIPLY_ADD2
    functions take single-length (digit_t) operands and
    return double-length (DRM_UINT64) results.
    Overflow is impossible.
*/
DRM_ALWAYS_INLINE DRM_UINT64 DRM_CALL MULTIPLY_ADD1(const digit_t d1, const digit_t d2, const digit_t d3) DRM_ALWAYS_INLINE_ATTRIBUTE;
DRM_ALWAYS_INLINE DRM_UINT64 DRM_CALL MULTIPLY_ADD1(const digit_t d1, const digit_t d2, const digit_t d3)
{
    DRM_UINT64 t = DPRODUU(d1,d2);
    ADDSame64_32(&t, d3);
    return t;
} /* MULTIPLY_ADD1 */


DRM_ALWAYS_INLINE DRM_UINT64 DRM_CALL MULTIPLY_ADD2(const digit_t d1, const digit_t d2, const digit_t d3, const digit_t d4) DRM_ALWAYS_INLINE_ATTRIBUTE;
DRM_ALWAYS_INLINE DRM_UINT64 DRM_CALL MULTIPLY_ADD2(const digit_t d1, const digit_t d2, const digit_t d3, const digit_t d4)
{
    DRM_UINT64 t = DPRODUU(d1,d2);
    ADDSame64_32(&t, d3);
    ADDSame64_32(&t, d4);
    return t;
} /* MULTIPLY_ADD2 */

#endif /* !DRM_INLINING_SUPPORTED */

#endif /* DRM_SUPPORT_NATIVE_64BIT_TYPES */

EXIT_PK_NAMESPACE;

#endif /* DBLINT_H */


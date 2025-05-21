
#ifndef _BASE_H
#define _BASE_H

#define _WHERE_ __FILE__,__LINE__

/* ASSERT */
#ifdef NOOS
#define ASSERT(a)
#else
// #include <stdio.h>
void urks(void);
#define ASSERT(a) if (!(a)) {urks();fprints("Assertion failed at %d in %s\n",__LINE__,__FILE__); exit(1);}
#endif


#define EQ    ==
#define NE    !=
#define GE    >=
#define GT    >
#define LE    <=
#define LT    <
#define NOT   !
#define AND   &&
#define OR    ||
#define BAND  &
#define BOR   |
#define BNOT  ~
#define XOR   ^

/*  min, max is not defined in stdlib.h !!! */
#ifndef max
#define max(a,b)  ((a) LT (b)) ? (b) : (a)
#endif
#ifndef min
#define min(a,b)  ((a) GT (b)) ? (b) : (a)
#endif
#ifndef between
#define between(a,b,c)  ((a) LE (b)) AND ((b) LE (c))
#endif


#define SETBIT(p,b) ((p)|=(b))
#define CLRBIT(p,b) ((p)&= ~(b))
#define TSTBIT(p,b) ((p)&(b))
#define TGLBIT(p,b) ((p)^=(b))
#define MASK(p, b) ((p) & ~(b))

#define Void    void
#define LOCAL   static
#define GLOBAL
#define EXTERN  extern

/* primitive types */
typedef int             Int;
typedef unsigned int    UInt;
typedef long            Long;
typedef unsigned long   ULong;
typedef short           Short;
typedef unsigned short  UShort;
typedef char            Char;
typedef char *          String;
typedef unsigned char   UChar;
typedef double          Double;
typedef float           Float;

/* primitive types for kevin */
typedef signed char     i8;
typedef unsigned char   u8;

typedef int             i16;
typedef unsigned int    u16;

typedef long            i32;
typedef unsigned long   u32;

typedef float           f32;
typedef double          f64;



#ifdef Bool /* Bool is defined in <X11/Xlib.h> */
#undef Bool
#endif

#ifndef Bool
typedef int Bool;
#endif

#ifndef FALSE
#define FALSE 0
#endif
#ifndef TRUE
#define TRUE  (!FALSE)
#endif

#ifndef NULL
#define NULL 0
#endif

#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)  \
  ((byte) & 0x80 ? '1' : '.'), \
  ((byte) & 0x40 ? '1' : '.'), \
  ((byte) & 0x20 ? '1' : '.'), \
  ((byte) & 0x10 ? '1' : '.'), \
  ((byte) & 0x08 ? '1' : '.'), \
  ((byte) & 0x04 ? '1' : '.'), \
  ((byte) & 0x02 ? '1' : '.'), \
  ((byte) & 0x01 ? '1' : '.') 

#endif

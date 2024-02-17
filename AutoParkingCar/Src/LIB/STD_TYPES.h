
#ifndef LIB_STD_Type_H_
#define LIB_STD_Type_H_

#define STD_NULL ((void*)0)
#define NULL_PTR ((void*)0)

typedef unsigned char             u8;
typedef signed char               s8;
typedef signed short int          s16;
typedef unsigned short int        u16;
typedef signed long int           s32;
typedef unsigned long int         u32;
typedef float                     f32;
typedef double                    f64;
typedef long double               f128;

#ifndef FALSE
#define FALSE       (0u)
#endif
#ifndef TRUE
#define TRUE        (1u)
#endif
#ifndef STD_HIGH
#define STD_HIGH    (0u)
#endif
#ifndef STD_LOW
#define STD_LOW     (1u)
#endif
#ifndef STD_ON
#define STD_ON      (1u)
#endif
#ifndef STD_OFF
#define STD_OFF     (0u)
#endif

#endif

# 1 "../../include/FreeRTOS_Sockets.h"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 1 "<command-line>" 2
# 1 "../../include/FreeRTOS_Sockets.h"
# 30 "../../include/FreeRTOS_Sockets.h"
        extern "C" {



# 1 "/usr/include/string.h" 1 3 4
# 26 "/usr/include/string.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/libc-header-start.h" 1 3 4
# 33 "/usr/include/x86_64-linux-gnu/bits/libc-header-start.h" 3 4
# 1 "/usr/include/features.h" 1 3 4
# 424 "/usr/include/features.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 1 3 4
# 427 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/wordsize.h" 1 3 4
# 428 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 2 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/long-double.h" 1 3 4
# 429 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 2 3 4
# 425 "/usr/include/features.h" 2 3 4
# 448 "/usr/include/features.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/gnu/stubs.h" 1 3 4
# 10 "/usr/include/x86_64-linux-gnu/gnu/stubs.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/gnu/stubs-64.h" 1 3 4
# 11 "/usr/include/x86_64-linux-gnu/gnu/stubs.h" 2 3 4
# 449 "/usr/include/features.h" 2 3 4
# 34 "/usr/include/x86_64-linux-gnu/bits/libc-header-start.h" 2 3 4
# 27 "/usr/include/string.h" 2 3 4


# 28 "/usr/include/string.h" 3 4
extern "C" {




# 1 "/usr/lib/gcc/x86_64-linux-gnu/7/include/stddef.h" 1 3 4
# 216 "/usr/lib/gcc/x86_64-linux-gnu/7/include/stddef.h" 3 4
typedef long unsigned int size_t;
# 34 "/usr/include/string.h" 2 3 4
# 42 "/usr/include/string.h" 3 4
extern void *memcpy (void *__restrict __dest, const void *__restrict __src,
       size_t __n) throw () __attribute__ ((__nonnull__ (1, 2)));


extern void *memmove (void *__dest, const void *__src, size_t __n)
     throw () __attribute__ ((__nonnull__ (1, 2)));





extern void *memccpy (void *__restrict __dest, const void *__restrict __src,
        int __c, size_t __n)
     throw () __attribute__ ((__nonnull__ (1, 2)));




extern void *memset (void *__s, int __c, size_t __n) throw () __attribute__ ((__nonnull__ (1)));


extern int memcmp (const void *__s1, const void *__s2, size_t __n)
     throw () __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));



extern "C++"
{
extern void *memchr (void *__s, int __c, size_t __n)
      throw () __asm ("memchr") __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));
extern const void *memchr (const void *__s, int __c, size_t __n)
      throw () __asm ("memchr") __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));
# 88 "/usr/include/string.h" 3 4
}
# 98 "/usr/include/string.h" 3 4
extern "C++" void *rawmemchr (void *__s, int __c)
     throw () __asm ("rawmemchr") __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));
extern "C++" const void *rawmemchr (const void *__s, int __c)
     throw () __asm ("rawmemchr") __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));







extern "C++" void *memrchr (void *__s, int __c, size_t __n)
      throw () __asm ("memrchr") __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));
extern "C++" const void *memrchr (const void *__s, int __c, size_t __n)
      throw () __asm ("memrchr") __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));
# 121 "/usr/include/string.h" 3 4
extern char *strcpy (char *__restrict __dest, const char *__restrict __src)
     throw () __attribute__ ((__nonnull__ (1, 2)));

extern char *strncpy (char *__restrict __dest,
        const char *__restrict __src, size_t __n)
     throw () __attribute__ ((__nonnull__ (1, 2)));


extern char *strcat (char *__restrict __dest, const char *__restrict __src)
     throw () __attribute__ ((__nonnull__ (1, 2)));

extern char *strncat (char *__restrict __dest, const char *__restrict __src,
        size_t __n) throw () __attribute__ ((__nonnull__ (1, 2)));


extern int strcmp (const char *__s1, const char *__s2)
     throw () __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));

extern int strncmp (const char *__s1, const char *__s2, size_t __n)
     throw () __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));


extern int strcoll (const char *__s1, const char *__s2)
     throw () __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));

extern size_t strxfrm (char *__restrict __dest,
         const char *__restrict __src, size_t __n)
     throw () __attribute__ ((__nonnull__ (2)));



# 1 "/usr/include/x86_64-linux-gnu/bits/types/locale_t.h" 1 3 4
# 22 "/usr/include/x86_64-linux-gnu/bits/types/locale_t.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/types/__locale_t.h" 1 3 4
# 28 "/usr/include/x86_64-linux-gnu/bits/types/__locale_t.h" 3 4
struct __locale_struct
{

  struct __locale_data *__locales[13];


  const unsigned short int *__ctype_b;
  const int *__ctype_tolower;
  const int *__ctype_toupper;


  const char *__names[13];
};

typedef struct __locale_struct *__locale_t;
# 23 "/usr/include/x86_64-linux-gnu/bits/types/locale_t.h" 2 3 4

typedef __locale_t locale_t;
# 153 "/usr/include/string.h" 2 3 4


extern int strcoll_l (const char *__s1, const char *__s2, locale_t __l)
     throw () __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2, 3)));


extern size_t strxfrm_l (char *__dest, const char *__src, size_t __n,
    locale_t __l) throw () __attribute__ ((__nonnull__ (2, 4)));





extern char *strdup (const char *__s)
     throw () __attribute__ ((__malloc__)) __attribute__ ((__nonnull__ (1)));






extern char *strndup (const char *__string, size_t __n)
     throw () __attribute__ ((__malloc__)) __attribute__ ((__nonnull__ (1)));
# 203 "/usr/include/string.h" 3 4
extern "C++"
{
extern char *strchr (char *__s, int __c)
     throw () __asm ("strchr") __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));
extern const char *strchr (const char *__s, int __c)
     throw () __asm ("strchr") __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));
# 223 "/usr/include/string.h" 3 4
}






extern "C++"
{
extern char *strrchr (char *__s, int __c)
     throw () __asm ("strrchr") __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));
extern const char *strrchr (const char *__s, int __c)
     throw () __asm ("strrchr") __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));
# 250 "/usr/include/string.h" 3 4
}
# 260 "/usr/include/string.h" 3 4
extern "C++" char *strchrnul (char *__s, int __c)
     throw () __asm ("strchrnul") __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));
extern "C++" const char *strchrnul (const char *__s, int __c)
     throw () __asm ("strchrnul") __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));
# 272 "/usr/include/string.h" 3 4
extern size_t strcspn (const char *__s, const char *__reject)
     throw () __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));


extern size_t strspn (const char *__s, const char *__accept)
     throw () __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));


extern "C++"
{
extern char *strpbrk (char *__s, const char *__accept)
     throw () __asm ("strpbrk") __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
extern const char *strpbrk (const char *__s, const char *__accept)
     throw () __asm ("strpbrk") __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
# 300 "/usr/include/string.h" 3 4
}






extern "C++"
{
extern char *strstr (char *__haystack, const char *__needle)
     throw () __asm ("strstr") __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
extern const char *strstr (const char *__haystack, const char *__needle)
     throw () __asm ("strstr") __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
# 327 "/usr/include/string.h" 3 4
}







extern char *strtok (char *__restrict __s, const char *__restrict __delim)
     throw () __attribute__ ((__nonnull__ (2)));



extern char *__strtok_r (char *__restrict __s,
    const char *__restrict __delim,
    char **__restrict __save_ptr)
     throw () __attribute__ ((__nonnull__ (2, 3)));

extern char *strtok_r (char *__restrict __s, const char *__restrict __delim,
         char **__restrict __save_ptr)
     throw () __attribute__ ((__nonnull__ (2, 3)));





extern "C++" char *strcasestr (char *__haystack, const char *__needle)
     throw () __asm ("strcasestr") __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
extern "C++" const char *strcasestr (const char *__haystack,
         const char *__needle)
     throw () __asm ("strcasestr") __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
# 368 "/usr/include/string.h" 3 4
extern void *memmem (const void *__haystack, size_t __haystacklen,
       const void *__needle, size_t __needlelen)
     throw () __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 3)));



extern void *__mempcpy (void *__restrict __dest,
   const void *__restrict __src, size_t __n)
     throw () __attribute__ ((__nonnull__ (1, 2)));
extern void *mempcpy (void *__restrict __dest,
        const void *__restrict __src, size_t __n)
     throw () __attribute__ ((__nonnull__ (1, 2)));




extern size_t strlen (const char *__s)
     throw () __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));




extern size_t strnlen (const char *__string, size_t __maxlen)
     throw () __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));




extern char *strerror (int __errnum) throw ();
# 420 "/usr/include/string.h" 3 4
extern char *strerror_r (int __errnum, char *__buf, size_t __buflen)
     throw () __attribute__ ((__nonnull__ (2))) ;





extern char *strerror_l (int __errnum, locale_t __l) throw ();



# 1 "/usr/include/strings.h" 1 3 4
# 23 "/usr/include/strings.h" 3 4
# 1 "/usr/lib/gcc/x86_64-linux-gnu/7/include/stddef.h" 1 3 4
# 24 "/usr/include/strings.h" 2 3 4






extern "C" {



extern int bcmp (const void *__s1, const void *__s2, size_t __n)
     throw () __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));


extern void bcopy (const void *__src, void *__dest, size_t __n)
  throw () __attribute__ ((__nonnull__ (1, 2)));


extern void bzero (void *__s, size_t __n) throw () __attribute__ ((__nonnull__ (1)));



extern "C++"
{
extern char *index (char *__s, int __c)
     throw () __asm ("index") __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));
extern const char *index (const char *__s, int __c)
     throw () __asm ("index") __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));
# 66 "/usr/include/strings.h" 3 4
}







extern "C++"
{
extern char *rindex (char *__s, int __c)
     throw () __asm ("rindex") __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));
extern const char *rindex (const char *__s, int __c)
     throw () __asm ("rindex") __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));
# 94 "/usr/include/strings.h" 3 4
}
# 104 "/usr/include/strings.h" 3 4
extern int ffs (int __i) throw () __attribute__ ((__const__));





extern int ffsl (long int __l) throw () __attribute__ ((__const__));
__extension__ extern int ffsll (long long int __ll)
     throw () __attribute__ ((__const__));



extern int strcasecmp (const char *__s1, const char *__s2)
     throw () __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));


extern int strncasecmp (const char *__s1, const char *__s2, size_t __n)
     throw () __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));






extern int strcasecmp_l (const char *__s1, const char *__s2, locale_t __loc)
     throw () __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2, 3)));



extern int strncasecmp_l (const char *__s1, const char *__s2,
     size_t __n, locale_t __loc)
     throw () __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2, 4)));


}
# 432 "/usr/include/string.h" 2 3 4



extern void explicit_bzero (void *__s, size_t __n) throw () __attribute__ ((__nonnull__ (1)));



extern char *strsep (char **__restrict __stringp,
       const char *__restrict __delim)
     throw () __attribute__ ((__nonnull__ (1, 2)));




extern char *strsignal (int __sig) throw ();


extern char *__stpcpy (char *__restrict __dest, const char *__restrict __src)
     throw () __attribute__ ((__nonnull__ (1, 2)));
extern char *stpcpy (char *__restrict __dest, const char *__restrict __src)
     throw () __attribute__ ((__nonnull__ (1, 2)));



extern char *__stpncpy (char *__restrict __dest,
   const char *__restrict __src, size_t __n)
     throw () __attribute__ ((__nonnull__ (1, 2)));
extern char *stpncpy (char *__restrict __dest,
        const char *__restrict __src, size_t __n)
     throw () __attribute__ ((__nonnull__ (1, 2)));




extern int strverscmp (const char *__s1, const char *__s2)
     throw () __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));


extern char *strfry (char *__string) throw () __attribute__ ((__nonnull__ (1)));


extern void *memfrob (void *__s, size_t __n) throw () __attribute__ ((__nonnull__ (1)));







extern "C++" char *basename (char *__filename)
     throw () __asm ("basename") __attribute__ ((__nonnull__ (1)));
extern "C++" const char *basename (const char *__filename)
     throw () __asm ("basename") __attribute__ ((__nonnull__ (1)));
# 498 "/usr/include/string.h" 3 4
}
# 35 "../../include/FreeRTOS_Sockets.h" 2

# 1 "../FreeRTOS-Kernel/include/FreeRTOS.h" 1
# 33 "../FreeRTOS-Kernel/include/FreeRTOS.h"
# 1 "/usr/lib/gcc/x86_64-linux-gnu/7/include/stddef.h" 1 3 4
# 149 "/usr/lib/gcc/x86_64-linux-gnu/7/include/stddef.h" 3 4
typedef long int ptrdiff_t;
# 426 "/usr/lib/gcc/x86_64-linux-gnu/7/include/stddef.h" 3 4
typedef struct {
  long long __max_align_ll __attribute__((__aligned__(__alignof__(long long))));
  long double __max_align_ld __attribute__((__aligned__(__alignof__(long double))));
# 437 "/usr/lib/gcc/x86_64-linux-gnu/7/include/stddef.h" 3 4
} max_align_t;






  typedef decltype(nullptr) nullptr_t;
# 34 "../FreeRTOS-Kernel/include/FreeRTOS.h" 2
# 48 "../FreeRTOS-Kernel/include/FreeRTOS.h"
# 1 "/usr/lib/gcc/x86_64-linux-gnu/7/include/stdint.h" 1 3 4
# 9 "/usr/lib/gcc/x86_64-linux-gnu/7/include/stdint.h" 3 4
# 1 "/usr/include/stdint.h" 1 3 4
# 26 "/usr/include/stdint.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/libc-header-start.h" 1 3 4
# 27 "/usr/include/stdint.h" 2 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/types.h" 1 3 4
# 27 "/usr/include/x86_64-linux-gnu/bits/types.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/wordsize.h" 1 3 4
# 28 "/usr/include/x86_64-linux-gnu/bits/types.h" 2 3 4


typedef unsigned char __u_char;
typedef unsigned short int __u_short;
typedef unsigned int __u_int;
typedef unsigned long int __u_long;


typedef signed char __int8_t;
typedef unsigned char __uint8_t;
typedef signed short int __int16_t;
typedef unsigned short int __uint16_t;
typedef signed int __int32_t;
typedef unsigned int __uint32_t;

typedef signed long int __int64_t;
typedef unsigned long int __uint64_t;







typedef long int __quad_t;
typedef unsigned long int __u_quad_t;







typedef long int __intmax_t;
typedef unsigned long int __uintmax_t;
# 130 "/usr/include/x86_64-linux-gnu/bits/types.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/typesizes.h" 1 3 4
# 131 "/usr/include/x86_64-linux-gnu/bits/types.h" 2 3 4


typedef unsigned long int __dev_t;
typedef unsigned int __uid_t;
typedef unsigned int __gid_t;
typedef unsigned long int __ino_t;
typedef unsigned long int __ino64_t;
typedef unsigned int __mode_t;
typedef unsigned long int __nlink_t;
typedef long int __off_t;
typedef long int __off64_t;
typedef int __pid_t;
typedef struct { int __val[2]; } __fsid_t;
typedef long int __clock_t;
typedef unsigned long int __rlim_t;
typedef unsigned long int __rlim64_t;
typedef unsigned int __id_t;
typedef long int __time_t;
typedef unsigned int __useconds_t;
typedef long int __suseconds_t;

typedef int __daddr_t;
typedef int __key_t;


typedef int __clockid_t;


typedef void * __timer_t;


typedef long int __blksize_t;




typedef long int __blkcnt_t;
typedef long int __blkcnt64_t;


typedef unsigned long int __fsblkcnt_t;
typedef unsigned long int __fsblkcnt64_t;


typedef unsigned long int __fsfilcnt_t;
typedef unsigned long int __fsfilcnt64_t;


typedef long int __fsword_t;

typedef long int __ssize_t;


typedef long int __syscall_slong_t;

typedef unsigned long int __syscall_ulong_t;



typedef __off64_t __loff_t;
typedef char *__caddr_t;


typedef long int __intptr_t;


typedef unsigned int __socklen_t;




typedef int __sig_atomic_t;
# 28 "/usr/include/stdint.h" 2 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/wchar.h" 1 3 4
# 29 "/usr/include/stdint.h" 2 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/wordsize.h" 1 3 4
# 30 "/usr/include/stdint.h" 2 3 4




# 1 "/usr/include/x86_64-linux-gnu/bits/stdint-intn.h" 1 3 4
# 24 "/usr/include/x86_64-linux-gnu/bits/stdint-intn.h" 3 4
typedef __int8_t int8_t;
typedef __int16_t int16_t;
typedef __int32_t int32_t;
typedef __int64_t int64_t;
# 35 "/usr/include/stdint.h" 2 3 4


# 1 "/usr/include/x86_64-linux-gnu/bits/stdint-uintn.h" 1 3 4
# 24 "/usr/include/x86_64-linux-gnu/bits/stdint-uintn.h" 3 4
typedef __uint8_t uint8_t;
typedef __uint16_t uint16_t;
typedef __uint32_t uint32_t;
typedef __uint64_t uint64_t;
# 38 "/usr/include/stdint.h" 2 3 4





typedef signed char int_least8_t;
typedef short int int_least16_t;
typedef int int_least32_t;

typedef long int int_least64_t;






typedef unsigned char uint_least8_t;
typedef unsigned short int uint_least16_t;
typedef unsigned int uint_least32_t;

typedef unsigned long int uint_least64_t;
# 68 "/usr/include/stdint.h" 3 4
typedef signed char int_fast8_t;

typedef long int int_fast16_t;
typedef long int int_fast32_t;
typedef long int int_fast64_t;
# 81 "/usr/include/stdint.h" 3 4
typedef unsigned char uint_fast8_t;

typedef unsigned long int uint_fast16_t;
typedef unsigned long int uint_fast32_t;
typedef unsigned long int uint_fast64_t;
# 97 "/usr/include/stdint.h" 3 4
typedef long int intptr_t;


typedef unsigned long int uintptr_t;
# 111 "/usr/include/stdint.h" 3 4
typedef __intmax_t intmax_t;
typedef __uintmax_t uintmax_t;
# 10 "/usr/lib/gcc/x86_64-linux-gnu/7/include/stdint.h" 2 3 4
# 49 "../FreeRTOS-Kernel/include/FreeRTOS.h" 2



    
# 52 "../FreeRTOS-Kernel/include/FreeRTOS.h"
   extern "C" {




# 1 "ConfigFiles/FreeRTOSConfig.h" 1
# 32 "ConfigFiles/FreeRTOSConfig.h"
# 1 "/usr/include/assert.h" 1 3 4
# 66 "/usr/include/assert.h" 3 4

# 66 "/usr/include/assert.h" 3 4
extern "C" {


extern void __assert_fail (const char *__assertion, const char *__file,
      unsigned int __line, const char *__function)
     throw () __attribute__ ((__noreturn__));


extern void __assert_perror_fail (int __errnum, const char *__file,
      unsigned int __line, const char *__function)
     throw () __attribute__ ((__noreturn__));




extern void __assert (const char *__assertion, const char *__file, int __line)
     throw () __attribute__ ((__noreturn__));


}
# 33 "ConfigFiles/FreeRTOSConfig.h" 2
# 80 "ConfigFiles/FreeRTOSConfig.h"

# 80 "ConfigFiles/FreeRTOSConfig.h"
unsigned long ulGetRunTimeCounterValue( void );
void vConfigureTimerForRunTimeStats( void );
# 118 "ConfigFiles/FreeRTOSConfig.h"
extern void vAssertCalled( unsigned long ulLine,
                           const char * const pcFileName );
# 58 "../FreeRTOS-Kernel/include/FreeRTOS.h" 2


# 1 "../FreeRTOS-Kernel/include/projdefs.h" 1
# 34 "../FreeRTOS-Kernel/include/projdefs.h"
typedef void (* TaskFunction_t)( void * );
# 61 "../FreeRTOS-Kernel/include/FreeRTOS.h" 2


# 1 "../FreeRTOS-Kernel/include/portable.h" 1
# 44 "../FreeRTOS-Kernel/include/portable.h"
# 1 "../FreeRTOS-Kernel/include/deprecated_definitions.h" 1
# 45 "../FreeRTOS-Kernel/include/portable.h" 2






# 1 "ConfigFiles/portmacro.h" 1
# 31 "ConfigFiles/portmacro.h"
# 1 "ConfigFiles/Windows.h" 1
# 32 "ConfigFiles/portmacro.h" 2
# 1 "ConfigFiles/WinBase.h" 1
# 33 "ConfigFiles/portmacro.h" 2
# 47 "ConfigFiles/portmacro.h"
typedef size_t StackType_t;
typedef long BaseType_t;
typedef unsigned long UBaseType_t;






    typedef uint32_t TickType_t;
# 78 "ConfigFiles/portmacro.h"
extern volatile BaseType_t xInsideInterrupt;
# 87 "ConfigFiles/portmacro.h"
void vPortCloseRunningThread( void * pvTaskToDelete,
                              volatile BaseType_t * pxPendYield );
void vPortDeleteThread( void * pvThreadToDelete );






void vPortEnterCritical( void );
void vPortExitCritical( void );
# 150 "ConfigFiles/portmacro.h"
void vPortGenerateSimulatedInterrupt( uint32_t ulInterruptNumber );
# 161 "ConfigFiles/portmacro.h"
void vPortSetInterruptHandler( uint32_t ulInterruptNumber,
                               uint32_t ( * pvHandler )( void ) );
# 52 "../FreeRTOS-Kernel/include/portable.h" 2
# 96 "../FreeRTOS-Kernel/include/portable.h"
    extern "C" {



# 1 "../FreeRTOS-Kernel/include/mpu_wrappers.h" 1
# 101 "../FreeRTOS-Kernel/include/portable.h" 2
# 128 "../FreeRTOS-Kernel/include/portable.h"
        StackType_t * pxPortInitialiseStack( StackType_t * pxTopOfStack,
                                             TaskFunction_t pxCode,
                                             void * pvParameters ) ;





typedef struct HeapRegion
{
    uint8_t * pucStartAddress;
    size_t xSizeInBytes;
} HeapRegion_t;


typedef struct xHeapStats
{
    size_t xAvailableHeapSpaceInBytes;
    size_t xSizeOfLargestFreeBlockInBytes;
    size_t xSizeOfSmallestFreeBlockInBytes;
    size_t xNumberOfFreeBlocks;
    size_t xMinimumEverFreeBytesRemaining;
    size_t xNumberOfSuccessfulAllocations;
    size_t xNumberOfSuccessfulFrees;
} HeapStats_t;
# 165 "../FreeRTOS-Kernel/include/portable.h"
void vPortDefineHeapRegions( const HeapRegion_t * const pxHeapRegions ) ;





void vPortGetHeapStats( HeapStats_t * pxHeapStats );




void * pvPortMalloc( size_t xSize ) ;
void vPortFree( void * pv ) ;
void vPortInitialiseBlocks( void ) ;
size_t xPortGetFreeHeapSize( void ) ;
size_t xPortGetMinimumEverFreeHeapSize( void ) ;





BaseType_t xPortStartScheduler( void ) ;






void vPortEndScheduler( void ) ;
# 212 "../FreeRTOS-Kernel/include/portable.h"
    }
# 64 "../FreeRTOS-Kernel/include/FreeRTOS.h" 2
# 1113 "../FreeRTOS-Kernel/include/FreeRTOS.h"
struct xSTATIC_LIST_ITEM
{



    TickType_t xDummy2;
    void * pvDummy3[ 4 ];



};
typedef struct xSTATIC_LIST_ITEM StaticListItem_t;


struct xSTATIC_MINI_LIST_ITEM
{



    TickType_t xDummy2;
    void * pvDummy3[ 2 ];
};
typedef struct xSTATIC_MINI_LIST_ITEM StaticMiniListItem_t;


typedef struct xSTATIC_LIST
{



    UBaseType_t uxDummy2;
    void * pvDummy3;
    StaticMiniListItem_t xDummy4;



} StaticList_t;
# 1164 "../FreeRTOS-Kernel/include/FreeRTOS.h"
typedef struct xSTATIC_TCB
{
    void * pxDummy1;



    StaticListItem_t xDummy3[ 2 ];
    UBaseType_t uxDummy5;
    void * pxDummy6;
    uint8_t ucDummy7[ ( 12 ) ];







        UBaseType_t uxDummy10[ 2 ];


        UBaseType_t uxDummy12[ 2 ];


        void * pxDummy14;





        uint32_t ulDummy16;





        uint32_t ulDummy18[ 1 ];
        uint8_t ucDummy19[ 1 ];


        uint8_t uxDummy20;



        uint8_t ucDummy21;




} StaticTask_t;
# 1228 "../FreeRTOS-Kernel/include/FreeRTOS.h"
typedef struct xSTATIC_QUEUE
{
    void * pvDummy1[ 3 ];

    union
    {
        void * pvDummy2;
        UBaseType_t uxDummy2;
    } u;

    StaticList_t xDummy3[ 2 ];
    UBaseType_t uxDummy4[ 3 ];
    uint8_t ucDummy5[ 2 ];


        uint8_t ucDummy6;



        void * pvDummy7;



        UBaseType_t uxDummy8;
        uint8_t ucDummy9;

} StaticQueue_t;
typedef StaticQueue_t StaticSemaphore_t;
# 1271 "../FreeRTOS-Kernel/include/FreeRTOS.h"
typedef struct xSTATIC_EVENT_GROUP
{
    TickType_t xDummy1;
    StaticList_t xDummy2;


        UBaseType_t uxDummy3;



        uint8_t ucDummy4;

} StaticEventGroup_t;
# 1299 "../FreeRTOS-Kernel/include/FreeRTOS.h"
typedef struct xSTATIC_TIMER
{
    void * pvDummy1;
    StaticListItem_t xDummy2;
    TickType_t xDummy3;
    void * pvDummy5;
    TaskFunction_t pvDummy6;

        UBaseType_t uxDummy7;

    uint8_t ucDummy8;
} StaticTimer_t;
# 1326 "../FreeRTOS-Kernel/include/FreeRTOS.h"
typedef struct xSTATIC_STREAM_BUFFER
{
    size_t uxDummy1[ 4 ];
    void * pvDummy2[ 3 ];
    uint8_t ucDummy3;

        UBaseType_t uxDummy4;

} StaticStreamBuffer_t;


typedef StaticStreamBuffer_t StaticMessageBuffer_t;



    }
# 37 "../../include/FreeRTOS_Sockets.h" 2

# 1 "ConfigFiles/FreeRTOSIPConfig.h" 1
# 105 "ConfigFiles/FreeRTOSIPConfig.h"
extern uint32_t ulRand();
# 307 "ConfigFiles/FreeRTOSIPConfig.h"
void vApplicationMQTTGetKeys( const char ** ppcRootCA,
                              const char ** ppcClientCert,
                              const char ** ppcClientPrivateKey );
# 39 "../../include/FreeRTOS_Sockets.h" 2






# 1 "../FreeRTOS-Kernel/include/event_groups.h" 1
# 35 "../FreeRTOS-Kernel/include/event_groups.h"
# 1 "../FreeRTOS-Kernel/include/timers.h" 1
# 37 "../FreeRTOS-Kernel/include/timers.h"
# 1 "../FreeRTOS-Kernel/include/task.h" 1
# 35 "../FreeRTOS-Kernel/include/task.h"
# 1 "../FreeRTOS-Kernel/include/list.h" 1
# 97 "../FreeRTOS-Kernel/include/list.h"
    extern "C" {
# 141 "../FreeRTOS-Kernel/include/list.h"
struct xLIST;
struct xLIST_ITEM
{
   
    TickType_t xItemValue;
    struct xLIST_ITEM * pxNext;
    struct xLIST_ITEM * pxPrevious;
    void * pvOwner;
    struct xLIST * pvContainer;
   
};
typedef struct xLIST_ITEM ListItem_t;

struct xMINI_LIST_ITEM
{
   
    TickType_t xItemValue;
    struct xLIST_ITEM * pxNext;
    struct xLIST_ITEM * pxPrevious;
};
typedef struct xMINI_LIST_ITEM MiniListItem_t;




typedef struct xLIST
{
   
    volatile UBaseType_t uxNumberOfItems;
    ListItem_t * pxIndex;
    MiniListItem_t xListEnd;
   
} List_t;
# 347 "../FreeRTOS-Kernel/include/list.h"
void vListInitialise( List_t * const pxList ) ;
# 358 "../FreeRTOS-Kernel/include/list.h"
void vListInitialiseItem( ListItem_t * const pxItem ) ;
# 371 "../FreeRTOS-Kernel/include/list.h"
void vListInsert( List_t * const pxList,
                  ListItem_t * const pxNewListItem ) ;
# 393 "../FreeRTOS-Kernel/include/list.h"
void vListInsertEnd( List_t * const pxList,
                     ListItem_t * const pxNewListItem ) ;
# 409 "../FreeRTOS-Kernel/include/list.h"
UBaseType_t uxListRemove( ListItem_t * const pxItemToRemove ) ;



    }
# 36 "../FreeRTOS-Kernel/include/task.h" 2



    extern "C" {
# 77 "../FreeRTOS-Kernel/include/task.h"
struct tskTaskControlBlock;
typedef struct tskTaskControlBlock * TaskHandle_t;





typedef BaseType_t (* TaskHookFunction_t)( void * );


typedef enum
{
    eRunning = 0,
    eReady,
    eBlocked,
    eSuspended,
    eDeleted,
    eInvalid
} eTaskState;


typedef enum
{
    eNoAction = 0,
    eSetBits,
    eIncrement,
    eSetValueWithOverwrite,
    eSetValueWithoutOverwrite
} eNotifyAction;




typedef struct xTIME_OUT
{
    BaseType_t xOverflowCount;
    TickType_t xTimeOnEntering;
} TimeOut_t;




typedef struct xMEMORY_REGION
{
    void * pvBaseAddress;
    uint32_t ulLengthInBytes;
    uint32_t ulParameters;
} MemoryRegion_t;




typedef struct xTASK_PARAMETERS
{
    TaskFunction_t pvTaskCode;
    const char * pcName;
    uint16_t usStackDepth;
    void * pvParameters;
    UBaseType_t uxPriority;
    StackType_t * puxStackBuffer;
    MemoryRegion_t xRegions[ 1 ];



} TaskParameters_t;



typedef struct xTASK_STATUS
{
    TaskHandle_t xHandle;
    const char * pcTaskName;
    UBaseType_t xTaskNumber;
    eTaskState eCurrentState;
    UBaseType_t uxCurrentPriority;
    UBaseType_t uxBasePriority;
    uint32_t ulRunTimeCounter;
    StackType_t * pxStackBase;
    uint16_t usStackHighWaterMark;
} TaskStatus_t;


typedef enum
{
    eAbortSleep = 0,
    eStandardSleep,
    eNoTasksWaitingTimeout
} eSleepModeStatus;
# 340 "../FreeRTOS-Kernel/include/task.h"
    BaseType_t xTaskCreate( TaskFunction_t pxTaskCode,
                            const char * const pcName,
                            const uint16_t usStackDepth,
                            void * const pvParameters,
                            UBaseType_t uxPriority,
                            TaskHandle_t * const pxCreatedTask ) ;
# 457 "../FreeRTOS-Kernel/include/task.h"
    TaskHandle_t xTaskCreateStatic( TaskFunction_t pxTaskCode,
                                    const char * const pcName,
                                    const uint32_t ulStackDepth,
                                    void * const pvParameters,
                                    UBaseType_t uxPriority,
                                    StackType_t * const puxStackBuffer,
                                    StaticTask_t * const pxTaskBuffer ) ;
# 681 "../FreeRTOS-Kernel/include/task.h"
void vTaskAllocateMPURegions( TaskHandle_t xTask,
                              const MemoryRegion_t * const pxRegions ) ;
# 725 "../FreeRTOS-Kernel/include/task.h"
void vTaskDelete( TaskHandle_t xTaskToDelete ) ;
# 779 "../FreeRTOS-Kernel/include/task.h"
void vTaskDelay( const TickType_t xTicksToDelay ) ;
# 846 "../FreeRTOS-Kernel/include/task.h"
BaseType_t xTaskDelayUntil( TickType_t * const pxPreviousWakeTime,
                            const TickType_t xTimeIncrement ) ;
# 889 "../FreeRTOS-Kernel/include/task.h"
BaseType_t xTaskAbortDelay( TaskHandle_t xTask ) ;
# 938 "../FreeRTOS-Kernel/include/task.h"
UBaseType_t uxTaskPriorityGet( const TaskHandle_t xTask ) ;
# 948 "../FreeRTOS-Kernel/include/task.h"
UBaseType_t uxTaskPriorityGetFromISR( const TaskHandle_t xTask ) ;
# 968 "../FreeRTOS-Kernel/include/task.h"
eTaskState eTaskGetState( TaskHandle_t xTask ) ;
# 1026 "../FreeRTOS-Kernel/include/task.h"
void vTaskGetInfo( TaskHandle_t xTask,
                   TaskStatus_t * pxTaskStatus,
                   BaseType_t xGetFreeStackSpace,
                   eTaskState eState ) ;
# 1073 "../FreeRTOS-Kernel/include/task.h"
void vTaskPrioritySet( TaskHandle_t xTask,
                       UBaseType_t uxNewPriority ) ;
# 1127 "../FreeRTOS-Kernel/include/task.h"
void vTaskSuspend( TaskHandle_t xTaskToSuspend ) ;
# 1178 "../FreeRTOS-Kernel/include/task.h"
void vTaskResume( TaskHandle_t xTaskToResume ) ;
# 1209 "../FreeRTOS-Kernel/include/task.h"
BaseType_t xTaskResumeFromISR( TaskHandle_t xTaskToResume ) ;
# 1244 "../FreeRTOS-Kernel/include/task.h"
void vTaskStartScheduler( void ) ;
# 1302 "../FreeRTOS-Kernel/include/task.h"
void vTaskEndScheduler( void ) ;
# 1355 "../FreeRTOS-Kernel/include/task.h"
void vTaskSuspendAll( void ) ;
# 1411 "../FreeRTOS-Kernel/include/task.h"
BaseType_t xTaskResumeAll( void ) ;
# 1426 "../FreeRTOS-Kernel/include/task.h"
TickType_t xTaskGetTickCount( void ) ;
# 1442 "../FreeRTOS-Kernel/include/task.h"
TickType_t xTaskGetTickCountFromISR( void ) ;
# 1456 "../FreeRTOS-Kernel/include/task.h"
UBaseType_t uxTaskGetNumberOfTasks( void ) ;
# 1469 "../FreeRTOS-Kernel/include/task.h"
char * pcTaskGetName( TaskHandle_t xTaskToQuery ) ;
# 1485 "../FreeRTOS-Kernel/include/task.h"
TaskHandle_t xTaskGetHandle( const char * pcNameToQuery ) ;
# 1512 "../FreeRTOS-Kernel/include/task.h"
UBaseType_t uxTaskGetStackHighWaterMark( TaskHandle_t xTask ) ;
# 1539 "../FreeRTOS-Kernel/include/task.h"
uint16_t uxTaskGetStackHighWaterMark2( TaskHandle_t xTask ) ;
# 1560 "../FreeRTOS-Kernel/include/task.h"
        void vTaskSetApplicationTaskTag( TaskHandle_t xTask,
                                         TaskHookFunction_t pxHookFunction ) ;
# 1573 "../FreeRTOS-Kernel/include/task.h"
        TaskHookFunction_t xTaskGetApplicationTaskTag( TaskHandle_t xTask ) ;
# 1584 "../FreeRTOS-Kernel/include/task.h"
        TaskHookFunction_t xTaskGetApplicationTaskTagFromISR( TaskHandle_t xTask ) ;
# 1628 "../FreeRTOS-Kernel/include/task.h"
    void vApplicationTickHook( void );
# 1644 "../FreeRTOS-Kernel/include/task.h"
    void vApplicationGetIdleTaskMemory( StaticTask_t ** ppxIdleTaskTCBBuffer,
                                               StackType_t ** ppxIdleTaskStackBuffer,
                                               uint32_t * pulIdleTaskStackSize );
# 1662 "../FreeRTOS-Kernel/include/task.h"
BaseType_t xTaskCallApplicationTaskHook( TaskHandle_t xTask,
                                         void * pvParameter ) ;
# 1672 "../FreeRTOS-Kernel/include/task.h"
TaskHandle_t xTaskGetIdleTaskHandle( void ) ;
# 1771 "../FreeRTOS-Kernel/include/task.h"
UBaseType_t uxTaskGetSystemState( TaskStatus_t * const pxTaskStatusArray,
                                  const UBaseType_t uxArraySize,
                                  uint32_t * const pulTotalRunTime ) ;
# 1820 "../FreeRTOS-Kernel/include/task.h"
void vTaskList( char * pcWriteBuffer ) ;
# 1874 "../FreeRTOS-Kernel/include/task.h"
void vTaskGetRunTimeStats( char * pcWriteBuffer ) ;
# 1904 "../FreeRTOS-Kernel/include/task.h"
uint32_t ulTaskGetIdleRunTimeCounter( void ) ;
# 2013 "../FreeRTOS-Kernel/include/task.h"
BaseType_t xTaskGenericNotify( TaskHandle_t xTaskToNotify,
                               UBaseType_t uxIndexToNotify,
                               uint32_t ulValue,
                               eNotifyAction eAction,
                               uint32_t * pulPreviousNotificationValue ) ;
# 2161 "../FreeRTOS-Kernel/include/task.h"
BaseType_t xTaskGenericNotifyFromISR( TaskHandle_t xTaskToNotify,
                                      UBaseType_t uxIndexToNotify,
                                      uint32_t ulValue,
                                      eNotifyAction eAction,
                                      uint32_t * pulPreviousNotificationValue,
                                      BaseType_t * pxHigherPriorityTaskWoken ) ;
# 2303 "../FreeRTOS-Kernel/include/task.h"
BaseType_t xTaskGenericNotifyWait( UBaseType_t uxIndexToWaitOn,
                                   uint32_t ulBitsToClearOnEntry,
                                   uint32_t ulBitsToClearOnExit,
                                   uint32_t * pulNotificationValue,
                                   TickType_t xTicksToWait ) ;
# 2465 "../FreeRTOS-Kernel/include/task.h"
void vTaskGenericNotifyGiveFromISR( TaskHandle_t xTaskToNotify,
                                    UBaseType_t uxIndexToNotify,
                                    BaseType_t * pxHigherPriorityTaskWoken ) ;
# 2571 "../FreeRTOS-Kernel/include/task.h"
uint32_t ulTaskGenericNotifyTake( UBaseType_t uxIndexToWaitOn,
                                  BaseType_t xClearCountOnExit,
                                  TickType_t xTicksToWait ) ;
# 2636 "../FreeRTOS-Kernel/include/task.h"
BaseType_t xTaskGenericNotifyStateClear( TaskHandle_t xTask,
                                         UBaseType_t uxIndexToClear ) ;
# 2701 "../FreeRTOS-Kernel/include/task.h"
uint32_t ulTaskGenericNotifyValueClear( TaskHandle_t xTask,
                                        UBaseType_t uxIndexToClear,
                                        uint32_t ulBitsToClear ) ;
# 2723 "../FreeRTOS-Kernel/include/task.h"
void vTaskSetTimeOutState( TimeOut_t * const pxTimeOut ) ;
# 2808 "../FreeRTOS-Kernel/include/task.h"
BaseType_t xTaskCheckForTimeOut( TimeOut_t * const pxTimeOut,
                                 TickType_t * const pxTicksToWait ) ;
# 2837 "../FreeRTOS-Kernel/include/task.h"
BaseType_t xTaskCatchUpTicks( TickType_t xTicksToCatchUp ) ;
# 2859 "../FreeRTOS-Kernel/include/task.h"
BaseType_t xTaskIncrementTick( void ) ;
# 2892 "../FreeRTOS-Kernel/include/task.h"
void vTaskPlaceOnEventList( List_t * const pxEventList,
                            const TickType_t xTicksToWait ) ;
void vTaskPlaceOnUnorderedEventList( List_t * pxEventList,
                                     const TickType_t xItemValue,
                                     const TickType_t xTicksToWait ) ;
# 2909 "../FreeRTOS-Kernel/include/task.h"
void vTaskPlaceOnEventListRestricted( List_t * const pxEventList,
                                      TickType_t xTicksToWait,
                                      const BaseType_t xWaitIndefinitely ) ;
# 2937 "../FreeRTOS-Kernel/include/task.h"
BaseType_t xTaskRemoveFromEventList( const List_t * const pxEventList ) ;
void vTaskRemoveFromUnorderedEventList( ListItem_t * pxEventListItem,
                                        const TickType_t xItemValue ) ;
# 2949 "../FreeRTOS-Kernel/include/task.h"
 void vTaskSwitchContext( void ) ;





TickType_t uxTaskResetEventItemValue( void ) ;




TaskHandle_t xTaskGetCurrentTaskHandle( void ) ;





void vTaskMissedYield( void ) ;





BaseType_t xTaskGetSchedulerState( void ) ;





BaseType_t xTaskPriorityInherit( TaskHandle_t const pxMutexHolder ) ;





BaseType_t xTaskPriorityDisinherit( TaskHandle_t const pxMutexHolder ) ;
# 2994 "../FreeRTOS-Kernel/include/task.h"
void vTaskPriorityDisinheritAfterTimeout( TaskHandle_t const pxMutexHolder,
                                          UBaseType_t uxHighestPriorityWaitingTask ) ;




UBaseType_t uxTaskGetTaskNumber( TaskHandle_t xTask ) ;





void vTaskSetTaskNumber( TaskHandle_t xTask,
                         const UBaseType_t uxHandle ) ;
# 3017 "../FreeRTOS-Kernel/include/task.h"
void vTaskStepTick( const TickType_t xTicksToJump ) ;
# 3033 "../FreeRTOS-Kernel/include/task.h"
eSleepModeStatus eTaskConfirmSleepModeStatus( void ) ;





TaskHandle_t pvTaskIncrementMutexHeldCount( void ) ;





void vTaskInternalSetTimeOutState( TimeOut_t * const pxTimeOut ) ;




    }
# 38 "../FreeRTOS-Kernel/include/timers.h" 2




    extern "C" {
# 77 "../FreeRTOS-Kernel/include/timers.h"
struct tmrTimerControl;
typedef struct tmrTimerControl * TimerHandle_t;




typedef void (* TimerCallbackFunction_t)( TimerHandle_t xTimer );





typedef void (* PendedFunction_t)( void *,
                                   uint32_t );
# 230 "../FreeRTOS-Kernel/include/timers.h"
    TimerHandle_t xTimerCreate( const char * const pcTimerName,
                                const TickType_t xTimerPeriodInTicks,
                                const UBaseType_t uxAutoReload,
                                void * const pvTimerID,
                                TimerCallbackFunction_t pxCallbackFunction ) ;
# 360 "../FreeRTOS-Kernel/include/timers.h"
    TimerHandle_t xTimerCreateStatic( const char * const pcTimerName,
                                      const TickType_t xTimerPeriodInTicks,
                                      const UBaseType_t uxAutoReload,
                                      void * const pvTimerID,
                                      TimerCallbackFunction_t pxCallbackFunction,
                                      StaticTimer_t * pxTimerBuffer ) ;
# 388 "../FreeRTOS-Kernel/include/timers.h"
void * pvTimerGetTimerID( const TimerHandle_t xTimer ) ;
# 409 "../FreeRTOS-Kernel/include/timers.h"
void vTimerSetTimerID( TimerHandle_t xTimer,
                       void * pvNewID ) ;
# 447 "../FreeRTOS-Kernel/include/timers.h"
BaseType_t xTimerIsTimerActive( TimerHandle_t xTimer ) ;







TaskHandle_t xTimerGetTimerDaemonTaskHandle( void ) ;
# 1199 "../FreeRTOS-Kernel/include/timers.h"
BaseType_t xTimerPendFunctionCallFromISR( PendedFunction_t xFunctionToPend,
                                          void * pvParameter1,
                                          uint32_t ulParameter2,
                                          BaseType_t * pxHigherPriorityTaskWoken ) ;
# 1236 "../FreeRTOS-Kernel/include/timers.h"
BaseType_t xTimerPendFunctionCall( PendedFunction_t xFunctionToPend,
                                   void * pvParameter1,
                                   uint32_t ulParameter2,
                                   TickType_t xTicksToWait ) ;
# 1250 "../FreeRTOS-Kernel/include/timers.h"
const char * pcTimerGetName( TimerHandle_t xTimer ) ;
# 1267 "../FreeRTOS-Kernel/include/timers.h"
void vTimerSetReloadMode( TimerHandle_t xTimer,
                          const UBaseType_t uxAutoReload ) ;
# 1282 "../FreeRTOS-Kernel/include/timers.h"
UBaseType_t uxTimerGetReloadMode( TimerHandle_t xTimer ) ;
# 1293 "../FreeRTOS-Kernel/include/timers.h"
TickType_t xTimerGetPeriod( TimerHandle_t xTimer ) ;
# 1308 "../FreeRTOS-Kernel/include/timers.h"
TickType_t xTimerGetExpiryTime( TimerHandle_t xTimer ) ;





BaseType_t xTimerCreateTimerTask( void ) ;
BaseType_t xTimerGenericCommand( TimerHandle_t xTimer,
                                 const BaseType_t xCommandID,
                                 const TickType_t xOptionalValue,
                                 BaseType_t * const pxHigherPriorityTaskWoken,
                                 const TickType_t xTicksToWait ) ;


    void vTimerSetTimerNumber( TimerHandle_t xTimer,
                               UBaseType_t uxTimerNumber ) ;
    UBaseType_t uxTimerGetTimerNumber( TimerHandle_t xTimer ) ;
# 1340 "../FreeRTOS-Kernel/include/timers.h"
    void vApplicationGetTimerTaskMemory( StaticTask_t ** ppxTimerTaskTCBBuffer,
                                          StackType_t ** ppxTimerTaskStackBuffer,
                                              uint32_t * pulTimerTaskStackSize );





    }
# 36 "../FreeRTOS-Kernel/include/event_groups.h" 2



    extern "C" {
# 82 "../FreeRTOS-Kernel/include/event_groups.h"
struct EventGroupDef_t;
typedef struct EventGroupDef_t * EventGroupHandle_t;
# 93 "../FreeRTOS-Kernel/include/event_groups.h"
typedef TickType_t EventBits_t;
# 148 "../FreeRTOS-Kernel/include/event_groups.h"
    EventGroupHandle_t xEventGroupCreate( void ) ;
# 201 "../FreeRTOS-Kernel/include/event_groups.h"
    EventGroupHandle_t xEventGroupCreateStatic( StaticEventGroup_t * pxEventGroupBuffer ) ;
# 296 "../FreeRTOS-Kernel/include/event_groups.h"
EventBits_t xEventGroupWaitBits( EventGroupHandle_t xEventGroup,
                                 const EventBits_t uxBitsToWaitFor,
                                 const BaseType_t xClearOnExit,
                                 const BaseType_t xWaitForAllBits,
                                 TickType_t xTicksToWait ) ;
# 357 "../FreeRTOS-Kernel/include/event_groups.h"
EventBits_t xEventGroupClearBits( EventGroupHandle_t xEventGroup,
                                  const EventBits_t uxBitsToClear ) ;
# 414 "../FreeRTOS-Kernel/include/event_groups.h"
    BaseType_t xEventGroupClearBitsFromISR( EventGroupHandle_t xEventGroup,
                                            const EventBits_t uxBitsToClear ) ;
# 493 "../FreeRTOS-Kernel/include/event_groups.h"
EventBits_t xEventGroupSetBits( EventGroupHandle_t xEventGroup,
                                const EventBits_t uxBitsToSet ) ;
# 569 "../FreeRTOS-Kernel/include/event_groups.h"
    BaseType_t xEventGroupSetBitsFromISR( EventGroupHandle_t xEventGroup,
                                          const EventBits_t uxBitsToSet,
                                          BaseType_t * pxHigherPriorityTaskWoken ) ;
# 701 "../FreeRTOS-Kernel/include/event_groups.h"
EventBits_t xEventGroupSync( EventGroupHandle_t xEventGroup,
                             const EventBits_t uxBitsToSet,
                             const EventBits_t uxBitsToWaitFor,
                             TickType_t xTicksToWait ) ;
# 740 "../FreeRTOS-Kernel/include/event_groups.h"
EventBits_t xEventGroupGetBitsFromISR( EventGroupHandle_t xEventGroup ) ;
# 754 "../FreeRTOS-Kernel/include/event_groups.h"
void vEventGroupDelete( EventGroupHandle_t xEventGroup ) ;


void vEventGroupSetBitsCallback( void * pvEventGroup,
                                 const uint32_t ulBitsToSet ) ;
void vEventGroupClearBitsCallback( void * pvEventGroup,
                                   const uint32_t ulBitsToClear ) ;



    UBaseType_t uxEventGroupGetNumber( void * xEventGroup ) ;
    void vEventGroupSetNumber( void * xEventGroup,
                               UBaseType_t uxEventGroupNumber ) ;




    }
# 46 "../../include/FreeRTOS_Sockets.h" 2
# 157 "../../include/FreeRTOS_Sockets.h"
    typedef struct xWIN_PROPS
    {

        int32_t lTxBufSize;
        int32_t lTxWinSize;


        int32_t lRxBufSize;
        int32_t lRxWinSize;
    } WinProperties_t;


    typedef struct xLOW_HIGH_WATER
    {

        size_t uxLittleSpace;
        size_t uxEnoughSpace;
    } LowHighWater_t;






    struct freertos_sockaddr
    {
        uint8_t sin_len;
        uint8_t sin_family;
        uint16_t sin_port;
        uint32_t sin_addr;



    };
# 207 "../../include/FreeRTOS_Sockets.h"
    extern const char * FreeRTOS_inet_ntoa( uint32_t ulIPAddress,
                                            char * pcBuffer );





    typedef unsigned printf_unsigned;
    typedef int printf_signed;
# 236 "../../include/FreeRTOS_Sockets.h"
    struct xSOCKET;
    typedef struct xSOCKET * Socket_t;
    typedef struct xSOCKET const * ConstSocket_t;





        struct xSOCKET_SET;
        typedef struct xSOCKET_SET * SocketSet_t;







    Socket_t FreeRTOS_socket( BaseType_t xDomain,
                              BaseType_t xType,
                              BaseType_t xProtocol );
    int32_t FreeRTOS_recvfrom( Socket_t xSocket,
                               void * pvBuffer,
                               size_t uxBufferLength,
                               BaseType_t xFlags,
                               struct freertos_sockaddr * pxSourceAddress,
                               uint32_t * pxSourceAddressLength );
    int32_t FreeRTOS_sendto( Socket_t xSocket,
                             const void * pvBuffer,
                             size_t uxTotalDataLength,
                             BaseType_t xFlags,
                             const struct freertos_sockaddr * pxDestinationAddress,
                             uint32_t xDestinationAddressLength );
    BaseType_t FreeRTOS_bind( Socket_t xSocket,
                              struct freertos_sockaddr const * pxAddress,
                              uint32_t xAddressLength );







        size_t FreeRTOS_GetLocalAddress( ConstSocket_t xSocket,
                                         struct freertos_sockaddr * pxAddress );
# 289 "../../include/FreeRTOS_Sockets.h"
        BaseType_t FreeRTOS_connect( Socket_t xClientSocket,
                                     struct freertos_sockaddr * pxAddress,
                                     uint32_t xAddressLength );
        BaseType_t FreeRTOS_listen( Socket_t xSocket,
                                    BaseType_t xBacklog );
        BaseType_t FreeRTOS_recv( Socket_t xSocket,
                                  void * pvBuffer,
                                  size_t uxBufferLength,
                                  BaseType_t xFlags );
        BaseType_t FreeRTOS_send( Socket_t xSocket,
                                  const void * pvBuffer,
                                  size_t uxDataLength,
                                  BaseType_t xFlags );
        Socket_t FreeRTOS_accept( Socket_t xServerSocket,
                                  struct freertos_sockaddr * pxAddress,
                                  uint32_t * pxAddressLength );
        BaseType_t FreeRTOS_shutdown( Socket_t xSocket,
                                      BaseType_t xHow );
# 327 "../../include/FreeRTOS_Sockets.h"
                BaseType_t FreeRTOS_GetRemoteAddress( ConstSocket_t xSocket,
                                                      struct freertos_sockaddr * pxAddress );






                static __inline BaseType_t FreeRTOS_GetIPType( ConstSocket_t xSocket )
                {
                    ( void ) xSocket;
                    return ipTYPE_IPv4;
                }



            BaseType_t FreeRTOS_issocketconnected( ConstSocket_t xSocket );


            BaseType_t FreeRTOS_mss( ConstSocket_t xSocket );




        BaseType_t FreeRTOS_connstatus( ConstSocket_t xSocket );


        BaseType_t FreeRTOS_maywrite( ConstSocket_t xSocket );







            BaseType_t FreeRTOS_rx_size( ConstSocket_t xSocket );
            BaseType_t FreeRTOS_tx_space( ConstSocket_t xSocket );
            BaseType_t FreeRTOS_tx_size( ConstSocket_t xSocket );
# 384 "../../include/FreeRTOS_Sockets.h"
        uint8_t * FreeRTOS_get_tx_head( ConstSocket_t xSocket,
                                        BaseType_t * pxLength );
# 447 "../../include/FreeRTOS_Sockets.h"
    BaseType_t FreeRTOS_setsockopt( Socket_t xSocket,
                                    int32_t lLevel,
                                    int32_t lOptionName,
                                    const void * pvOptionValue,
                                    size_t uxOptionLength );
    BaseType_t FreeRTOS_closesocket( Socket_t xSocket );

    BaseType_t FreeRTOS_inet_pton( BaseType_t xAddressFamily,
                                   const char * pcSource,
                                   void * pvDestination );
    const char * FreeRTOS_inet_ntop( BaseType_t xAddressFamily,
                                     const void * pvSource,
                                     char * pcDestination,
                                     uint32_t uxSize );


    uint32_t FreeRTOS_inet_addr( const char * pcIPAddress );
    BaseType_t FreeRTOS_inet_pton4( const char * pcSource,
                                    void * pvDestination );
    const char * FreeRTOS_inet_ntop4( const void * pvSource,
                                      char * pcDestination,
                                      uint32_t uxSize );
# 487 "../../include/FreeRTOS_Sockets.h"
    const struct xSTREAM_BUFFER * FreeRTOS_get_rx_buf( ConstSocket_t xSocket );

    void FreeRTOS_netstat( void );





        typedef enum eSELECT_EVENT
        {
            eSELECT_READ = 0x0001,
            eSELECT_WRITE = 0x0002,
            eSELECT_EXCEPT = 0x0004,
            eSELECT_INTR = 0x0008,
            eSELECT_ALL = 0x000F,

            eSELECT_CALL_IP = 0x0010,

        } eSelectEvent_t;

        SocketSet_t FreeRTOS_CreateSocketSet( void );
        void FreeRTOS_DeleteSocketSet( SocketSet_t xSocketSet );
        void FreeRTOS_FD_SET( Socket_t xSocket,
                              SocketSet_t xSocketSet,
                              EventBits_t xBitsToSet );
        void FreeRTOS_FD_CLR( Socket_t xSocket,
                              SocketSet_t xSocketSet,
                              EventBits_t xBitsToClear );
        EventBits_t FreeRTOS_FD_ISSET( Socket_t xSocket,
                                       SocketSet_t xSocketSet );
        BaseType_t FreeRTOS_select( SocketSet_t xSocketSet,
                                    TickType_t xBlockTimeTicks );




        }

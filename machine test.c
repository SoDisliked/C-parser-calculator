#ifndef __MINCTEST_H__
#define __MINCTEST_H__

#include <stdio.h>
#include <math.h>
#include <time.h>

#define LTEST_FLOAT_TOLERANCE 0.001

static int ltests = 0;
static int lfails = 0;

#define lresults() do {\
    if (lfails == 0) {\
        printf("ALL TESTS PASSED (%d/%d)\n", ltests, ltests);\
    } else {\
        printf("SOME TESTS HAVE FAILED (%d/%d)\n", ltests-lfails, ltests);\
    }\
} while (0)

#define lrun(name, test) do {\
    const int ts = ltests;\
    const int fs = lfails;\
    const clock_t start = clock();\
    printf("\t%-14s", name);\
    test();\
    printf("pass:%2d fail:%2d %4dms\n",\
            (ltests-ts)-(lfails-fs), lfails-fs,\
            (int)((clock() - start) * 1000 / CLOCKS_PER_SEC));\
} while (0)

#define lok(test) do {\
   ++ltests;\
   if (!(test)) {\
       ++lfails;\
       printf("%s:%d error \n", __FILE__, __LINE__);\
    }} while (0)

#define lequal(a, b) do {\
   ++ltests;\
   if ((a) != (b)) {\
       ++lfails;\
       printf("%s:%d (%d != %d)\n", __FILE__, __LINE__, (a), (b));\
}} while (0)

#define lfequal(a, b) do {\
   ++ltests;\
   const double __LF_COMPARE= fabs((double)(a)-(double)(b));\
   if (__LF_COMPARE > LTEST_FLOAT_TOLERANCE || (__LF_COMPARE != __LF_COMPARE)) {\
      ++lfails;\
      printf("%s:%d (%f != %f)\n", __FILE__, __LINE__, (double)(a), (double)(b));\
    }} while (0)

#endif /* machine test */
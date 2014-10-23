#include <stdio.h>


////edited. by Justin Fletcher..


#include <limits.h>
#include <float.h>

#define UCHAR_MIN 0
#define USHRT_MIN 0
#define UINT_MIN 0
#define ULONG_MIN 0


int main()
{

  char c;
  unsigned char uc;
  short s;
  unsigned short us;
  int i;
  unsigned int ui;
  long l;
  unsigned long ul;
  long long ll;
  unsigned long long ull;
  float f;
  double d;




  printf("char =   %lu | min = %d max = %d\n", sizeof(c), SCHAR_MIN, CHAR_MAX); 
  printf("uchar =  %lu | min = %d max = %d\n", sizeof(uc), UCHAR_MIN, UCHAR_MAX);
  printf("short =  %lu | min = %d max = %d\n", sizeof(s), SHRT_MIN, SHRT_MAX);
  printf("ushort = %lu | min = %d max = %d\n", sizeof(us), USHRT_MIN, USHRT_MAX);
  printf("int =    %lu | min = %d max = %d\n", sizeof(i), INT_MIN, INT_MAX);
  printf("uint =   %lu | min = %d max = %d\n", sizeof(ui), UINT_MIN, UINT_MAX);
  printf("long =   %lu | min = %ld max = %ld\n", sizeof(l), LONG_MIN, LONG_MAX);
  printf("ulong =  %lu | min = %d max = %lu\n", sizeof(ul), ULONG_MIN, ULONG_MAX);
  printf("llong =  %lu | min = %ld max = %ld\n", sizeof(ll), LONG_MIN, LONG_MAX);
  printf("ullong = %lu | min = %d max = %lu\n", sizeof(ull), ULONG_MIN, ULONG_MAX);
  printf("float =  %lu | min = %f max = %f\n", sizeof(f), FLT_MIN, FLT_MAX);
  printf("double = %lu | min = %f max = %f\n", sizeof(d), DBL_MIN, DBL_MAX);


  return 0;
}
/* standard header */
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/* standard definitions */
#define LOOP_COUNT 1000

/* main program */
int main(void)
{
  /* variable declaration */
  int i, Fd, BytesWrite;
  char Buffer[1] = "B";
  uint32_t CCHa, CCLa, CCHb, CCLb, TH, TL;
  uint64_t Fa, Fb, T;
  float Overhead = 0.0413;

  /* open /dev/null */
  Fd = open("dev/null", O_WRONLY);

  /* start counter */
  __asm__ __volatile__ (
                          "xorl %%eax, %%eax\n"
                          "cpuid\n"
                          "rdtsc\n"
                          : "=a" (CCLa), "=d" (CCHa)
                          :
                          : "%ebx", "%ecx");
     
  /* write 1 byte to /dev/null */
  BytesWrite = write(Fd, Buffer, 1);
     
  /* end counter */
  __asm__ __volatile__ (
                          "xorl %%eax, %%eax\n"
                          "cpuid\n"
                          "rdtsc\n"
                          : "=a" (CCLb), "=d" (CCHb)
                          :
                          : "%ebx", "%ecx");
     
  /* cycle count: start, end */
  Fa = (((uint64_t)CCHa << 32) | CCLa);
  Fb = (((uint64_t)CCHb << 32) | CCLb);
    
  /* total elapsed cycles */
  T = (Fb - Fa);
  printf("%f\n", ((T/(1500.096))-Overhead));
   
  return(0);
    
} /* main () */

